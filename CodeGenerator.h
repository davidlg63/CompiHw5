//
// Created by User on 6/18/2022.
//

#ifndef HW5_CODEGENERATOR_H
#define HW5_CODEGENERATOR_H

#include "Symbols.h"
#include "bp.hpp"
#include "RegisterGenerator.h"
using namespace std;
class CodeGenerator{

public:
    static void generateAdditionCode(const retType* firstNum, const retType* secondNum, const retType* result, string regNum);
    static void generateSubtractionCode(const retType* firstNum, const retType* secondNum, const retType* result, string regNum);
    static void generateMultiplicationCode(const retType* firstNum, const retType* secondNum, const retType* result, string regNum);
    static void generateDivisionCode(const retType* firstNum, const retType* secondNum, const retType* result, string regNum);
    static void DoAction(string resultReg, string firstReg, string secondReg, string action);
};


#endif //HW5_CODEGENERATOR_H
