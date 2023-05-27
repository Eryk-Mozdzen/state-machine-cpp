#pragma once

#include "state.h"

namespace sm {

template<int MAX_EVENTS>
class StateMachine {
    State<MAX_EVENTS> *current;

public:
    StateMachine(State<MAX_EVENTS> *st);

    void update();
};

template<int MAX_EVENTS>
StateMachine<MAX_EVENTS>::StateMachine(State<MAX_EVENTS> *st) : current{st} {
    if(current==nullptr) {
        return;
    }

    current->on_enter();
}

template<int MAX_EVENTS>
void StateMachine<MAX_EVENTS>::update() {
    if(current==nullptr) {
        return;
    }

    sm::State<MAX_EVENTS>::handle(&current);
    current->on_execute();
}

}
