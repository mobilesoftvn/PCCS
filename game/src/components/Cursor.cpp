#include "Cursor.h"

Cursor::Cursor() : _doRedraw(true) {
    setType("Cursor");
}

void Cursor::update(const Time& time) {
    Entity::update(time);

    MouseState* mouseState = getPhantomGame()->getDriver()->getInput()->getMouseState();
    Vector3 position = mouseState->getMousePosition();

    setPosition(position);

    if(_doRedraw) {
        draw();
    }
}

void Cursor::draw(void) {
    _doRedraw = false;

    getGraphics()
            .clear()
            .beginPath()
            .setFillStyle(Colors::WHITE)
            .image("images/cursors/mouse3.png", 0, 0, 49, 65)
            ;

    if(!_tooltip.empty()) {
        getGraphics().text(10.0f, 30.0f, 10, "fonts/waree.ttf", _tooltip);
    }

    getGraphics().stroke();
}

void Cursor::setTooltip(string tooltip) {
    _doRedraw = true;
    _tooltip  = tooltip;
}
