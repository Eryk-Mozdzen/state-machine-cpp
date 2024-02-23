#pragma once

#include "smcpp/internal/StateBase.h"

namespace smcpp {

template<typename C>
class State : public internal::StateBase {
protected:
    C &context;

public:
    State(C &context) : context{context} {}
};

}
