#include <iostream>
#include "state.h"

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
        std::cout << "entering On state" << std::endl;
    }
    void on_execute() override {
        std::cout << "light is on" << std::endl;
    }
};

class Off : public sm::State<5> {
    void on_enter() override {
        std::cout << "entering Off state" << std::endl;
    }
};

int main() {

    TurnOn turn_on;
    TurnOff turn_off;
    On on;
    Off off;

    sm::State<5>::link(&on, &off, &turn_off);
    sm::State<5>::link(&off, &on, &turn_on);

    sm::State<5> *current = &on;

    while(true) {
        char input;
        std::cin >> input;

        switch(input) {
            case '1': sm::State<5>::handle(&current, &turn_on); break;
            case '2': sm::State<5>::handle(&current, &turn_off); break;
        }
    }
}
