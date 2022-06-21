//
// Created by User on 6/18/2022.
//

#include "RegisterGenerator.h"

using namespace std;

string RegisterGenerator::getRegisterInternal() {
    if (INT_MAX == _current_reg_number)
    {
        _current_reg_prefix += 't';
        _current_reg_number = 0;
    }
    return _current_reg_prefix + std::to_string(_current_reg_number++);
}

RegisterGenerator &RegisterGenerator::Get() {
    static RegisterGenerator instance;
    return instance;
}

std::string RegisterGenerator::getRegister() {
    return RegisterGenerator::Get().getRegisterInternal();
}

