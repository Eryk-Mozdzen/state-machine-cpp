#pragma once

namespace sm {

template<typename T>
class Event {
protected:
    T *context;

public:
    Event() : context{nullptr} {}

    void setContext(T *ctx) {
        context = ctx;
    }

    virtual bool triggered() = 0;
    virtual void clear() {}
    virtual void reset() {}
};

}
