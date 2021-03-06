#include "BSPTree.h"
#include "Pathfinding.h"

BSPTree::BSPTree(float initialWidth, float initialHeight, float smallestSize, unsigned int collisionMaxPerSpace) :
    _enableDebug(false),
    _initialWidth(initialWidth),
    _initialHeight(initialHeight),
    _smallestSize(smallestSize),
    _collisionMaxPerSpace(collisionMaxPerSpace),
    _isTreeIterating(false),
    _isPathfindingDirty(true)
{
    setType("BSPTree");
    _boundingBox.size.x = _initialWidth;
    _boundingBox.size.y = _initialHeight;

    _root = new Space(0, 0, _initialWidth, _initialHeight, static_cast<unsigned int>(smallestSize));

    stringstream ss1;
    ss1 << "Created a " << _initialWidth << "x" << _initialHeight << " BSP tree.";
    Console::log(ss1.str());

    stringstream ss2;
    ss2 << "Minimal tile size: " << smallestSize << "x" << smallestSize
            << ". Preferred collisions per space: " << collisionMaxPerSpace;
    Console::log(ss2.str());

    pathfinding = new Pathfinding(*this);
    //addComponent(pathfinding); // NB: breaks the server.
}

BSPTree::~BSPTree() {
    delete _root;
    _root = nullptr;
    delete pathfinding;
    pathfinding = nullptr;
}

bool BSPTree::inlineOfSight(const Vector3& a, const Vector3& b) {
    Line2 lineOfSight(a, b);
    Box3 coadunation(a, b - a);
    coadunation.repair();

    vector<Entity*> entities = getEntitiesFromBox(coadunation);

    for(Entity* entity : entities) {
        if(entity->isType("Bullet")) {
            continue;
        }

        Box3 box = entity->getBoundingBox();
        if(box.intersect(lineOfSight)) {
            return false;
        }
    }

    return true;
}

bool BSPTree::inlineOfSight(Entity* eye, Entity* target) {
    const Vector3& a = eye->getBoundingBox().getCenter();
    const Vector3& b = target->getBoundingBox().getCenter();

    Line2 lineOfSight(a, b);
    Box3 coadunation(a, b - a);
    coadunation.repair();

    vector<Entity*> entities = getEntitiesFromBox(coadunation);

    for(Entity* entity : entities) {
        if(entity->isType("Bullet")) {
            continue;
        }

        Box3 box = entity->getBoundingBox();

        if(entity == eye || entity == target) {
            continue;
        }

        // Assume that we can see through our own type.
        // EG: a soldier can  see through other soldiers.
        if(eye->isType(entity)) {
            continue;
        }

        if(box.intersect(lineOfSight)) {
            return false;
        }
    }

    return true;
}

bool BSPTree::inlineOfSight(Entity* eye, const Vector3& b) {
    const Vector3& a = eye->getBoundingBox().getCenter();

    Line2 lineOfSight(a, b);
    Box3 coadunation(a, b - a);
    coadunation.repair();

    vector<Entity*> entities = getEntitiesFromBox(coadunation);

    for(Entity* entity : entities) {
        if(entity->isType("Bullet")) {
            continue;
        }

        Box3 box = entity->getBoundingBox();

        if(entity == eye) {
            continue;
        }

        // Assume that we can see through our own type.
        // EG: a soldier can  see through other soldiers.
        if(eye->isType(entity)) {
            continue;
        }

        if(box.intersect(lineOfSight)) {
            return false;
        }
    }

    return true;
}

void BSPTree::addComponent(Composite* component) {
    if(!dynamic_cast<Entity*>(component)) {
        throw SharedException(
                "Only phantom::Entity derivatives "
                "can be added to a BSPtree layer."
        );
    }

    Layer::addComponent(component);
}

void BSPTree::update(const PhantomTime& time) {
    getGraphics().clear();

    pathfinding->update(time);

    _isTreeIterating = true;

    _root->clear();
    // We just cleared the tree, so the first pathfinding call, need not
    // clean it first. This means that the first pathfinding run per update,
    // has about zero overhead.
    _isPathfindingDirty = false;

    vector<Composite*>& children    = getComponents();

    // Insert everything to build up the BSP tree.
    for(vector<Composite*>::iterator it = children.begin(); it != children.end(); ++it) {
        Entity* entity = static_cast<Entity*>(*it);

        _root->insert(entity);
    }

    Layer::update(time);

    vector<Space*> spaces;
    _root->getCollisionSpaces(spaces, _collisionMaxPerSpace);

    for(size_t i = 0; i < spaces.size(); ++i) {
        Box3& area = spaces[i]->getArea();
        vector<Entity*>& entities = spaces[i]->getEntities();
        vector<Entity*>::iterator a, b;
        int offset = 0;

        for(a = entities.begin(); a != entities.end(); ++a, ++offset) {
            if((*a)->isDestroyed()) {
                continue;
            }

            b = entities.begin();
            std::advance(b, offset);
            for(; b != entities.end(); ++b) {
                if((*b)->isDestroyed()) {
                    continue;
                }

                if(*a != *b) {
                    if(calculateCollision(*a, *b)) {
                        CollisionData collisionData;

                        //if((*a)->canCollideWith(*b)) { // <-- actually costs FPS ?!?!
                            (*a)->onCollision(*b, collisionData);
                            (*b)->onCollision(*a, collisionData);
                        //}
                    }
                }
            }
        }
    }

    if(_enableDebug) {
        getGraphics().clear();
        _root->render(getGraphics());
    }

    _isTreeIterating = false;

    for(auto it = _destroyUs.begin(); it != _destroyUs.end(); ++it) {
        destroyComponent(*it);
    }
    _destroyUs.clear();


    for(auto it = _removeUs.begin(); it != _removeUs.end(); ++it) {
        removeComponent(*it);
    }
    _removeUs.clear();
}

vector<Entity*> BSPTree::getEntitiesFromBox(const Box3& location) {
    vector<Entity*> returnValue;
    vector<Composite*> children = getComponents();

    for(vector<Composite*>::iterator it = children.begin(); it != children.end(); ++it){
        Entity* e = static_cast<Entity*>(*it);
        if(e->getBoundingBox().intersect(location)){
            returnValue.push_back(e);
        }
    }

    return returnValue;
}

bool BSPTree::calculateCollision(Entity *a, Entity *b) {
    // TODO: fancier shape testing, please!
    return a->getBoundingBox().intersect(b->getBoundingBox());;
}

void BSPTree::enableDebug() {
    _enableDebug = true;
}

void BSPTree::disableDebug() {
    _enableDebug = false;
}

Space* BSPTree::getSpaceAtUsingHeuristic(const Vector3& location, Entity* entity) {
    return _root->getSpaceAtUsingHeuristic(location, entity);
}

Space* BSPTree::getSpaceAt(const Vector3& location) {
    return _root->getSpaceAt(location);
}

vector<Space*>& BSPTree::getNeighbours(Space* location, Entity* entity) {
    return _root->getNeighboursOf(location, entity);
}

void BSPTree::cleanPathfinding() {
    if(_isPathfindingDirty) {
        _root->cleanPathfinding();
    }

    // Since this function is called, assume that the callee will make the
    // pathfinding stuff dirty.
    _isPathfindingDirty = true;
}

void BSPTree::getEntitiesAt(vector<Entity*>& out, Vector3& location) {
    Space* space = _root->getSpaceAt(location);

    if(space != nullptr) {
        vector<Entity*>& entities = space->getEntities();

        for(Entity* entity : entities) {
             if(entity->getBoundingBox().contains(location)) {
                out.push_back(entity);
            }
        }
    }
}

void BSPTree::destroyComponent(Composite* who) {
    if(_isTreeIterating) {
        _destroyUs.push_back(who);
    } else {
        Layer::destroyComponent(who);
    }
}

void BSPTree::removeComponent(Composite* who) {
    if(_isTreeIterating) {
        _removeUs.push_back(who);
    } else {
        Layer::removeComponent(who);
    }
}