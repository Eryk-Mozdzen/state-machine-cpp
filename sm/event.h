#pragma once

namespace sm {

class Event {
    bool is_triggered;

protected:
    Event();
    void trigger();

public:
    bool isTriggered() const;

    template <int S, int E>
    friend class StateMachine;
};

}
