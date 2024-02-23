#pragma once

namespace smcpp::internal {

class StateBase {
public:
    virtual void enter() {};
    virtual void execute() {};
    virtual void exit() {};
};

}
