//
// Created by User on 5/28/2022.
//

#ifndef HW3_OUTPUT_CPP_SYMBOLTABLEENTRY_H
#define HW3_OUTPUT_CPP_SYMBOLTABLEENTRY_H

#include <string>
#include <vector>
#include "Type_.h"

struct SymbolTableEntry{
    std::string name;
    Type_ type;
    int offset;
    std::vector<Type_> params;
    bool isFunction;

    ///Use this ctor for regular symbols
    SymbolTableEntry(const std::string& name, const Type_ type, int offset);
    ///Use this ctor for function symbols
    SymbolTableEntry(const std::string& name, const Type_ type, int offset, const std::vector<Type_>& params);
    void getArgsTypesAsStrings(std::vector<std::string>&);
};

#endif //HW3_OUTPUT_CPP_SYMBOLTABLEENTRY_H
