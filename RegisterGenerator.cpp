//
// Created by User on 6/18/2022.
//

#include "RegisterGenerator.h"

using namespace std;

RegisterGenerator::RegisterGenerator() : _current_reg_prefix("t"), _current_reg_number(0)
{}

string RegisterGenerator::getRegister() {
    if (INT_MAX == _current_reg_number)
    {
        _current_reg_prefix += 't';
        _current_reg_number = 0;
    }
    return _current_reg_prefix + std::to_string(_current_reg_number++);
}

