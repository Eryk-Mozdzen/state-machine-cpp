#pragma once

namespace sm {

class Event {
    bool is_triggered;

protected:
    Event() : is_triggered{false} {}
    void trigger() {is_triggered = true;}

public:
    bool isTriggered() const {return is_triggered;}

    template <int S, int E>
    friend class StateMachine;
};

}
