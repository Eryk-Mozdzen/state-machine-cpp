#include <iostream>

#include "smcpp/Event.h"
#include "smcpp/State.h"
#include "smcpp/StateMachine.h"

namespace example {

class Context {
public:
    char input;
};

class TurnOnEvent : public smcpp::Event<Context> {
    using smcpp::Event<Context>::Event;

public:
    bool triggered() {
        if(context.input=='1') {
            std::cout << "switch on" << std::endl;
            return true;
        }

        return false;
    }
};

class TurnOffEvent : public smcpp::Event<Context> {
    using smcpp::Event<Context>::Event;

public:
    bool triggered() {
        if(context.input=='2') {
            std::cout << "switch off" << std::endl;
            return true;
        }

        return false;
    }
};

class OnState : public smcpp::State<Context> {
    using smcpp::State<Context>::State;

    void enter() {
        std::cout << "enter On state" << std::endl;
    }

    void execute() {
        std::cout << "execute On state" << std::endl;

        std::cin >> context.input;
    }

    void exit() {
        std::cout << "exit On state" << std::endl;
    }
};

class OffState : public smcpp::State<Context> {
    using smcpp::State<Context>::State;

    void enter() {
        std::cout << "enter Off state" << std::endl;
    }

    void execute() {
        std::cout << "execute Off state" << std::endl;

        std::cin >> context.input;
    }

    void exit() {
        std::cout << "exit Off state" << std::endl;
    }
};

}

int main() {
    example::Context context;
    example::TurnOnEvent turn_on(context);
    example::TurnOffEvent turn_off(context);
    example::OnState on(context);
    example::OffState off(context);

    smcpp::StateMachine<2, 1> sm;

    sm.transit(&on, &off, &turn_off);
    sm.transit(&off, &on, &turn_on);

    sm.start(&on);

    while(true) {
        sm.update();
    }
}
