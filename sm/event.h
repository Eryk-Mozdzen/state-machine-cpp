#pragma once

namespace sm {

class Event {
    bool is_triggered;

    template <int MAX_STATES>
    friend class State;

protected:
    Event();
    void trigger();

public:
    bool isTriggered() const;
};

}
