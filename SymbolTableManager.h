//
// Created by User on 5/25/2022.
//

#ifndef HW3_SYMBOLTABLESTACK_H
#define HW3_SYMBOLTABLESTACK_H

#include <memory>
#include <stack>
#include "SymbolTable.h"
#include "Type_.h"
#include "Symbols.h"
#include "SymbolTableEntry.h"
#include "ScopeType.h"
#define YYSTYPE SymbolBase*

class SymbolTableManager
{
    std::stack<std::shared_ptr<SymbolTable>> _symbolTableStack;
    std::stack<int> _offsetStack;
    std::string stackPointer;

    bool areSameParams(const std::vector<Type_>& actual, const std::vector<Type_>& expected);
    void outputFunctionParamsInScope();
    void outputFunctionDeclaration(SymbolTableEntry& entry);

public:
    SymbolTableManager();
    void pushOnSameScope(std::shared_ptr<SymbolTable> table);
    void pushOnNewScope(std::shared_ptr<SymbolTable> table);
    void pop();
    std::shared_ptr<SymbolTable> top();
    void openScope();
    void closeScope();
    void openWhileScope();
    void openFuncScope();
    int getOffset();
    bool doesSymbolExists(Type_ type, const std::string& name);
    Type_ doesFunctionExist(const std::string& functionName, const std::vector<Type_> params);
    Type_ getFunctionReturnType(const std::string& functionName);
    Type_ getVarType(const std::string& name);
    int getVarOffset(const std::string& name);
    /// gets the register name that is assigned to the variable.
    std::string getVarRegister(const std::string& var_name);
    ///Assigns a register to a variable.
    void assignRegisterToVar(const std::string& var_name, const std::string& reg);
    bool isFunction (const std::string& name);
    Type_ getCurrentScopeFunctionReturnType();
    bool isWhileScoped();
    std::vector<std::string> getParamList(const std::string& functionName);
    std::string getStackPointer();
    void setStackPointer(const std::string& stackPointer);
    static std::string ConvertTypeToString(Type_ type);
    static std::string ConvertTypeToLlvmType(Type_ type);
};

#endif //HW3_SYMBOLTABLESTACK_H
