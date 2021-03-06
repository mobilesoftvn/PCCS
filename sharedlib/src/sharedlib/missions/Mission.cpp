#include "Mission.h"
#include <core/Console.h>

Mission::Mission(const std::string& title) {
    //Generate some mission at the moment.
    setType("Mission");

    UID_network = "Nico W.I.P.";

    std::function<void(string args)> function = [this] (string args) {
        // Will cause a memory leak since the components are not being deleted.
        for(Objective *obj : _objectives) {
            obj->forcedComplete = true;
        }
    };
    Console::mapCommand("complete(" + title + ")", function);
}

Mission::~Mission() {
    for(auto objective = _objectives.begin(); objective != _objectives.end();) {
        if(*objective != nullptr) {
            delete *objective;
            objective = _objectives.erase(objective);
        }
        else {
            ++objective;
        }
    }

    for(auto objective = _objectivesCompleted.begin(); objective != _objectivesCompleted.end();) {
        if(*objective != nullptr) {
            delete *objective;
            objective = _objectives.erase(objective);
        }
        else {
            ++objective;
        }
    }
}

void Mission::addObjective(Objective *objectiveID) {
    _objectives.push_back(objectiveID);
    Console::log("New objective: " + objectiveID->getTitle());
}

void Mission::toData(Data& data){
    GameObject::toData(data);
}

void Mission::fromData(Data& data){
    GameObject::fromData(data);

}


void Mission::removeObjective(Objective *objectiveID) {
    std::vector<Objective*>::iterator obj;
    for(obj = _objectives.begin(); obj != _objectives.end(); ++obj) {
        if(*obj == objectiveID) {
            _objectives.erase(obj);
            return;
        }
    }
}
void Mission::update(const PhantomTime& time){
    GameObject::update(time);
    checkIfCompleted();
}

void Mission::onMissionComplete() {
    if(_objectives.empty())
        Console::log("Mission complete!");
}

void Mission::checkIfCompleted() {
    for(std::vector<Objective*>::iterator o = _objectives.begin(); o != _objectives.end();) {
        if((*o)->wasMore){
            if((*o)->conditionsMet()) {
                (*o)->destroy();
                //delete *o;
                *o = 0;
                o = _objectives.erase(o);

                onMissionComplete();
            }else{
                ++o;
            }
        }else{
            ++o;
        }
    }
}
