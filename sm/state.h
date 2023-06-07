#pragma once

namespace sm {

template<typename T>
class State {
protected:
    T *context;

public:
    State() : context{nullptr} {}

    void setContext(T *ctx) {
        context = ctx;
    }

    virtual void enter() {};
    virtual void execute() {};
    virtual void exit() {};
};

}
