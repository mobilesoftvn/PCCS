#include "Tree.h"

Tree::Tree() : phantom::Entity()
{
    draw();
}

Tree::~Tree()
{
}

void Tree::draw() {
    phantom::Graphics *gfx = getGraphics();
    gfx->beginPath();
    gfx->setFillStyle(phantom::Color(75, 33, 0, 127));
    gfx->image("tree.png", 0, 0, 151, 142);
    gfx->beginPath();
}

void Tree::update(float elapsed) {
    Entity::update(elapsed);
}