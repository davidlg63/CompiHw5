

#include "CodeGenerator.h"
#include "Symbols.h"
#include "SymbolTableManager.h"
#include <iostream>
using namespace std;



 void CodeGenerator::generateAdditionCode(const retType* firstNum, const retType* secondNum, const retType* result, const string& regNum)
{
     DoAction(regNum, firstNum->reg, secondNum->reg, "add");
}

void CodeGenerator::generateSubtractionCode(const retType* firstNum, const retType* secondNum, const retType* result, const string& regNum)
{
     DoAction(regNum, firstNum->reg, secondNum->reg, "sub");
}

void CodeGenerator::generateDivisionCode(const retType *firstNum, const retType *secondNum, const retType *result, const string& regNum)
{
     generateDivideByZeroErrorCheckCodeAndExitIfYes(secondNum);
     DoAction(regNum, firstNum->reg, secondNum->reg, "sdiv");
}

void CodeGenerator::generateMultiplicationCode(const retType *firstNum, const retType *secondNum, const retType *result, const string& regNum)
{
     DoAction(regNum, firstNum->reg, secondNum->reg, "mul");
}

void CodeGenerator::DoAction(const string& resultReg, const string& firstReg, const string& secondReg, const string& action)
{
    string code = resultReg + " = "+ action + " i32 " + firstReg + ", " + secondReg;
    CodeBuffer::instance().emit(code);
}

void CodeGenerator::generateIntByteCreationCode(const string &reg, const string &value) {
    string code = reg + "=" + "add i32 0, " + value;
    CodeBuffer::instance().emit(code);
}

void CodeGenerator::generateBoolNot(const string &resultReg, const string &expressionReg) {
    //Inverts the value of expressionReg, the addition is modulo 2 because the type is i1.
    string code = resultReg + " = add i1 1, " + expressionReg;
    CodeBuffer::instance().emit(code);
}

void CodeGenerator::generateStandardLibraryFunctionsDeclaration() {
    CodeBuffer::instance().emit("declare i32 @printf(i8*, ...)");
    CodeBuffer::instance().emit("declare void @exit(i32)");
}

void CodeGenerator::generatePrintFunctions() {
    string printi_code = "define void @printi(i32) {\n"
                         "    %spec_ptr = getelementptr [4 x i8], [4 x i8]* @.int_specifier, i32 0, i32 0\n"
                         "    call i32 (i8*, ...) @printf(i8* %spec_ptr, i32 %0)\n"
                         "    ret void\n"
                         "}";

    string print_code = "define void @print(i8*) {\n"
                        "    %spec_ptr = getelementptr [4 x i8], [4 x i8]* @.str_specifier, i32 0, i32 0\n"
                        "    call i32 (i8*, ...) @printf(i8* %spec_ptr, i8* %0)\n"
                        "    ret void\n"
                        "}";
    CodeBuffer& codeBuffer = CodeBuffer::instance();
    codeBuffer.emit(R"(@.int_specifier = constant [4 x i8] c"%d\0A\00")");
    codeBuffer.emit(R"(@.str_specifier = constant [4 x i8] c"%s\0A\00")");
    codeBuffer.emit(printi_code);
    codeBuffer.emit(print_code);
}

void CodeGenerator::generateCallToFuncWithoutArguments(call2Fun* func) {
     string func_type = SymbolTableManager::ConvertTypeToString(func->type);
     string result_reg = RegisterGenerator::getRegister();
     func->reg = result_reg;
     string code = result_reg + " = " + "call " + func_type + " @" + func->name + "()";
     CodeBuffer::instance().emit(code);
}

void CodeGenerator::generateCallToFuncWithArguments(call2Fun *func, const expressionList *params) {
    string func_type = SymbolTableManager::ConvertTypeToString(func->type);
    string code;
    if (TYPE_VOID != func->type)
    {
        string result_reg = RegisterGenerator::getRegister();
        code += result_reg + " = ";
        func->reg = result_reg;
    }
    code += "call " + func_type + " @" + func->name +"(";
    if("print" == func->name) //print is a special function that accepts and i8* this is why we need to address it seperatly.
    {
        code += "i8* " + params->registersList[0];
    }
    else {
        /*Insert the params*/
        for (int i = 0; i < params->registersList.size(); i++) {
            code += "i32 " + params->registersList[i];
            if(i < params->registersList.size() - 1)
            {
                code += ", ";
            }
        }
    }
    code += ")"; //Any way we need to close the brackets of the params.
    CodeBuffer::instance().emit(code);
}

void CodeGenerator::generateStringCode(retType *result, const String* str) {
    string tmp = str->value.substr(1, str->value.size() - 2);
    string reg = RegisterGenerator::getRegister();
    result->reg = reg;
    //BUG: not raw
    string raw_reg = RegisterGenerator::getRawRegister(reg);
    string code = "@" + raw_reg + " = constant [" + to_string(tmp.size() + 1) + " x i8] c\"" + tmp + "\\00\"";
    CodeBuffer::instance().emitGlobal(code);
    string size = to_string(tmp.size() + 1);
    code =  reg + " = getelementptr [" + size + "x i8], [" + size +" x i8]* @" + raw_reg + ", i32 0, i32 0";
    CodeBuffer::instance().emit(code);
}

void CodeGenerator::generateDivideByZeroErrorCheckCodeAndExitIfYes(const retType* num) {
     CodeBuffer& instance = CodeBuffer::instance();
     instance.emitGlobal(R"(@.divideByZeroErrorMessage = constant [23 x i8] c"Error division by zero\00")");
     string is_zero_reg = RegisterGenerator::getRegister();
     string check_is_zero = is_zero_reg + " = icmp eq i32 0, " + num->reg;
     instance.emit(check_is_zero);
     int loc = instance.emit("br i1 " + is_zero_reg + ", label @" + ", label @");
     string ifEqual = instance.genLabel();

     string divideByZeroMsgReg = RegisterGenerator::getRegister();
     string getDivideByZeroMsgReg =
             divideByZeroMsgReg + " = getelementptr [23 x i8], [23 x i8]* @.divideByZeroErrorMessage, i32 0, i32 0";
     instance.emit(getDivideByZeroMsgReg);

     string callPrint = "call void @print(i8* " + divideByZeroMsgReg + ")";
     instance.emit(callPrint);

     instance.emit("call void @exit(i32 1)");

     int dummyBranchToNotEq = instance.emit("br label @");
     string ifNotEqual = instance.genLabel();
     instance.bpatch(CodeBuffer::makelist({dummyBranchToNotEq, FIRST}), ifNotEqual);
     instance.bpatch(CodeBuffer::makelist({loc, FIRST}), ifEqual);
     instance.bpatch(CodeBuffer::makelist({loc, SECOND}), ifNotEqual);
}

string CodeGenerator::generateFunctionCallCode(const call2Fun *func, const Id *func_id, const expressionList *params) {
    string func_type = SymbolTableManager::ConvertTypeToLlvmType(func->type);
    string code, func_reg;
    if (TYPE_VOID == func->type)
    {
        code = "call " + func_type + " @" + func->name + "(";
    }
    else
    {
        func_reg = RegisterGenerator::getRegister();
        code = func_reg + " = " + "call " + func_type + " @" + func->name + "(";
    }
    for(int i = 0; i < params->exprList.size(); i++)
    {
        string param_type = SymbolTableManager::ConvertTypeToLlvmType(params->exprList[i]);
        code += param_type + " " + params->registersList[i];
        if(i < params->exprList.size() - 1)
        {
            code += ", ";
        }
    }
    code += ")";
    CodeBuffer::instance().emit(code);
    return func_reg;
}

string CodeGenerator::generateUpdateRegisterOnStackCode(const int offset, const string& stackPointer) {
    string new_reg = RegisterGenerator::getRegister();
    string code = new_reg + " = getelementptr [50 x i32], [50 x i32]* " + stackPointer + ", i32 0 , i32 " + to_string(offset);
    CodeBuffer::instance().emit(code);
    return new_reg;
}

void CodeGenerator::generateBoolExpressionBackPatchLabels(std::vector<std::pair<int, BranchLabelIndex>>& trueList,
                                           std::vector<std::pair<int, BranchLabelIndex>>& falseList,
                                           const string& reg_to_assign)
{
     CodeBuffer& codeBuffer = CodeBuffer::instance();

     int trueLabelLine = codeBuffer.emit("br label @");
     auto trueLabelList = CodeBuffer::makelist({trueLabelLine, FIRST});
     string trueLabel = codeBuffer.genLabel();
     int nextLabelAfterIfLine = codeBuffer.emit("br label @");
     string falseLabel = codeBuffer.genLabel();
     int nextLabelAfterFalseLine = codeBuffer.emit("br label @");
     string nextLabel = codeBuffer.genLabel();
     auto nextLabelList = CodeBuffer::merge(CodeBuffer::makelist({nextLabelAfterIfLine, FIRST}),
                                            CodeBuffer::makelist({nextLabelAfterFalseLine,FIRST}));
     codeBuffer.bpatch(trueLabelList, trueLabel);
     codeBuffer.bpatch(nextLabelList, nextLabel);
     codeBuffer.emit(reg_to_assign +" = phi i32 [1" +", %" + trueLabel + "] , [0" + " , %" + falseLabel+"]");
     codeBuffer.bpatch(trueList, trueLabel);
     codeBuffer.bpatch(falseList, falseLabel);
}

void CodeGenerator::generateInitNewVar(const string& new_reg, const string& reg)
{
    string code = new_reg + " = add i32 "+ reg + ", 0";
    CodeBuffer::instance().emit(code);
}

string CodeGenerator::generateTruncRegisterCode(const string &reg_to_trunc) {
    string truncReg = RegisterGenerator::getRegister();
    string truncCode = truncReg + " =  trunc i32 " +  reg_to_trunc+ " to i1";
    CodeBuffer::instance().emit(truncCode);
    return truncReg;
}

std::string CodeGenerator::generateConvertFromi1Toi32(const std::string& reg) {
     string freshReg = RegisterGenerator::getRegister();
     string code = freshReg + " = zext i1 " + reg + " to i32";
     CodeBuffer::instance().emit(code);
     return freshReg;
}

