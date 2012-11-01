#include "ScrollBehaviour.h"

ScrollBehaviour::ScrollBehaviour() {
    setType("ScrollBehaviour");

    _input    = getDriver()->getInput();
    _edgeSize = 70;

    for(int i = 0; i < 4; ++i) {
        _hasMouse[i] = false;
    }

    _normals[0].y = -1;
    _normals[1].x = 1;
    _normals[2].y = 1;
    _normals[3].x = -1;

    matchScreen();
    draw();
}

void ScrollBehaviour::update(const Time& time) {
    Composite::update(time);
    Vector3 mousePosition = _input->getMouseState()->getMousePosition();

    // Premature off-screen detection. It's getting genuine annoying that
    // the camera keeps scrolling when my mouse is offscreen... Especially
    // since I'm also running the game in parallel on my desktop. -- Gerjo
    Vector3 screensize = getPhantomGame()->getWorldSize();
    const float threshold = 15;

    if(mousePosition.x > screensize.x-threshold || mousePosition.x < threshold ||
       mousePosition.y > screensize.y-threshold || mousePosition.y < threshold) {
        return;
    }

    bool hasChange = false;

    for(int i = 0; i < 4; ++i) {
        bool newState = 0;

        if(_edges[i].contains(mousePosition)) {
            newState = true;
            getDriver()->getActiveCamera()->addPosition(_normals[i] * time.getElapsed() * 450);
        }

        if(_hasMouse[i] != newState) {
            hasChange = true;
        }

        _hasMouse[i] = newState;
    }

    if(hasChange) {
        draw();
    }
}

void ScrollBehaviour::matchScreen(void) {

    float width  = static_cast<float>(getPhantomGame()->getWorldSize().x);
    float height = static_cast<float>(getPhantomGame()->getWorldSize().y);

    _edges[0].origin.x = 0.0f;
    _edges[0].origin.y = 0.0f;
    _edges[0].size.x   = width;
    _edges[0].size.y   = static_cast<float>(_edgeSize);

    _edges[1].origin.x = width - static_cast<float>(_edgeSize);
    _edges[1].origin.y = 0.0f;
    _edges[1].size.x   = static_cast<float>(_edgeSize);
    _edges[1].size.y   = height;

    _edges[2].origin.x = 0.0f;
    _edges[2].origin.y = height - static_cast<float>(_edgeSize);
    _edges[2].size.x   = width;
    _edges[2].size.y   = static_cast<float>(_edgeSize);

    _edges[3].origin.x = 0.0f;
    _edges[3].origin.y = 0.0f;
    _edges[3].size.x   = static_cast<float>(_edgeSize);
    _edges[3].size.y   = height;
}

void ScrollBehaviour::draw(void) {

    Graphics& g = getGraphics().clear();

    for(int i = 0; i < 4; ++i) {
        g.beginPath();

        if(_hasMouse[i]) {
            g.setFillStyle(Color(0, 0, 0, 100));
        } else {
            g.setFillStyle(Color(0, 0, 0, 30));
        }

        g.rect(_edges[i].origin.x, _edges[i].origin.y, _edges[i].size.x, _edges[i].size.y);
        g.fill();
    }
}