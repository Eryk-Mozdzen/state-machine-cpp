#pragma once

namespace smcpp::internal {

class EventBase {
public:
    virtual bool triggered() = 0;
    virtual void action() {}
    virtual void clear() {}
    virtual void reset() {}
};

}
