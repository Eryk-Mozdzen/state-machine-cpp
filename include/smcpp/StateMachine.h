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

    void clear_events();
    void reset_events();

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

    for(int i=0; i<S; i++) {
        if(states[i].state==from || states[i].state==nullptr) {
            states[i].state = from;
            from_transition = &states[i];
            break;
        }
    }

    for(int i=0; i<S; i++) {
        if(states[i].state==to || states[i].state==nullptr) {
            states[i].state = to;
            to_transition = &states[i];
            break;
        }
    }

    assert(from_transition!=nullptr);
    assert(to_transition!=nullptr);

    Transition *transition = nullptr;

    for(int i=0; i<E; i++) {
        if(from_transition->transitions[i].next==nullptr) {
            transition = &from_transition->transitions[i];
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

    current = nullptr;

    for(int i=0; i<S; i++) {
        if(states[i].state==initial) {
            current = &states[i];
            break;
        }
    }

    assert(current!=nullptr);

    current->state->enter();
}

template<int S, int E>
void StateMachine<S, E>::update() {
    assert(current!=nullptr);

    Transition *transition = nullptr;

    for(int i=0; i<E; i++) {
        if(current->transitions[i].event!=nullptr && current->transitions[i].next!=nullptr) {
            if(current->transitions[i].event->triggered()) {
                transition = &current->transitions[i];
                break;
            }
        }
    }

    clear_events();

    if(transition!=nullptr) {
        current->state->exit();
        transition->event->action();
        current = transition->next;
        reset_events();
        current->state->enter();
    }

    current->state->execute();
}

template<int S, int E>
void StateMachine<S, E>::clear_events() {
    for(int i=0; i<S; i++) {
        for(int j=0; j<E; j++) {
            if(states[i].transitions[j].event!=nullptr) {
                states[i].transitions[j].event->clear();
            }
        }
    }
}

template<int S, int E>
void StateMachine<S, E>::reset_events() {
    for(int i=0; i<S; i++) {
        for(int j=0; j<E; j++) {
            if(states[i].transitions[j].event!=nullptr) {
                states[i].transitions[j].event->reset();
            }
        }
    }
}

}
