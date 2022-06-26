
#ifndef HW5_CODEGENERATOR_H
#define HW5_CODEGENERATOR_H

#include "Symbols.h"
#include "bp.hpp"
#include "RegisterGenerator.h"
using namespace std;
class CodeGenerator {

public:
    static void
    generateAdditionCode(const retType *firstNum, const retType *secondNum, const retType *result, string regNum);

    static void
    generateSubtractionCode(const retType *firstNum, const retType *secondNum, const retType *result, string regNum);

    static void
    generateMultiplicationCode(const retType *firstNum, const retType *secondNum, const retType *result, const string& regNum);

    static void
    generateDivisionCode(const retType *firstNum, const retType *secondNum, const retType *result, const string& regNum);

    static void DoAction(const string& resultReg, const string& firstReg, const string& secondReg, const string& action);

    //Code that assigns value to register reg
    static void generateIntByteCreationCode(const std::string &reg, const std::string &value);

    static void generateBoolNot(const std::string& resultReg, const std::string& expressionReg);

    static void generateStandardLibraryFunctionsDeclaration();

    static void generatePrintFunctions();

    static void generateCallToFuncWithoutArguments(call2Fun* func);

    static void generateCallToFuncWithArguments(call2Fun* func, const expressionList* params);

    static void generateStringCode(retType* result_exp, const String* str);
};


#endif //HW5_CODEGENERATOR_H
