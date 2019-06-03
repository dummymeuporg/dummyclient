#pragma once

#include <exception>

namespace Model {

class Error : public std::exception {

};

class ScreenNotHandled : public Error {
public:
    virtual const char* what() const noexcept override {
        return "this screen is not handled";
    };
};

} // namespace Model
