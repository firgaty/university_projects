#ifndef INCLUDE_CONTROLLER_CONTROLLERBASE_HPP_
#define INCLUDE_CONTROLLER_CONTROLLERBASE_HPP_

#include "Input.hpp"

class ControllerBase
{
public:
    virtual const Input input()     = 0;
    virtual ~ControllerBase() = 0;
};

using Controller = ControllerBase;

#endif // INCLUDE_CONTROLLER_CONTROLLERBASE_HPP_