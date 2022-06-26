//
// Created by User on 5/30/2022.
//
#include "Symbols.h"

void expressionList::insertElement(const Type_ expType, const std::string& reg) {
        exprList.insert(exprList.begin(), expType);
        registersList.insert(registersList.begin(), reg);
}