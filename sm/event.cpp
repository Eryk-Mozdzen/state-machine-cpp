#include "event.h"

namespace sm {

Event::Event() : is_triggered{false} {

}

void Event::trigger() {
    is_triggered = true;
}

bool Event::isTriggered() const {
    return is_triggered;
}

}
