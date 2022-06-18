//
// Created by User on 5/25/2022.
//

#ifndef HW3_SYMBOLTABLENODE_H
#define HW3_SYMBOLTABLENODE_H

#include <string>
#include <memory>
#include <list>
#include "SymbolBase.h"
#include "SymbolTableEntry.h"
#include "ScopeType.h"

class SymbolTable
{
public:
    std::list<SymbolTableEntry> table;
    std::shared_ptr<SymbolTable> parent;
    ScopeType scopeType;
    Type_ functionRetType;

    explicit SymbolTable(std::shared_ptr<SymbolTable> parent, ScopeType = ScopeType::OTHER_SCOPE);
    void Insert(const std::string& name, const Type_ type, const int offset);
    void InsertFunction(const std::string& name, const Type_ type, const int offset, const std::vector<Type_>& params = std::vector<Type_>()
            , const std::vector<std::string>& paramsIdentifiers = std::vector<std::string>());

};

#endif //HW3_SYMBOLTABLENODE_H
