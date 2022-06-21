//
// Created by User on 6/18/2022.
//

#include "CodeGenerator.h"
#include "bp.hpp"

using namespace std;

void CodeGenerator::generateIntByteCreationCode(const string &reg, const string &value) {
    string code = reg + "=" + "add i32 0, " + value;
    CodeBuffer::instance().emit(code);
}
