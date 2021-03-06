#ifndef BSPTREE_H
#define	BSPTREE_H

#include <phantom.h>
#include "Space.h"
#include <vector>
#include "../SharedException.h"
#include "../CompileConfig.h"

using namespace phantom;
using namespace std;

class Pathfinding;

class LIBEXPORT BSPTree : public Layer  {
public:
    BSPTree(float initialWidth, float initialHeight, float smallestSize, unsigned int collisionMaxPerSpace);
    virtual ~BSPTree();

    virtual void addComponent(Composite* component);
    virtual void update(const PhantomTime& time);
    virtual void removeComponent(Composite* who);
    virtual void destroyComponent(Composite* who);

    void enableDebug();
    void disableDebug();

    bool inlineOfSight(Entity* eye, Entity* target);
    bool inlineOfSight(Entity* eye, const Vector3& b);
    bool inlineOfSight(const Vector3& a, const Vector3& b);

    vector<Entity*> getEntitiesFromBox(const Box3& location);
    void getEntitiesAt(vector<Entity*>& out, Vector3& location);
    Pathfinding* pathfinding;

    friend class Space;
    friend class Pathfinding;
private:
    vector<Space*>& getNeighbours(Space* location, Entity* entity);
    Space* getSpaceAt(const Vector3& location);
    Space* getSpaceAtUsingHeuristic(const Vector3& location, Entity* entity = nullptr);

    void cleanPathfinding();
    bool calculateCollision(Entity* a, Entity* b);

    bool _enableDebug;
    float _initialWidth;
    float _initialHeight;
    float _smallestSize;
    unsigned int _collisionMaxPerSpace;
    Space* _root;
    bool _isTreeIterating;

    // The sadness is unbearable :(
    deque<Composite*> _destroyUs;
    deque<Composite*> _removeUs;

    bool _isPathfindingDirty;
};

#endif	/* BSPTREE_H */

