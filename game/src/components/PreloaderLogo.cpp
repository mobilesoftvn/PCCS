#include "PreloaderLogo.h"

PreloaderLogo::PreloaderLogo() {

    Vector3 splashSize(800, 400, 0);
    Vector3 splashPos = (getGame()->getViewPort() - splashSize) * 0.5;// * 0.5 +  * 0.5;

    getGraphics()
            .clear()
            .beginPath()
            .setFillStyle(Colors::BLACK)
            .rect(0, 0, getGame()->getViewPort().x, getGame()->getViewPort().y)
            .fill()

            .beginPath()
            .setFillStyle(Colors::WHITE)
            .image("images/splashscreen.png", splashPos.x, splashPos.y, splashSize.x, splashSize.y)
            .fill()
            ;
}