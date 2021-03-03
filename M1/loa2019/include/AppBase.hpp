#ifndef INCLUDE_APPBASE_HPP_
#define INCLUDE_APPBASE_HPP_

#include "Controller/ControllerBase.hpp"
#include "View/Display.hpp"

class AppBase
{
protected:
    ControllerBase *_controller;
    Display *_view;

public:
    AppBase(ControllerBase *controller, Display *view);
    virtual ~AppBase() = 0;
    virtual int loop() = 0;
};

#endif // INCLUDE_APPBASE_HPP_