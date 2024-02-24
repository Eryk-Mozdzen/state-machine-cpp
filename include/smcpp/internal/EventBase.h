#pragma once

namespace smcpp::internal {

class EventBase {
public:
    virtual bool triggered() const = 0;
    virtual void action() {}
    virtual void reset() {}
};

}
