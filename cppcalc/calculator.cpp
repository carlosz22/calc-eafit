#include "calculator.h"
#include "parser.h"
#include "ast.h"
#include <string>
#include <iostream>
#include <sstream>


Calculator::Calculator():
   memory(0), interactive(true), environPref(false), wPrint(false)
{}

void Calculator::eval(string expr) {
  imprimir.clear();
   Parser* parser = new Parser(new istringstream(expr));

   AST* tree = parser->parse();

   int result = tree->evaluate();
   //if(!(parser->getAssign())) {
   if (getPrint()){
    cout << "=> " << result;
    
    if (imprimir.size() > 0) {
      cout << " [";
      if (imprimir.size() == 1){
	cout << imprimir[0];
      }
      else {
	for(int j = 0; j < imprimir.size(); j++) {
	  cout << imprimir[j];
	  if(j != (imprimir.size() - 1)){
	    cout << ", ";
	  }
	}

      }

      cout << "]";
    }

    cout << endl;
  }
  // }

   delete tree;

   delete parser;

   //return result;
}

void Calculator::store(int val) {
   memory = val;
}

int Calculator::recall() {
   return memory;
}

int Calculator::plus(int val) {
  memory += val;
  return memory;
}

int Calculator::minus(int val) {
  memory -= val;
  return memory;
}

int Calculator::clear() {
  memory = 0;
  return memory;
}

void Calculator::setVariables(string s, int val) {
  variables[s] = val;
  if(getPrint()){
    stringstream numtostr;
    string nuevo;
    int num = variables[s];
    numtostr << num;
    nuevo = s + " <- " + numtostr.str();
    imprimir.push_back(nuevo);
  }
}

int Calculator::getVariables(string s) {
  return variables[s];
}

void Calculator::setIntMode(bool im){
  interactive = im;
}
bool Calculator::getIntMode() {
  return interactive;
}

void Calculator::setPref(bool prt) {
  environPref = prt;
}

bool Calculator::getPref(){
  return environPref;
}
void Calculator::setPrint(bool prt){
  wPrint = prt;
}

bool Calculator::getPrint() {
  return wPrint;
}
