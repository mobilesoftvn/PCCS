#include "Ground.h"

Ground::Ground() {
    draw();
}

void Ground::draw(void) {
    getGraphics()
        .setFillStyle(Color(0,0,0))
    .rect(0, 0, 12, 12)
    .beginPath()
    .setFillStyle(Color(0,127,0))
    .rect(1, 1, 11, 11)
    .beginPath();
}

void Ground::update(const float& elapsed) {

}
