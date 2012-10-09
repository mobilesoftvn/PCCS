#include "Tree.h"

Tree::Tree() : GameObject() {
    setType("Tree");

    _boundingBox.size.x = 32;
    _boundingBox.size.y = 32;

    getGraphics()
        .beginPath()
        .setFillStyle(Colors::WHITE)
        //.rect(_boundingBox)
        .image("images/tree64.png", 0, 0, _boundingBox.size.x, _boundingBox.size.y)
        .fill()
    ;
}

bool Tree::canCollideWith(Composite* other) {
    if(other->isType("Tree")) {
        return false;
    }

    return true;
}