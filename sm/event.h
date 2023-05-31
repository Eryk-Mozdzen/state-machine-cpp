#pragma once

namespace sm {

class Event {
    bool is_triggered;

protected:
    Event() : is_triggered{false} {}
    void trigger() {is_triggered = true;}

    template <int S, int E>
    friend class StateMachine;
};

}
