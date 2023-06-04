#pragma once

#include "event.h"
#include "state.h"

namespace sm {

template<int S, int E>
class StateMachine {
    struct StateTransition;

    struct Transition {
        Event *event;
        StateTransition *next;
    };

    struct StateTransition {
        State *state;
        Transition transitions[E];
    };

    StateTransition states[S];
    StateTransition *current;

    void clear();

public:
    StateMachine(State *st);
    void transit(State *from, State *to, Event *event);
    void start();
    void update();
};

template<int S, int E>
StateMachine<S, E>::StateMachine(State *st) : current{nullptr} {
    for(int i=0; i<S; i++) {
        states[i].state = nullptr;

        for(int j=0; j<E; j++) {
            states[i].transitions[j].event = nullptr;
            states[i].transitions[j].next = nullptr;
        }
    }

    if(st==nullptr) {
        return;
    }

    states[0].state = st;
    current = &states[0];
}

template<int S, int E>
void StateMachine<S, E>::transit(State *from, State *to, Event *event) {
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

    if(from_transition==nullptr || to_transition==nullptr || event==nullptr) {
        return;
    }

    for(int i=0; i<E; i++) {
        if(from_transition->transitions[i].next==nullptr) {
            from_transition->transitions[i].event = event;
            from_transition->transitions[i].next = to_transition;
        }
    }
}

template<int S, int E>
void StateMachine<S, E>::start() {
    if(current==nullptr) {
        return;
    }

    current->state->enter();
}

template<int S, int E>
void StateMachine<S, E>::update() {
    if(current==nullptr) {
        return;
    }

    for(int i=0; i<E; i++) {
        if(current->transitions[i].event!=nullptr) {
            if(current->transitions[i].event->is_triggered) {
                current->state->exit();
                current = current->transitions[i].next;
                current->state->enter();
                break;
            }
        }
    }

    clear();

    current->state->execute();
}

template<int S, int E>
void StateMachine<S, E>::clear() {
    for(int i=0; i<S; i++) {
        if(states[i].state!=nullptr) {
            for(int j=0; j<E; j++) {
                if(states[i].transitions[j].event!=nullptr) {
                    states[i].transitions[j].event->is_triggered = false;
                }
            }
        }
    }
}

}
