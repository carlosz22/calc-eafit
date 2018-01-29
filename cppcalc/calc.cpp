#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <ctype.h>
#include "calcex.h"
#include "calculator.h"
#include <fstream>
#include <vector>

using namespace std;

Calculator* calc;

void envInitialize(char* env[]);
void cmdlinescan(int argc, char* argv[]);
void cmdLineFileScan(int argc, char* argv[]);

int main(int argc, char* argv[], char* env[]) {
   string line;
   calc = new Calculator();
   calc->setPrint(false);
   envInitialize(env);
   cmdlinescan(argc,argv);
   if (calc->getPref()){
      envInitialize(env);
   }
   cmdLineFileScan(argc, argv);

   calc->setPrint(true);
   if (calc->getIntMode()){
         cout << "> ";
         while(getline(cin, line)){
             try {
               //calc = new Calculator();

               calc->eval(line);

               //cout << "=> " << result << endl;
               } catch(Exception ex) {
               cout << "* parse error" << endl;
               }
               cout << "> ";
            }
         }
         else{// lectura de los archivos
            for (int i = 1; i < argc; i++){
               string aux(argv[i]);
               int sizet = aux.length();
               if (sizet > 5) {
                     string ext = aux.substr(sizet -5, sizet -1);
                     if (ext == ".calc"){
                        ifstream inf(argv[i]);
                        while(getline(inf, line)){
                           try {
                              calc->eval(line);
                           } catch(Exception ex) {
                              cout << "* parse error" << endl;
                           }
                        }
                     }
                  }
            }
         }
      delete calc;
}


void envInitialize(char* env[]){
 for (int i = 0; env[i] != NULL; i++){
      if (strncmp(env[i], "CALCVAR", 7) == 0) {
         string aux = env[i];
         int size = aux.length();
         int j = 0;
         bool afterequal = false;
         while (j < size){
            if (afterequal){
               if(!isdigit(aux[j])){
                  break;
               }
            }
            if (aux[j] == '='){
               afterequal = true;
            }
            j++;
         }
         string sub = aux.substr(7, j);
         calc->eval(sub);
      }
   }
}

void cmdlinescan(int argc, char* argv[]) {
   for (int i = 0; i < argc; i++){
      if(strcmp(argv[i],"-e") == 0){
         calc->setPref(true);
         break;
      }
   }
   for (int i = 0; i < argc; i++) {
      if(strcmp(argv[i],"-v") == 0) {
         calc->eval(argv[i+1]);
      }
   }
}

void cmdLineFileScan(int argc, char* argv[]) {
   for (int i = 0; i < argc; i++) {
      string aux = argv[i];
      int size = aux.length();
      if (size > 5) {
         string ext = aux.substr(size - 5, size -1);
         char extType[8];
         strcpy(extType, ext.c_str());
         if (strcmp(extType, ".calc") == 0){
            calc->setIntMode(false);
            break;
         }
      }
   }
}
