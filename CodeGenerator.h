
#ifndef HW5_CODEGENERATOR_H
#define HW5_CODEGENERATOR_H

#include "Symbols.h"
#include "bp.hpp"
#include "RegisterGenerator.h"
class CodeGenerator {

    static void generateDivideByZeroErrorCheckCodeAndExitIfYes(const retType* num);

public:
    static void
    generateAdditionCode(const retType *firstNum, const retType *secondNum, const retType *result, const std::string& regNum);

    static void
    generateSubtractionCode(const retType *firstNum, const retType *secondNum, const retType *result, const std::string& regNum);

    static void
    generateMultiplicationCode(const retType *firstNum, const retType *secondNum, const retType *result, const std::string& regNum);

    static void
    generateDivisionCode(const retType *firstNum, const retType *secondNum, const retType *result, const std::string& regNum);

    static void DoAction(const string& resultReg, const string& firstReg, const string& secondReg, const std::string& action);

    //Code that assigns value to register reg
    static void generateIntByteCreationCode(const std::string &reg, const std::string &value);

    static void generateBoolNot(const std::string& resultReg, const std::string& expressionReg);

    static void generateStandardLibraryFunctionsDeclaration();

    static void generatePrintFunctions();

    static void generateCallToFuncWithoutArguments(call2Fun* func);

    static void generateCallToFuncWithArguments(call2Fun* func, const expressionList* params);

    static void generateStringCode(retType* result_exp, const String* str);

    static void generateFunctionCallCode(const call2Fun* func, const Id* func_id, const expressionList* params);

    static std::string generateUpdateRegisterOnStackCode(int offset, const std::string& stackPointer);

    static void generateBoolExpressionBackPatchLabels(std::vector<std::pair<int, BranchLabelIndex>>& trueList,
                                                      std::vector<std::pair<int, BranchLabelIndex>>& falseList,
                                                      const std::string& reg_to_assign);
    static void generateInitNewVar(const std::string& new_reg, const std::string& reg);

    //generates code the truncs the register nd returns the new created register.
    static std::string generateTruncRegisterCode(const std::string& reg_to_trunc);
};


#endif //HW5_CODEGENERATOR_H
