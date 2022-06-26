

#include "CodeGenerator.h"
#include "Symbols.h"
#include "SymbolTableManager.h"
using namespace std;



 void CodeGenerator::generateAdditionCode(const retType* firstNum, const retType* secondNum, const retType* result, string regNum)
{
    string code;
    if (firstNum->type == Type_::TYPE_INT && secondNum->type ==Type_::TYPE_BYTE)
    {
        string reg2Int = RegisterGenerator::getRegister();
        string castCode = "%t" + reg2Int + " = zext i8 %t" + secondNum->reg +" to i32";
        CodeBuffer::instance().emit(castCode);
        DoAction(regNum,firstNum->reg, reg2Int,  "add");

    }
    else if (firstNum->type == Type_::TYPE_BYTE  && secondNum->type ==Type_::TYPE_INT)
    {
        string reg1Int = RegisterGenerator::getRegister();
        string castCode = "%t" + reg1Int + " = zext i8 %t" + secondNum->reg +" to i32";
        CodeBuffer::instance().emit(castCode);
        DoAction(regNum,reg1Int, secondNum->reg, "add");
    }
    else if (firstNum->type == Type_::TYPE_BYTE  && secondNum->type ==Type_::TYPE_BYTE)
    {
        string reg1Int = RegisterGenerator::getRegister();
        string reg2Int = RegisterGenerator::getRegister();
        string castCode = "%t" + reg1Int + " = zext i8 %t" + secondNum->reg +" to i32";
        CodeBuffer::instance().emit(castCode);
        castCode = "%t" + reg2Int + " = zext i8 %t" + secondNum->reg +" to i32";
        CodeBuffer::instance().emit(castCode);
        DoAction(regNum,reg1Int, reg2Int, "add");
    }
    else
        DoAction(regNum, firstNum->reg, secondNum->reg, "add");
}

void CodeGenerator::generateSubtractionCode(const retType* firstNum, const retType* secondNum, const retType* result, string regNum)
{
    string code;
    if (firstNum->type == Type_::TYPE_INT && secondNum->type ==Type_::TYPE_BYTE)
    {
        string reg2Int = RegisterGenerator::getRegister();
        string castCode = "%t" + reg2Int + " = zext i8 %t" + secondNum->reg +" to i32";
        CodeBuffer::instance().emit(castCode);
        DoAction(regNum,firstNum->reg, reg2Int,  "sub");

    }
    else if (firstNum->type == Type_::TYPE_BYTE  && secondNum->type ==Type_::TYPE_INT)
    {
        string reg1Int = RegisterGenerator::getRegister();
        string castCode = "%t" + reg1Int + " = zext i8 %t" + secondNum->reg +" to i32";
        CodeBuffer::instance().emit(castCode);
        DoAction(regNum,reg1Int, secondNum->reg, "sub");;
    }
    else if (firstNum->type == Type_::TYPE_BYTE  && secondNum->type ==Type_::TYPE_BYTE)
    {
        string reg1Int = RegisterGenerator::getRegister();
        string reg2Int = RegisterGenerator::getRegister();
        string castCode = "%t" + reg1Int + " = zext i8 %t" + secondNum->reg +" to i32";
        CodeBuffer::instance().emit(castCode);
        castCode = "%t" + reg2Int + " = zext i8 %t" + secondNum->reg +" to i32";
        CodeBuffer::instance().emit(castCode);
        DoAction(regNum,reg1Int, reg2Int, "sub");
    }
    else
        DoAction(regNum, firstNum->reg, secondNum->reg, "sub");
}

void CodeGenerator::generateDivisionCode(const retType *firstNum, const retType *secondNum, const retType *result, const string& regNum)
{
    /************************************ add devide by zero error***********************************/
    string code;
    if (firstNum->type == Type_::TYPE_INT && secondNum->type ==Type_::TYPE_BYTE)
    {
        string reg2Int = RegisterGenerator::getRegister();
        string castCode = "%t" + reg2Int + " = zext i8 %t" + secondNum->reg +" to i32";
        CodeBuffer::instance().emit(castCode);
        DoAction(regNum,firstNum->reg, reg2Int,  "sdiv");

    }
    else if (firstNum->type == Type_::TYPE_BYTE  && secondNum->type ==Type_::TYPE_INT)
    {
        string reg1Int = RegisterGenerator::getRegister();
        string castCode = "%t" + reg1Int + " = zext i8 %t" + secondNum->reg +" to i32";
        CodeBuffer::instance().emit(castCode);
        DoAction(regNum,reg1Int, secondNum->reg, "sdiv");
    }
    else if (firstNum->type == Type_::TYPE_BYTE  && secondNum->type ==Type_::TYPE_BYTE)
    {
        string reg1Int = RegisterGenerator::getRegister();
        string reg2Int = RegisterGenerator::getRegister();
        string castCode = "%t" + reg1Int + " = zext i8 %t" + secondNum->reg +" to i32";
        CodeBuffer::instance().emit(castCode);
        castCode = "%t" + reg2Int + " = zext i8 %t" + secondNum->reg +" to i32";
        CodeBuffer::instance().emit(castCode);
        DoAction(regNum,reg1Int, reg2Int, "sdiv");
    }
    else
        DoAction(regNum, firstNum->reg, secondNum->reg, "sdiv");
}

void CodeGenerator::generateMultiplicationCode(const retType *firstNum, const retType *secondNum, const retType *result, const string& regNum)
{
    string code;
    if (firstNum->type == Type_::TYPE_INT && secondNum->type ==Type_::TYPE_BYTE)
    {
        string reg2Int = RegisterGenerator::getRegister();
        string castCode = "%t" + reg2Int + " = zext i8 %t" + secondNum->reg +" to i32";
        CodeBuffer::instance().emit(castCode);
        DoAction(regNum,firstNum->reg, reg2Int,  "mul");

    }
    else if (firstNum->type == Type_::TYPE_BYTE  && secondNum->type ==Type_::TYPE_INT)
    {
        string reg1Int = RegisterGenerator::getRegister();
        string castCode = "%t" + reg1Int + " = zext i8 %t" + secondNum->reg +" to i32";
        CodeBuffer::instance().emit(castCode);
        DoAction(regNum,reg1Int, secondNum->reg, "mul");
    }
    else if (firstNum->type == Type_::TYPE_BYTE  && secondNum->type ==Type_::TYPE_BYTE)
    {
        string reg1Int = RegisterGenerator::getRegister();
        string reg2Int = RegisterGenerator::getRegister();
        string castCode = "%t" + reg1Int + " = zext i8 %t" + secondNum->reg +" to i32";
        CodeBuffer::instance().emit(castCode);
        castCode = "%t" + reg2Int + " = zext i8 %t" + secondNum->reg +" to i32";
        CodeBuffer::instance().emit(castCode);
        DoAction(regNum,reg1Int, reg2Int, "mul");
    }
    else
        DoAction(regNum, firstNum->reg, secondNum->reg, "mul");
}

void CodeGenerator::DoAction(const string& resultReg, const string& firstReg, const string& secondReg, const string& action)
{
    string code = "%t" + resultReg + " = "+ action + " i32 %t" +firstReg + ", %t" + secondReg;
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
    string code = "@" + reg + " = constant [" + to_string(tmp.size() + 1) + " x i8] c\"" + tmp + "\\00\"";
    CodeBuffer::instance().emitGlobal(code);
    string size = to_string(tmp.size() + 1);
    code =  reg + " = getelementptr [" + size + "x i8], [" + size +" x i8]* @" + reg + ", i32 0, i32 0";
    CodeBuffer::instance().emit(code);
}

