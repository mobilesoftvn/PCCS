#include "Clicktor.h"
#include <sharedlib/gameobjects/GameObject.h>

using namespace std;
using namespace phantom;

void Clicktor::setCamera(Camera *camera) {
    this->_camera = camera;
}

void Clicktor::update(const Time& time) {
    GameObject *gameobject = dynamic_cast<GameObject *>(getParent());

    if(gameobject != nullptr) {
        MouseState* mouseState = getDriver()->getInput()->getMouseState();
        Box3 bb = gameobject->getBoundingBox();
        if(bb.contains(mouseState->getPosition() + _camera->getPosition()) && mouseState->isButtonDown(Buttons::LEFT_MOUSE)) {
            gameobject->onClick(mouseState);
            mouseState->handleEvent(Buttons::LEFT_MOUSE, 0);
        } else if(mouseState->isButtonDown(Buttons::LEFT_MOUSE)) {
            gameobject->onUnClicked(mouseState);
        }
    }
}