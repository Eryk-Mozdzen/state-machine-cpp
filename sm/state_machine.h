#pragma once

#include "state.h"

namespace sm {

template<int MAX_EVENTS>
class StateMachine {
    State<MAX_EVENTS> *current;

public:
    StateMachine(State<MAX_EVENTS> *st);

    void link(State<MAX_EVENTS> *from, State<MAX_EVENTS> *to, Event *trigger);

    void update();
    void execute() const;
};

template<int MAX_EVENTS>
StateMachine<MAX_EVENTS>::StateMachine(State<MAX_EVENTS> *st) : current{st} {
    if(current==nullptr) {
        return;
    }

    current->on_enter();
}

template<int MAX_EVENTS>
void StateMachine<MAX_EVENTS>::link(State<MAX_EVENTS> *from, State<MAX_EVENTS> *to, Event *trigger) {
    if(from==nullptr || to==nullptr || trigger==nullptr) {
        return;
    }

    sm::State<MAX_EVENTS>::link(from, to, trigger);
}

template<int MAX_EVENTS>
void StateMachine<MAX_EVENTS>::update() {
    if(current==nullptr) {
        return;
    }

    sm::State<MAX_EVENTS>::handle(&current);
}

template<int MAX_EVENTS>
void StateMachine<MAX_EVENTS>::execute() const {
    if(current==nullptr) {
        return;
    }

    current->on_execute();
}

}
