#include "parser.h"
#include "calcex.h"
#include <string>
#include <sstream>
#include <map>

Parser::Parser(istream* in) {
   scan = new Scanner(in);
   isAssign = false;
}

Parser::~Parser() {
   try {
      delete scan;
   } catch (...) {}
}

AST* Parser::parse() {
   return Prog();
}

AST* Parser::Prog() {
   AST* result = Expr();
   Token* t = scan->getToken();

   if (t->getType() != eof) {
      throw ParseError;
   }

   return result;
}

AST* Parser::Expr() {
   return RestExpr(Term());
}

AST* Parser::RestExpr(AST* e) {
   Token* t = scan->getToken();

   if (t->getType() == add) {
      return RestExpr(new AddNode(e,Term()));
   }

   if (t->getType() == sub)
      return RestExpr(new SubNode(e,Term()));

   scan->putBackToken();

   return e;
}

AST* Parser::Term() {
   return RestTerm(Storable());
   //write your Term() code here. This code is just temporary
   //so you can try the calculator out before finishing it.

   // cout << "Term not implemented" << endl;

   // throw ParseError;
}

AST* Parser::RestTerm(AST* e) {
   Token* t = scan->getToken();

   if (t->getType() == times) {
      return RestTerm(new TimesNode(e,Storable()));
   }

   if (t->getType() == divide)
      return RestTerm(new DivideNode(e,Storable()));

  if (t->getType() == modu) {
    return RestTerm(new ModNode(e,Storable()));
  }

   scan->putBackToken();

   return e;
}

AST* Parser::Storable() {
  AST* result = MemOperation(Factor());

  Token* t = scan->getToken();

  scan->putBackToken();
  return result;
}

AST* Parser::MemOperation(AST* e) {
  Token* t = scan->getToken();

  if (t->getType() == keyword) {
    if (t->getLex() == "S") {
      return new StoreNode(e);
    } else if(t->getLex() == "P") {
        return new PlusNode(e);
    } else if(t->getLex() == "M") {
        return new MinNode(e);
    }
  }

  scan->putBackToken();
  return e;
}

AST* Parser::Factor() {
  Token* t = scan->getToken();

  if (t->getType() == number) {
    istringstream in(t->getLex());
    int val;
    in >> val;
    return new NumNode(val);
  }

  if(t->getType() == identifier) {
    istringstream in(t->getLex());
    string id;
    in >> id;
    return Assignable(id);
  }

  if (t->getType() == keyword) {
    if (t->getLex() == "R") {
      return new RecallNode();
    } else if (t->getLex() == "C") {
      return new ClearNode();
    }
    else {
      throw ParseError;
    }
  }


  if (t->getType() == lparen) {

    AST* result = Expr();

    t = scan->getToken();

    if(t->getType() == rparen) {
      return result;
    }

  /*  cout << "Syntax error expected ) at line: "
	 << t->getLine()
	 << " col: "
	 << t->getCol()
	 << endl;
*/
    throw ParseError;
  }

  /*cout << "Syntax error expected ) at line: "
       << t->getLine()
       << " col: "
       << t->getCol()
       << endl;
*/
  throw ParseError;
}

AST* Parser::Assignable(string id){
  Token* t = scan->getToken();
  if(t->getType() == igual){
    setAssign(true);
    return Assign(id);
  }
  scan->putBackToken();
  return new ValueNode(id);
}

AST* Parser::Assign(string s){
  AST* result = Expr();
  int m = result->evaluate();
  scan->putBackToken();
  return new AssignVarNode(new NumNode(m), s);
}

void Parser::setAssign(bool prt){
  isAssign = prt;
}

bool Parser::getAssign(){
  return isAssign;
}
