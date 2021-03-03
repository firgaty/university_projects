#ifndef INCLUDE_CONTROLLER_KEYBOARDLAYOUT_HPP_
#define INCLUDE_CONTROLLER_KEYBOARDLAYOUT_HPP_

#include <wchar.h>

#include "Controller/Input.hpp"

struct KeyboardLayout {
    virtual const Input operator()(const wint_t &c) = 0;
};

struct Layout_en_GB : public virtual KeyboardLayout {
    const Input operator()(const wint_t &c);
};
struct Layout_fr_FR : public virtual KeyboardLayout {
    const Input operator()(const wint_t &c);
};
struct Layout_en_US : public virtual KeyboardLayout {
    const Input operator()(const wint_t &c);
};

#endif