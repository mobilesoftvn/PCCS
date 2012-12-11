#ifndef LIGHTTANKMECH_H_
#define LIGHTTANKMECH_H_

#include "../artificialintelligence/AIState.h"
#include "LightWeapon.h"
#include "GameObject.h"
#include "EnemyMixin.h"

class LIBEXPORT LightTankMech : public GameObject, public EnemyMixin {
public:
    LightTankMech();
    virtual ~LightTankMech();

    virtual void update(const phantom::PhantomTime& time);

    LightWeapon *weapon;

    virtual MessageState handleMessage(AbstractMessage *message);
    void fromData(Data &data);
    void toData(Data& data);
    Pathfinding::Route seekRoute(Vector3 location);
    virtual void move(const Vector3& location);

private:
    AIState *moveState, *attackState;
};

#endif