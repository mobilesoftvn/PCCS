#include "LightFactory.h"
#include "LightSoldier.h"

LightFactory* LightFactory::INSTANCE = 0;

LightFactory::LightFactory() {

}

LightFactory::LightFactory(const LightFactory& origin) {
    // Thou shalt not clone.
}

GameObject* LightFactory::create(string objectName) {
    if(INSTANCE == 0) {
        INSTANCE = new LightFactory();
    }

    return INSTANCE->createFromString(objectName);
}

GameObject* LightFactory::createFromString(string objectName) {

    string nameLowerCase = objectName;

    transform(nameLowerCase.begin(), nameLowerCase.end(), nameLowerCase.begin(), ::tolower);

    if(nameLowerCase == "tree") {
        return new LightTree();

    } else if(nameLowerCase == "soldier") {
        LightSoldier* ls = new LightSoldier();
        ls->weapon = static_cast<LightWeapon*>(create("weapon"));
        ls->addComponent(ls->weapon);
        return ls;

    } else if(nameLowerCase == "weapon") {
        return new LightWeapon();

    } else if(nameLowerCase == "bullet") {
        return new LightBullet();

    }

    throw SharedException(
        "Unable to create a '" + objectName + "' instance, it "
        "is not a known type in the LightFactory. ");
}