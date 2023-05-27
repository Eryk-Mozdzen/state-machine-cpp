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

    virtual void on_enter() {};
    virtual void on_execute() {};
    virtual void on_exit() {};

public:
    State();
    static void link(State<MAX_EVENTS> *from, State<MAX_EVENTS> *to, Event *trigger);
    static void handle(State<MAX_EVENTS> **st, Event *trigger);
};

template<int MAX_EVENTS>
State<MAX_EVENTS>::State() {
    for(int i=0; i<MAX_EVENTS; i++) {
        transitions[i].trigger = nullptr;
        transitions[i].next = nullptr;
    }
}

template<int MAX_EVENTS>
void State<MAX_EVENTS>::link(State<MAX_EVENTS> *from, State<MAX_EVENTS> *to, Event *trigger) {
    for(int i=0; i<MAX_EVENTS; i++) {
        if(from->transitions[i].next==nullptr) {
            from->transitions[i].trigger = trigger;
            from->transitions[i].next = to;
            return;
        }
    }
}

template<int MAX_EVENTS>
void State<MAX_EVENTS>::handle(State<MAX_EVENTS> **st, Event *event) {
    for(int i=0; i<MAX_EVENTS; i++) {
        if((*st)->transitions[i].trigger==event) {
            event->on_trigger();
            (*st)->on_exit();
            *st = (*st)->transitions[i].next;
            (*st)->on_enter();
            return;
        }
    }
}

}
