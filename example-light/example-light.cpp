#include <iostream>
#include "state_machine.h"

class Context {
public:
    char input;
};

class TurnOn : public sm::Event<Context> {
public:
    bool triggered() {
        if(context->input=='1') {
            std::cout << "switch on" << std::endl;
            return true;
        }

        return false;
    }
};

class TurnOff : public sm::Event<Context> {
public:
    bool triggered() {
        if(context->input=='2') {
            std::cout << "switch off" << std::endl;
            return true;
        }

        return false;
    }
};

class On : public sm::State<Context> {
    void enter() {
        std::cout << "enter On state" << std::endl;
    }

    void execute() {
        std::cout << "execute On state" << std::endl;
    }

    void exit() {
        std::cout << "exit On state" << std::endl;
    }
};

class Off : public sm::State<Context> {
    void enter() {
        std::cout << "enter Off state" << std::endl;
    }

    void execute() {
        std::cout << "execute Off state" << std::endl;
    }

    void exit() {
        std::cout << "exit Off state" << std::endl;
    }
};

int main() {

    TurnOn turn_on;
    TurnOff turn_off;
    On on;
    Off off;

    Context context;
    sm::StateMachine<2, 2, Context> sm(&on, &context);

    sm.transit(&on, &off, &turn_off);
    sm.transit(&off, &on, &turn_on);
    sm.start();

    while(true) {
        std::cin >> context.input;

        sm.update();
    }
}
