#pragma once

#include <string>
#include <map>
#include <string>
#include <vector>

using namespace std;


class Calculator {
 public:
   Calculator();

   void eval(string expr);
   void store(int val);
   int recall();
   int plus(int val);
   int minus(int val);
   int clear();
   void setVariables(string s, int val);
   bool getIntMode();
   int getVariables(string s);
   void setIntMode(bool);
   bool getPref();
   void setPref(bool);
   bool getPrint();
   void setPrint(bool);


 private:
   int memory;
   bool interactive;
   bool environPref;
   bool wPrint;
   map<string, int> variables;
   vector<string> imprimir;
};

extern Calculator* calc;
