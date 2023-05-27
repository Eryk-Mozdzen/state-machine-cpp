#pragma once

namespace sm {

class Event {
    bool is_triggered;

    virtual void on_trigger() {};

public:
    Event();

    void trigger();
    bool isTriggered() const;
    void clear();
};

Event::Event() : is_triggered{false} {

}

void Event::trigger() {
    on_trigger();

    is_triggered = true;
}

bool Event::isTriggered() const {
    return is_triggered;
}

void Event::clear() {
    is_triggered = false;
}

}
