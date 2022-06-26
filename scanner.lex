%{

/* Declarations section */
#include <stdio.h>
#include "SymbolTableManager.h"
#include "parser.tab.hpp"
#include "hw3_output.hpp"
void lexicalError();
%}

%option yylineno
%option noyywrap
%option nounput

%%

void								return VOID;
int									return INT;
byte								return BYTE;
b 									return B;
bool								return BOOL;
auto 								return AUTO;
and									return AND;
or									return OR;
not									return NOT;
true 								return TRUE;
false 								return FALSE;
return 								return RETURN;
if									return IF;
else 								return ELSE;
while 								return WHILE;
break 								return BREAK;
continue							return CONTINUE;
,									return COMMA;
\(									return LPAREN;
\)									return RPAREN;
\{									return LBRACE;
\}									return RBRACE;
=									return ASSIGN;
\<									return RELOP_LESS;
\>									return RELOP_GREATER;
\<=									return RELOP_LEQ;
\>=									return RELOP_GEQ;
==									return RELOP_EQ;
!=									return RELOP_NOTEQ
\+									return BINOP_PLUS;
\-									return BINOP_MINUS;
\*									return BINOP_MUL;
\/									return BINOP_DIV;
[a-zA-Z][a-zA-Z0-9]*				{yylval = new Id(yytext); return ID;};
;									return SC;
0|[1-9]([0-9])*						{yylval = new Num(yytext); return NUM;};
\"([^\n\r\"\\]|\\[rnt"\\])+\"		{yylval = new String(yytext); return STRING;};
\/\/[^\r\n]*[\r|\n|\r\n]?			;
[\r\n\t ]+							;
.									lexicalError();

%%

void lexicalError()
{
	output::errorLex(yylineno);
	exit(1);
}