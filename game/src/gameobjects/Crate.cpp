#include "Crate.h"

namespace phantom{
    Crate::Crate():isVisible(true) {

        _boundingBox.size.x = 32;
        _boundingBox.size.y = 36;

        setType("Crate");
        draw();
    }
    void Crate::draw(){
        getGraphics().clear();
        if(isVisible){

            getGraphics()
                .beginPath()
                .setFillStyle(Colors::WHITE)
                .image("images/crate32x36.png", 0, 0, _boundingBox.size.x, _boundingBox.size.y)
                .fill();

            return;
        }
    }
    void Crate::onCollision(Composite* other){
        if(other->isType("Soldier") && isVisible){
            std::cout << "Got an item!!" << endl;
            isVisible = false;
            draw();
        }
    }

}