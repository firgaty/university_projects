#ifndef INCLUDE_APPCREATOR_HPP_
#define INCLUDE_APPCREATOR_HPP_

#include "AppBase.hpp"

class AppCreator : public virtual AppBase
{
public:
    AppCreator(ControllerBase *controller, Display *view);
    ~AppCreator();
    int loop();
};

#endif // INCLUDE_APPCREATOR_HPP_
