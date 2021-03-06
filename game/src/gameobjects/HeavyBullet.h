#ifndef HEAVYBULLET_H
#define	HEAVYBULLET_H

#include <phantom.h>
#include <sharedlib/gameobjects/LightBullet.h>
#include "../networking/Dedicated.h"

using namespace phantom;

class HeavyBullet : public LightBullet {
public:
    HeavyBullet();
    virtual ~HeavyBullet();
    virtual void update(const PhantomTime& time);
    virtual void onCollision(Composite* entity, CollisionData& collisionData);

private:

};

#endif	/* HEAVYBULLET_H */
