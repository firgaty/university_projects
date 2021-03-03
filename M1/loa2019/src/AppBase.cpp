#include "AppBase.hpp"

AppBase::AppBase(ControllerBase *controller, Display *view)
{
    _controller = controller;
    _view       = view;
}

AppBase::~AppBase()
{
    delete _controller;
    delete _view;
}