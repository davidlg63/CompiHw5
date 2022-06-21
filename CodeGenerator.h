//
// Created by User on 6/18/2022.
//

#ifndef HW5_CODEGENERATOR_H
#define HW5_CODEGENERATOR_H

#include "Symbols.h"

class CodeGenerator{

public:
    static void generateAdditionCode(const retType* firstNum, const retType* secondNum, const retType* result);
    static void generateSubtractionCode(const retType* firstNum, const retType* secondNum, const retType* result);
    static void generateMultiplicationCode(const retType* firstNum, const retType* secondNum, const retType* result);
    static void generateDivisionCode(const retType* firstNum, const retType* secondNum, const retType* result);
    static void generateIntByteCreationCode(const std::string& reg, const std::string& value);
};


#endif //HW5_CODEGENERATOR_H
