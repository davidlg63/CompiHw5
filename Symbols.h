//
// Created by User on 5/28/2022.
//

#ifndef HW3_OUTPUT_CPP_NONTERMINALS_H
#define HW3_OUTPUT_CPP_NONTERMINALS_H

#include <string>
#include <vector>
#include "SymbolBase.h"
#include "Type_.h"
#include "bp.hpp"

struct TerminalID : public SymbolBase
{
    std::string name;
    explicit TerminalID(const char* _name) : name(_name){};
};

struct NonTerminalVar : public SymbolBase
{
    Type_ type;
    std::string name;
    NonTerminalVar(Type_ _type, std::string _name) : type(_type), name(_name){};
};

struct paramList : public SymbolBase
{
    std::vector<Type_> types_in_list;
    std::vector<std::string> names_in_list;
    paramList(): types_in_list(std::vector<Type_>()), names_in_list(std::vector<std::string>()){}
};

struct call2Fun : public SymbolBase
{
    std::string name;
    Type_ type;
    std::vector<Type_> expList;
    std::string reg;
    call2Fun() = default;
};

struct expressionList : public SymbolBase
{
    std::vector<Type_> exprList;
    std::vector<std::string> registersList;
    expressionList() = default;
    void insertElement(const Type_ expType);
    void insertRegister(const std::string& reg);
};



struct Id : public SymbolBase
{
    std::string name;
    std::string reg;
    explicit Id(const char* val): name(std::string(val)){}
};

struct retType : public SymbolBase
{
    Type_ type;
    std::string reg;
    std::vector<std::pair<int, BranchLabelIndex>> trueList;
    std::vector<std::pair<int, BranchLabelIndex>> falseList;
    retType()= default;
};

struct Num : public SymbolBase
{
    std::string value;
    explicit Num(const char* val): value(std::string(val)){}
};

struct Param : public SymbolBase
{
    std::string name;
    Type_ type;
    Param(const Type_ _type, const std::string& _name) : type(_type), name(_name){};
};

struct Label : public SymbolBase
{
    std::string label;
    explicit Label(const std::string& lbl) : label(lbl){};
};

struct StatementNode : public SymbolBase
{
    std::vector<std::pair<int, BranchLabelIndex>> nextList;
    std::vector<std::pair<int, BranchLabelIndex>> breakList;
    std::vector<std::pair<int, BranchLabelIndex>> continueList;
};

struct JumpMarker : public SymbolBase
{
    std::vector<std::pair<int, BranchLabelIndex>> nextList;
};

struct String : public SymbolBase
{
    std::string value;
    explicit String(const char* val) : value(val){};
};


#endif //HW3_OUTPUT_CPP_NONTERMINALS_H