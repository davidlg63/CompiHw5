//
// Created by User on 6/18/2022.
//

#include "CodeGenerator.h"



 void CodeGenerator::generateAdditionCode(const retType* firstNum, const retType* secondNum, const retType* result, string regNum)
{
    string code;
    if (firstNum->type == Type_::TYPE_INT && secondNum->type ==Type_::TYPE_BYTE)
    {
        string reg2Int = RegisterGenerator::getRegister();
        string castCode = "%t" + reg2Int + " = zext i8 %t" + secondNum->storeReg +" to i32";
        CodeBuffer::instance().emit(castCode);
        DoAction(regNum,firstNum->storeReg, reg2Int,  "add");

    }
    else if (firstNum->type == Type_::TYPE_BYTE  && secondNum->type ==Type_::TYPE_INT)
    {
        string reg1Int = RegisterGenerator::getRegister();
        string castCode = "%t" + reg1Int + " = zext i8 %t" + secondNum->storeReg +" to i32";
        CodeBuffer::instance().emit(castCode);
        DoAction(regNum,reg1Int, secondNum->storeReg, "add");
    }
    else if (firstNum->type == Type_::TYPE_BYTE  && secondNum->type ==Type_::TYPE_BYTE)
    {
        string reg1Int = RegisterGenerator::getRegister();
        string reg2Int = RegisterGenerator::getRegister();
        string castCode = "%t" + reg1Int + " = zext i8 %t" + secondNum->storeReg +" to i32";
        CodeBuffer::instance().emit(castCode);
        castCode = "%t" + reg2Int + " = zext i8 %t" + secondNum->storeReg +" to i32";
        CodeBuffer::instance().emit(castCode);
        DoAction(regNum,reg1Int, reg2Int, "add");
    }
    else
        DoAction(regNum, firstNum->storeReg, secondNum->storeReg, "add");
}

void CodeGenerator::generateSubtractionCode(const retType* firstNum, const retType* secondNum, const retType* result, string regNum)
{
    string code;
    if (firstNum->type == Type_::TYPE_INT && secondNum->type ==Type_::TYPE_BYTE)
    {
        string reg2Int = RegisterGenerator::getRegister();
        string castCode = "%t" + reg2Int + " = zext i8 %t" + secondNum->storeReg +" to i32";
        CodeBuffer::instance().emit(castCode);
        DoAction(regNum,firstNum->storeReg, reg2Int,  "sub");

    }
    else if (firstNum->type == Type_::TYPE_BYTE  && secondNum->type ==Type_::TYPE_INT)
    {
        string reg1Int = RegisterGenerator::getRegister();
        string castCode = "%t" + reg1Int + " = zext i8 %t" + secondNum->storeReg +" to i32";
        CodeBuffer::instance().emit(castCode);
        DoAction(regNum,reg1Int, secondNum->storeReg, "sub");;
    }
    else if (firstNum->type == Type_::TYPE_BYTE  && secondNum->type ==Type_::TYPE_BYTE)
    {
        string reg1Int = RegisterGenerator::getRegister();
        string reg2Int = RegisterGenerator::getRegister();
        string castCode = "%t" + reg1Int + " = zext i8 %t" + secondNum->storeReg +" to i32";
        CodeBuffer::instance().emit(castCode);
        castCode = "%t" + reg2Int + " = zext i8 %t" + secondNum->storeReg +" to i32";
        CodeBuffer::instance().emit(castCode);
        DoAction(regNum,reg1Int, reg2Int, "sub");
    }
    else
        DoAction(regNum, firstNum->storeReg, secondNum->storeReg, "sub");
}

void CodeGenerator::generateDivisionCode(const retType *firstNum, const retType *secondNum, const retType *result, string regNum)
{
    /************************************ add devide by zero error***********************************/
    string code;
    if (firstNum->type == Type_::TYPE_INT && secondNum->type ==Type_::TYPE_BYTE)
    {
        string reg2Int = RegisterGenerator::getRegister();
        string castCode = "%t" + reg2Int + " = zext i8 %t" + secondNum->storeReg +" to i32";
        CodeBuffer::instance().emit(castCode);
        DoAction(regNum,firstNum->storeReg, reg2Int,  "sdiv");

    }
    else if (firstNum->type == Type_::TYPE_BYTE  && secondNum->type ==Type_::TYPE_INT)
    {
        string reg1Int = RegisterGenerator::getRegister();
        string castCode = "%t" + reg1Int + " = zext i8 %t" + secondNum->storeReg +" to i32";
        CodeBuffer::instance().emit(castCode);
        DoAction(regNum,reg1Int, secondNum->storeReg, "sdiv");
    }
    else if (firstNum->type == Type_::TYPE_BYTE  && secondNum->type ==Type_::TYPE_BYTE)
    {
        string reg1Int = RegisterGenerator::getRegister();
        string reg2Int = RegisterGenerator::getRegister();
        string castCode = "%t" + reg1Int + " = zext i8 %t" + secondNum->storeReg +" to i32";
        CodeBuffer::instance().emit(castCode);
        castCode = "%t" + reg2Int + " = zext i8 %t" + secondNum->storeReg +" to i32";
        CodeBuffer::instance().emit(castCode);
        DoAction(regNum,reg1Int, reg2Int, "sdiv");
    }
    else
        DoAction(regNum, firstNum->storeReg, secondNum->storeReg, "sdiv");
}

void CodeGenerator::generateMultiplicationCode(const retType *firstNum, const retType *secondNum, const retType *result, string regNum)
{
    string code;
    if (firstNum->type == Type_::TYPE_INT && secondNum->type ==Type_::TYPE_BYTE)
    {
        string reg2Int = RegisterGenerator::getRegister();
        string castCode = "%t" + reg2Int + " = zext i8 %t" + secondNum->storeReg +" to i32";
        CodeBuffer::instance().emit(castCode);
        DoAction(regNum,firstNum->storeReg, reg2Int,  "mul");

    }
    else if (firstNum->type == Type_::TYPE_BYTE  && secondNum->type ==Type_::TYPE_INT)
    {
        string reg1Int = RegisterGenerator::getRegister();
        string castCode = "%t" + reg1Int + " = zext i8 %t" + secondNum->storeReg +" to i32";
        CodeBuffer::instance().emit(castCode);
        DoAction(regNum,reg1Int, secondNum->storeReg, "mul");
    }
    else if (firstNum->type == Type_::TYPE_BYTE  && secondNum->type ==Type_::TYPE_BYTE)
    {
        string reg1Int = RegisterGenerator::getRegister();
        string reg2Int = RegisterGenerator::getRegister();
        string castCode = "%t" + reg1Int + " = zext i8 %t" + secondNum->storeReg +" to i32";
        CodeBuffer::instance().emit(castCode);
        castCode = "%t" + reg2Int + " = zext i8 %t" + secondNum->storeReg +" to i32";
        CodeBuffer::instance().emit(castCode);
        DoAction(regNum,reg1Int, reg2Int, "mul");
    }
    else
        DoAction(regNum, firstNum->storeReg, secondNum->storeReg, "mul");
}

void CodeGenerator::DoAction(string resultReg, string firstReg, string secondReg, string action)
{
    string code = "%t" + resultReg + " = "+ action + " i32 %t" +firstReg + ", %t" + secondReg;
    CodeBuffer::instance().emit(code);
}