//
// Created by User on 5/25/2022.
//

#include <iostream>
#include "SymbolTableManager.h"

using namespace std;

SymbolTableManager::SymbolTableManager() : _symbolTableStack(stack<shared_ptr<SymbolTable>>()), _offsetStack(stack<int>()){
    _offsetStack.push(0); //Zero should always be the first offset
    //_symbolTableStack.push(make_shared<SymbolTable>(SymbolTable(nullptr)));
}

void SymbolTableManager::pushOnSameScope(std::shared_ptr<SymbolTable> table) {
    _symbolTableStack.push(table);
    int current_offset = _offsetStack.top();
    _offsetStack.pop();
    _offsetStack.push(current_offset + 1);
}

void SymbolTableManager::pushOnNewScope(std::shared_ptr<SymbolTable> table) {
    _symbolTableStack.push(table);
    int current_offset;
    if (_offsetStack.empty())
    {
        current_offset = 0;
    }
    else
    {
        current_offset = _offsetStack.top();
    }
    _offsetStack.push(current_offset);
}

void SymbolTableManager::pop() {
    _symbolTableStack.pop();
    _offsetStack.pop();
}

std::shared_ptr<SymbolTable> SymbolTableManager::top() {
    if (_symbolTableStack.empty())
    {
        return nullptr;
    }
    return _symbolTableStack.top();
}

void SymbolTableManager::openScope() {
    std::shared_ptr<SymbolTable> newTable = std::make_shared<SymbolTable>(SymbolTable(this->top()));
    pushOnNewScope(newTable);
}

void SymbolTableManager::openWhileScope() {
    std::shared_ptr<SymbolTable> newTable = std::make_shared<SymbolTable>(SymbolTable(this->top(), WHILE_SCOPE));
    pushOnNewScope(newTable);
}

void SymbolTableManager::openFuncScope() {
    std::shared_ptr<SymbolTable> newTable = std::make_shared<SymbolTable>(SymbolTable(this->top(), FUNC_SCOPE));
    pushOnNewScope(newTable);
}


void SymbolTableManager::closeScope() {
    //output::endScope();
    shared_ptr<SymbolTable> scope = top();
    outputFunctionParamsInScope();
    for (auto &entry : scope->table) {
        if (entry.isFunction) {
            outputFunctionDeclaration(entry);
        } else if(entry.offset >= 0){
           // output::printID(entry.name, entry.offset, ConvertTypeToString(entry.type));
        }
    }
    this->pop();
}

int SymbolTableManager::getOffset() {
    int offset = _offsetStack.top();
    _offsetStack.pop();
    _offsetStack.push(offset + 1);
    return offset;
}

bool SymbolTableManager::doesSymbolExists(Type_ type, const std::string& name) {
    std::shared_ptr<SymbolTable> currentTable = this->top();
    while (nullptr != currentTable)
    {
        for(const SymbolTableEntry& entry : currentTable->table)
        {
            if(entry.name == name)
            {
                return true;
            }
        }
        currentTable = currentTable->parent;
    }
    return false;
}

Type_ SymbolTableManager::doesFunctionExist(const std::string &functionName, const std::vector<Type_> params) {
    shared_ptr<SymbolTable> currentTable = this->top();
    while (nullptr != currentTable)
    {
        for(const SymbolTableEntry& entry : currentTable->table)
        {
            if(entry.isFunction && entry.name == functionName && areSameParams(params, entry.params))
            {
                return entry.type;
            }
        }
        currentTable = currentTable->parent;
    }
    return TYPE_NOT_VALID;
}


Type_ SymbolTableManager::getFunctionReturnType(const std::string &functionName) {
    std::shared_ptr<SymbolTable> currentTable = this->top();
    while (nullptr != currentTable)
    {
        for(const SymbolTableEntry& entry : currentTable->table)
        {
            if(entry.isFunction && entry.name == functionName)
            {
                return entry.type;
            }
        }
        currentTable = currentTable->parent;
    }
    return TYPE_NOT_VALID;
}

Type_ SymbolTableManager::getVarType(const std::string &name) {
    std::shared_ptr<SymbolTable> currentTable = this->top();
    while (nullptr != currentTable)
    {
        for(const SymbolTableEntry& entry : currentTable->table)
        {
            if(false == entry.isFunction && entry.name == name)
            {
                return entry.type;
            }
        }
        currentTable = currentTable->parent;
    }
    return TYPE_NOT_VALID;
}

bool SymbolTableManager::isFunction(const std::string &name) {
    std::shared_ptr<SymbolTable> currentTable = this->top();
    while (nullptr != currentTable)
    {
        for(const SymbolTableEntry& entry : currentTable->table)
        {
            if(entry.isFunction && entry.name == name)
            {
                return true;
            }
        }
        currentTable = currentTable->parent;
    }
    return false;
}

Type_ SymbolTableManager::getCurrentScopeFunctionReturnType() {
    auto currentScope = this->top();
    while(currentScope != nullptr)
    {
        if(FUNC_SCOPE == currentScope->scopeType)
        {
            return currentScope->functionRetType;
        }
        currentScope = currentScope->parent;
    }
    return TYPE_NOT_VALID;
}


bool SymbolTableManager::areSameParams(const std::vector<Type_>& actual, const std::vector<Type_>& expected)
{
    if(actual.size() != expected.size())
    {
        return false;
    }
    auto itActual = actual.begin();
    for(auto itExpected = expected.begin(); itExpected != expected.end(); itExpected++)
    {
        if(*itActual != *itExpected && !(*itActual == Type_::TYPE_BYTE && *itExpected == Type_::TYPE_INT))
        {
            return false;
        }
        itActual++;
    }
    return true;

}

bool SymbolTableManager::isWhileScoped() {
    std::shared_ptr<SymbolTable> currentTable = this->top();
    while (nullptr != currentTable)
    {
        if(WHILE_SCOPE == currentTable->scopeType)
        {
            return true;
        }
        currentTable = currentTable->parent;
    }
    return false;
}

std::vector<std::string> SymbolTableManager::getParamList(const std::string& functionName) {
    std::shared_ptr<SymbolTable> currentTable = this->top();
    std::vector<std::string> result = std::vector<std::string>();
    while (nullptr != currentTable)
    {
        for(const SymbolTableEntry& entry : currentTable->table)
        {
            if(entry.isFunction && entry.name == functionName)
            {
                for(const Type_& param : entry.params)
                {
                    result.push_back(ConvertTypeToString(param));
                }
                return result;
            }
        }
        currentTable = currentTable->parent;
    }
    return result; //Should not reach here.
}

std::string SymbolTableManager::ConvertTypeToString(Type_ type) {
    switch (type)
        {
            case(Type_::TYPE_BOOL):
                return  "bool";
            case(Type_::TYPE_VOID):
                return  "void";
            case(Type_::TYPE_INT):
                return  "int";
            case(Type_::TYPE_BYTE):
                return  "byte";
            case(Type_::TYPE_STRING):
                return  "string";
            default:
                return "NOT_VALID";
        }
}

void SymbolTableManager::outputFunctionParamsInScope() {
    for(const auto& entry : top()->table)
    {
        if(entry.offset < 0)
        {
           // output::printID(entry.name, entry.offset, ConvertTypeToString(entry.type));
        }
    }
}

void SymbolTableManager::outputFunctionDeclaration(SymbolTableEntry& entry) {
    vector<string> arg_types = vector<string>();
    entry.getArgsTypesAsStrings(arg_types);
    string type = ConvertTypeToString(entry.type);
   // type = output::makeFunctionType(type, arg_types);
   // output::printID(entry.name, entry.offset, type);
}

std::string SymbolTableManager::getVarRegister(const std::string& var_name) {
    std::shared_ptr<SymbolTable> currentTable = this->top();
    while (nullptr != currentTable)
    {
        for(const SymbolTableEntry& entry : currentTable->table)
        {
            if(false == entry.isFunction && entry.name == var_name)
            {
                return entry.register_name;
            }
        }
        currentTable = currentTable->parent;
    }
    return ""; //Shouldn't reach here, a check that var exists should be performed before calling this method.
}

void SymbolTableManager::assignRegisterToVar(const std::string& var_name, const std::string& reg)
{
    std::shared_ptr<SymbolTable> currentTable = this->top();
    while (nullptr != currentTable)
    {
        for(SymbolTableEntry& entry : currentTable->table)
        {
            if(false == entry.isFunction && entry.name == var_name)
            {
                entry.register_name = reg;
            }
        }
        currentTable = currentTable->parent;
    }
}

int SymbolTableManager::getVarOffset(const string& name) {
    std::shared_ptr<SymbolTable> currentTable = this->top();
    while (nullptr != currentTable)
    {
        for(const SymbolTableEntry& entry : currentTable->table)
        {
            if(false == entry.isFunction && entry.name == name)
            {
                return entry.offset;
            }
        }
        currentTable = currentTable->parent;
    }
    return -1;
}

std::string SymbolTableManager::getStackPointer() {
    return stackPointer;
}

std::string SymbolTableManager::ConvertTypeToLlvmType(Type_ type) {
    switch (type)
    {
        case(Type_::TYPE_BOOL):
            return  "i32";
        case(Type_::TYPE_VOID):
            return  "void";
        case(Type_::TYPE_INT):
            return  "i32";
        case(Type_::TYPE_BYTE):
            return  "i32";
        case(Type_::TYPE_STRING):
            return  "i8*";
        default:
            return "NOT_VALID";
    }
}

void SymbolTableManager::setStackPointer(const std::string& sp) {
    stackPointer = sp;
}

int SymbolTableManager::viewCurrentOffset() {
    return _offsetStack.top();
}




