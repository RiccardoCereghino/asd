#include <iostream>
#include <stdexcept>
#include <vector> 
#include <fstream> 
#include <chrono>          // necessario compilare con -std=c++11
#include <stdlib.h>        // srand, rand
#include <string>          // std::string

#include "string-utility.h"


using namespace std::chrono; 
using namespace std; 

namespace dict {

// Codici di errore

enum Error {OK, FAIL};

// Tipi e costanti

typedef string Key;        // tipo base 
typedef string Value;      // tipo base 

const Key emptyKey = "###RESERVED KEYWORD### EMPTY KEY";
const Value emptyValue = "###RESERVED KEYWORD### EMPTY VALUE";

typedef struct {
    Key	key;
    Value value;
} Elem;


// Implementazione basata su alberi binari

struct node;
//const node empty_node = NULL;
typedef node* Dictionary; // un Dictionary è il primo nodo
const Dictionary empty_node = NULL;



Error insertElem(const Key, const Value, Dictionary&);
Error deleteElem(const Key, Dictionary&);
Value search(const Key, const Dictionary&);
Dictionary createEmptyDict();


}  // end namespace Dict


dict::Dictionary readFromFile(string);
dict::Dictionary readFromStdin();
dict::Dictionary readFromStream(istream&);
void print(const dict::Dictionary&);
void print_node(const dict::Dictionary&);