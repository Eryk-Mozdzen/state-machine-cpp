#pragma once

#include "event.h"

namespace sm {

template<int MAX_EVENTS>
class State {
    struct Transition {
        Event *trigger;
        State<MAX_EVENTS> *next;
    };

    Transition transitions[MAX_EVENTS];

    void clear_all();

public:
    State();
    void transit(State<MAX_EVENTS> *to, Event *trigger);
    static void handle(State<MAX_EVENTS> **st);

    virtual void on_enter() {};
    virtual void on_execute() {};
    virtual void on_exit() {};
};

template<int MAX_EVENTS>
State<MAX_EVENTS>::State() {
    for(int i=0; i<MAX_EVENTS; i++) {
        transitions[i].trigger = nullptr;
        transitions[i].next = nullptr;
    }
}

template<int MAX_EVENTS>
void State<MAX_EVENTS>::transit(State<MAX_EVENTS> *to, Event *trigger) {
    for(int i=0; i<MAX_EVENTS; i++) {
        if(transitions[i].next==nullptr) {
            transitions[i].trigger = trigger;
            transitions[i].next = to;
            return;
        }
    }
}

template<int MAX_EVENTS>
void State<MAX_EVENTS>::handle(State<MAX_EVENTS> **st) {
    Transition *transition = nullptr;

    for(int i=0; i<MAX_EVENTS; i++) {
        if((*st)->transitions[i].trigger==nullptr) {
            return;
        }

        if((*st)->transitions[i].trigger->isTriggered()) {
            transition = &(*st)->transitions[i];
            break;
        }
    }

    if(transition==nullptr) {
        return;
    }

    (*st)->on_exit();
    *st = transition->next;
    (*st)->clear_all();
    (*st)->on_enter();
}

template<int MAX_EVENTS>
void State<MAX_EVENTS>::clear_all() {
    for(int i=0; i<MAX_EVENTS; i++) {
        if(transitions[i].trigger==nullptr) {
            return;
        }

        transitions[i].trigger->is_triggered = false;
    }
}

}
