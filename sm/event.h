#pragma once

namespace sm {

class Event {
    bool is_triggered;

    virtual void on_clear() {}

protected:
    Event() : is_triggered{false} {

    }

    void trigger() {
        is_triggered = true;
    }

public:
    bool isTriggered() const {
        return is_triggered;
    }

    void clear() {
        on_clear();
        is_triggered = false;
    }
};

}
