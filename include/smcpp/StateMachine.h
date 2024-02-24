#pragma once

#include <cassert>

#include "smcpp/internal/EventBase.h"
#include "smcpp/internal/StateBase.h"

namespace smcpp {

template<int S, int E>
class StateMachine {
    struct StateTransition;

    struct Transition {
        internal::EventBase *event;
        StateTransition *next;

        Transition() : event{nullptr}, next{nullptr} {}
    };

    struct StateTransition {
        internal::StateBase *state;
        Transition transitions[E];

        StateTransition() : state{nullptr} {}
    };

    StateTransition states[S];
    StateTransition *current;

public:
    StateMachine();

    void transit(internal::StateBase *from, internal::StateBase *to, internal::EventBase *event);
    void start(internal::StateBase *initial);
    void update();
};

template<int S, int E>
StateMachine<S, E>::StateMachine() : current{nullptr} {

}

template<int S, int E>
void StateMachine<S, E>::transit(internal::StateBase *from, internal::StateBase *to, internal::EventBase *event) {
    assert(from!=nullptr);
    assert(to!=nullptr);
    assert(event!=nullptr);

    StateTransition *from_transition = nullptr;
    StateTransition *to_transition = nullptr;

    for(StateTransition &s : states) {
        if(s.state==from || s.state==nullptr) {
            s.state = from;
            from_transition = &s;
            break;
        }
    }

    for(StateTransition &s : states) {
        if(s.state==to || s.state==nullptr) {
            s.state = to;
            to_transition = &s;
            break;
        }
    }

    assert(from_transition!=nullptr);
    assert(to_transition!=nullptr);

    Transition *transition = nullptr;

    for(Transition &t : from_transition->transitions) {
        if(t.next==nullptr) {
            transition = &t;
            break;
        }
    }

    assert(transition!=nullptr);

    transition->event = event;
    transition->next = to_transition;
}

template<int S, int E>
void StateMachine<S, E>::start(internal::StateBase *initial) {
    assert(initial!=nullptr);

    for(StateTransition &s : states) {
        if(s.state==initial) {
            current = &s;
            break;
        }
    }

    assert(current!=nullptr);

    for(Transition &t : current->transitions) {
        if(t.event!=nullptr) {
            t.event->reset();
        }
    }

    current->state->enter();
}

template<int S, int E>
void StateMachine<S, E>::update() {
    assert(current!=nullptr);

    Transition *transition = nullptr;

    for(Transition &t : current->transitions) {
        if(t.event!=nullptr) {
            if(t.event->triggered()) {
                transition = &t;
                break;
            }
        }
    }

    if(transition!=nullptr) {
        current->state->exit();
        transition->event->action();
        current = transition->next;

        for(Transition &t : current->transitions) {
            if(t.event!=nullptr) {
                t.event->reset();
            }
        }

        current->state->enter();
    }

    current->state->execute();
}

}
