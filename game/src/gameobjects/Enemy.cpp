#include "Enemy.h"
#include "layer/EntityLayer.h"

namespace phantom{
    Enemy::Enemy(){
        isAttacking = false;
        setType("Enemy");
        _target  = 0;
        draw();
        _boundingBox.size.x = 100;
        _boundingBox.size.y = 100;
    }
    void Enemy::draw(){
        getGraphics().clear();
        getGraphics()
            .beginPath()
            .setFillStyle(Colors::WHITE)
            .rect(_boundingBox.size.x / 2 + 5, _boundingBox.size.y / 2 + 5, 14.0f, 14.0f)
            .stroke();

        getGraphics()
            .beginPath()
            .rect(_boundingBox.size.x / 2 + 6, _boundingBox.size.y / 2 + 6, 12.0f, 12.0f);

        if(isAttacking) {
            getGraphics().setFillStyle(Colors::GREEN);
        } else {
            getGraphics().setFillStyle(Colors::BLUE);
        }
        getGraphics().stroke();


    }
    void Enemy::attack(Soldier* target){
        getGraphics()
            .beginPath()
            .setFillStyle(Colors::RED)
            .line(_boundingBox.size.x / 2 + 11, _boundingBox.size.y / 2 + 11,target->getPosition().x - _position.x,target->getPosition().y - _position.y)
            .fill();
    }
    void Enemy::update(const float& elapsed){
        draw();
        if(isAttacking){
            attack(_target);
        }
        isAttacking = false;
        _target = 0;
    }
    void Enemy::onCollision(Composite* other){
        if(_target == 0){
            if(other->isType("Soldier")){
                isAttacking = true;
                _target = static_cast<Soldier*>(other);
            }
        }
    }
}