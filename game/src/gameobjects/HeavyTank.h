#ifndef HEAVYTANK_H_
#define HEAVYTANK_H_

#include <sharedlib/gameobjects/LightTank.h>

class HeavyTank : public LightTank {
public:
    HeavyTank();
    ~HeavyTank();

    void update(const phantom::PhantomTime &time);
    void paint();
    void attack(GameObject *victim);
    void move(const Vector3& location);
    void onMouseHover(const Vector3& mouseLocationWorld, const Vector3& mouseLocationScreen);
    void fromData(Data &data);
    void toData(Data& data);
private:
    Vector3 _directionTur;
};

#endif // !HEAVYTANK_H_
