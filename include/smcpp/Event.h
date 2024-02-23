#pragma once

#include "smcpp/internal/EventBase.h"

namespace smcpp {

template<typename C>
class Event : public internal::EventBase {
protected:
    const C &context;

public:
    Event(const C &context) : context{context} {}
};

}
