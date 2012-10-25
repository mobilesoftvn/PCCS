#include "LightFactory.h"


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
        return new LightSoldier();
    }

    throw SharedException(
        "Unable to create a '" + objectName + "' instance, it "
        "is not a known type in the LightFactory. ");
}