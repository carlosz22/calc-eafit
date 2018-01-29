#pragma once

#include "ast.h"
#include "scanner.h"

class Parser {
 public:
   Parser(istream* in);
   ~Parser();

   AST* parse();

   void setAssign(bool);
   bool getAssign();

 private:
   AST* Prog();
   AST* Expr();
   AST* RestExpr(AST* e);
   AST* Term();
   AST* RestTerm(AST* t);
   AST* MemOperation(AST* e);
   AST* Storable();
   AST* Factor();
   AST* Assignable(string s);
   AST* Assign(string s);

   bool isAssign;

   Scanner* scan;
};
