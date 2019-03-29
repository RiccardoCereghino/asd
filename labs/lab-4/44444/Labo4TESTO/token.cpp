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
  int n;
  istringstream itmp(s);
  itmp >> n;
  return n;
}

// da numero a stringa
string int2str(int n) {
  ostringstream otmp;
  otmp << n;
  return otmp.str();
}

// ritorna false se e solo se token di tipo sconosciuto o se stringa vuota.
// se stringa non vuota, la stringa perde il pezzo iniziale,
// che diventa token.

bool prossimoToken(string &s, token &t) {
  int i = 0;

  switch (s[i]){
    case '(':
      t.val = "(";
      t.k = PARENTESI_APERTA;
      break;
    case ')':
      t.val = ")";
      t.k = PARENTESI_CHIUSA;
      break;                
    case '+':
      t.val = "+";
      t.k = OP_SOMMA;
      break;                
    case '*':
      t.val = "*";
      t.k = OP_MOLTIPLICAZIONE;
      break;                
    case '-':
      if(isdigit(s[i+1])){
        while(isdigit(s[i+1]))
          ++i;
        t.val = s.substr(0,i+1);
        t.k = NUMERO;
      }else{
        t.val = "-";
        t.k = OP_SOTTRAZIONE;
      }
      break;
    default:
      if(isdigit(s[i])){
        while(isdigit(s[i+1]))
          ++i;
        t.val = s.substr(0,i+1);
        t.k = NUMERO;
      }
      else{
        t.val = "";
        t.k = SCONOSCIUTO;
        return false;
      }
      break;
  }
  
  ++i;

  if( s.size() > 1){
    if(s[i]==' '){
      ++i;
    }
    else
      return false;
  }

  s = s.substr(i,s.size());
  
  return (s.size() != 0);
}