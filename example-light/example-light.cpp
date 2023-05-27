#include <iostream>
#include "state_machine.h"

class TurnOn : public sm::Event {
    void on_trigger() override {
        std::cout << "switch on" << std::endl;
    }
};

class TurnOff : public sm::Event {
    void on_trigger() override {
        std::cout << "switch off" << std::endl;
    }
};

class On : public sm::State<5> {
    void on_enter() override {
        std::cout << "enter On state" << std::endl;
    }
    void on_execute() override {
        std::cout << "execute On state" << std::endl;
    }
    void on_exit() override {
        std::cout << "exit On state" << std::endl;
    }
};

class Off : public sm::State<5> {
    void on_enter() override {
        std::cout << "enter Off state" << std::endl;
    }
    void on_execute() override {
        std::cout << "execute Off state" << std::endl;
    }
    void on_exit() override {
        std::cout << "exit Off state" << std::endl;
    }
};

int main() {

    TurnOn turn_on;
    TurnOff turn_off;
    On on;
    Off off;

    on.transit(&off, &turn_off);
    off.transit(&on, &turn_on);

    sm::StateMachine<5> sm(&on);

    while(true) {
        char input;
        std::cin >> input;

        switch(input) {
            case '1': turn_on.trigger(); break;
            case '2': turn_off.trigger(); break;
        }

        sm.update();
    }
}
