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
    bool triggered() const {
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
    bool triggered() const {
        if(context.input=='2') {
            std::cout << "switch off" << std::endl;
            return true;
        }

        return false;
    }
};

class BrightState : public smcpp::State<Context> {
    using smcpp::State<Context>::State;

    void enter() {
        std::cout << "enter bright state" << std::endl;
    }

    void execute() {
        std::cout << "execute bright state" << std::endl;
    }

    void exit() {
        std::cout << "exit bright state" << std::endl;
    }
};

class DarkState : public smcpp::State<Context> {
    using smcpp::State<Context>::State;

    void enter() {
        std::cout << "enter dark state" << std::endl;
    }

    void execute() {
        std::cout << "execute dark state" << std::endl;
    }

    void exit() {
        std::cout << "exit dark state" << std::endl;
    }
};

}

int main() {
    example::Context context;
    example::TurnOnEvent on(context);
    example::TurnOffEvent off(context);
    example::BrightState bright(context);
    example::DarkState dark(context);

    smcpp::StateMachine<2, 1> sm;

    sm.transit(&bright, &dark, &off);
    sm.transit(&dark, &bright, &on);

    sm.start(&bright);

    while(true) {
        std::cin >> context.input;

        sm.update();
    }
}
