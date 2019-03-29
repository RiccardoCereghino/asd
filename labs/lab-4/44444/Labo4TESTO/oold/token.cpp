/////////////////////////////////////////////////////////////////////
//
// Laboratorio 3: calcolo di semplici espressioni numeriche 
//                mediante pile e code
//
// vengono accettati dall'esterno solo numeri positivi.
// Per trattare anche numeri negativi occorre modificare
// l'analizzatore lessicale.
//
///////////////////////////////////////////////////////////////////


#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

#include "token.h"

using std::cout;
using std::cin;
using std::string;
using std::istringstream;
using std::ostringstream;

/////////////////////////////////////////////////////////////////////
// Funzioni ausiliarie su tipi di dato semplici
/////////////////////////////////////////////////////////////////////
void printToken(token &t){
  cout << "\n VAL :  " << t.val << "\n KIND :  " << t.k << "\n";
}

// da stringa a numero
int str2int(const string &s) {
  return stoi(s);
}

// da numero a stringa
string int2str(int n) {
  // DA IMPLEMENTARE
  return std::to_string(n);
}

// ritorna false se e solo se token di tipo sconosciuto o se stringa vuota.
// se stringa non vuota, la stringa perde il pezzo iniziale,
// che diventa token.

bool prossimoToken(string &s, token &t) {
  token tmp;
  int i = 0;
  bool b = true;

  if(s[i]==' '){
    s = s.substr(i+1,s.size()-1);
  }

  if(isdigit(s[i])){
    while(isdigit(s[i+1]))
      ++i;
    ++i;
    tmp.val = s.substr(0,i);
    tmp.k = NUMERO;
    s = s.substr(i,s.size()-1);
  }
  else{
    switch (s[i]){
      case '(':
        tmp.val = "(";
        tmp.k = PARENTESI_APERTA;
        break;
      case ')':
        tmp.val = ")";
        tmp.k = PARENTESI_CHIUSA;
        break;                
      case '+':
        tmp.val = "+";
        tmp.k = OP_SOMMA;
        break;                
      case '*':
        tmp.val = "*";
        tmp.k = OP_MOLTIPLICAZIONE;
        break;                
      case '-':
        tmp.val = "-";
        tmp.k = OP_SOTTRAZIONE;
        break;

      default:
        tmp.val = "";
        tmp.k = SCONOSCIUTO;
        b = false;
        break;
    }
    ++i;
    s = s.substr(i,s.size()-1);
  }
  t = tmp;
  return (b && s.size() != 0);
}