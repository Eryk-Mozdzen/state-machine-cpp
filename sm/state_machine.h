#pragma once

#include "event.h"
#include "state.h"

namespace sm {

template<int S, int E, typename T>
class StateMachine {
    struct StateTransition;

    struct Transition {
        Event<T> *event;
        StateTransition *next;

        Transition() : event{nullptr}, next{nullptr} {}
    };

    struct StateTransition {
        State<T> *state;
        Transition transitions[E];

        StateTransition() : state{nullptr} {}
    };

    StateTransition states[S];
    StateTransition *current;
    T *context;

    void clear_events();
    void reset_events();

public:
    StateMachine(State<T> *st, T *ctx=nullptr);
    void transit(State<T> *from, State<T> *to, Event<T> *event);
    void start();
    void update();
};

template<int S, int E, typename T>
StateMachine<S, E, T>::StateMachine(State<T> *st, T *ctx) : current{nullptr}, context{ctx} {
    if(st==nullptr) {
        return;
    }

    states[0].state = st;
    current = &states[0];
}

template<int S, int E, typename T>
void StateMachine<S, E, T>::transit(State<T> *from, State<T> *to, Event<T> *event) {
    if(from==nullptr || to==nullptr || event==nullptr) {
        return;
    }

    StateTransition *from_transition = nullptr;
    StateTransition *to_transition = nullptr;

    for(int i=0; i<S; i++) {
        if(states[i].state==from || states[i].state==nullptr) {
            states[i].state = from;
            states[i].state->setContext(context);
            from_transition = &states[i];
            break;
        }
    }

    for(int i=0; i<S; i++) {
        if(states[i].state==to || states[i].state==nullptr) {
            states[i].state = to;
            states[i].state->setContext(context);
            to_transition = &states[i];
            break;
        }
    }

    if(from_transition==nullptr || to_transition==nullptr) {
        return;
    }

    for(int i=0; i<E; i++) {
        if(from_transition->transitions[i].next==nullptr) {
            from_transition->transitions[i].event = event;
            from_transition->transitions[i].event->setContext(context);
            from_transition->transitions[i].next = to_transition;
            return;
        }
    }
}

template<int S, int E, typename T>
void StateMachine<S, E, T>::start() {
    if(current==nullptr) {
        return;
    }

    current->state->enter();
}

template<int S, int E, typename T>
void StateMachine<S, E, T>::update() {
    if(current==nullptr) {
        return;
    }

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

template<int S, int E, typename T>
void StateMachine<S, E, T>::clear_events() {
    for(int i=0; i<S; i++) {
        for(int j=0; j<E; j++) {
            if(states[i].transitions[j].event!=nullptr) {
                states[i].transitions[j].event->clear();
            }
        }
    }
}

template<int S, int E, typename T>
void StateMachine<S, E, T>::reset_events() {
    for(int i=0; i<S; i++) {
        for(int j=0; j<E; j++) {
            if(states[i].transitions[j].event!=nullptr) {
                states[i].transitions[j].event->reset();
            }
        }
    }
}

}
