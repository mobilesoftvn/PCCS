#ifndef CLICKABLEENTITY_H_
#define CLICKABLEENTITY_H_

#include <core/Entity.h>
#include <utils/Time.h>
#include <physics/Vector3.h>
#include <input/MouseState.h>

#include "CompileConfig.h"

class LIBEXPORT ClickableEntity : public phantom::Entity
{
public:
    virtual void clicked(const phantom::MouseState& mouseState) = 0;
    virtual void unclicked(const phantom::MouseState& mouseState) = 0;
    virtual void update(const phantom::Time& time);
};

#endif // !CLICKABLEENTITY_H_