#pragma once

namespace sm {

class State {
    virtual void enter() {}
    virtual void execute() {}
    virtual void exit() {}

    template <int S, int E>
    friend class StateMachine;
};

}
