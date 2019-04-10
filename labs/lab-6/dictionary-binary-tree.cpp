#include "dictionary.h"

#include <math.h> // sqrt()

using namespace dict;

struct dict::node {
  Elem	elem;
  node  *left_child;
  node  *right_child;
};

/****************************************************************/
/*              FUNZIONE NON IMPLEMENTATA                       */
/****************************************************************/
Error dict::deleteElem(const Key k, Dictionary& s)
{
  return OK;  	
}


/****************************************************************/
/*              FUNZIONE NON IMPLEMENTATA                       */
/****************************************************************/
Value dict::search(const Key k, const Dictionary& s)
{	
  return emptyValue;
}
/****************************************************************/
/*              FUNZIONE NON IMPLEMENTATA                       */
/****************************************************************/
Error dict::insertElem(const Key k, const Value v,  Dictionary& s)
{
  
  if( s == empty_node )
  {cout << "aa";
    Dictionary aux = new node;
    aux -> elem .  key   = k;
    aux -> elem .  value = v;
    aux -> left_child    = empty_node;
    aux -> right_child   = empty_node;
    s = aux;
    print_node(s);
  }

  else if( k < s->elem.key )
  {print_node(s);
    insertElem( k, v, s->left_child );
  }

  else if( k > s->elem.key )
  {print_node(s);
    insertElem( k, v, s->right_child );
  }

  return OK;
}

Dictionary dict::createEmptyDict(){
  return empty_node;
}

/****************************************************************/
Dictionary readFromFile(string nome_file)
{
    ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
    if (!ifs) {cout << "\nErrore apertura file, verificare di avere inserito un nome corretto\n"; return dict::createEmptyDict();}  
    return readFromStream(ifs);
}


/****************************************************************/
Dictionary readFromStdin()
{
    cout << "\nInserire una sequenza di linee che rispettano la sintassi key: value.<enter>\nDigitare CTRL^ D per terminare l'inserimento\n";
    Dictionary d = readFromStream((std::cin));
// Questa serve per aggirare un bug di alcune versioni attuali di glibc.
    clearerr(stdin);
    return d;
}


/****************************************************************/
Dictionary readFromStream(istream& str)
{
    Dictionary d = createEmptyDict();     
    string key, kcopy;
    string value;
    getline (str, key, ':'); 
    getline (str, value); 
    while (!str.eof())  
        {     
        kcopy = key;
        removeBlanksAndLower(kcopy);   
        insertElem(kcopy, value, d); // FINCHE' NON IMPLEMENTATE LA INSERTELEM, NON PUO' FUNZIONARE CORRETTAMENTE: la insertElem e' la prima funzione che dovete implementare
        getline (str, key, ':'); 
        getline (str, value); 
        }
    str.clear();
    return d;
}


/****************************************************************/

void print_node(const Dictionary& s)
{
  cout << "KEY: "   << s -> elem.key   << endl;
  cout << "VALUE: " << s -> elem.value << endl; 
}

/****************************************************************/
void print_aux(const Dictionary& s, int& total_elem )
// stampa il contenuto del dizionario ed anche informazioni su come sono stati organizzati gli elementi
{cout << "aa";
  if( s == empty_node ) return;
  cout << "aa";
  ++total_elem;
  print_node( s->left_child );
  print_node( s );
  print_node( s->right_child );

  print_aux( s->left_child , total_elem );
  print_aux( s->right_child , total_elem );
  return;
}

void print(const Dictionary& s)
{cout << "aa";
  int total_elem = 0;
  print_aux( s, total_elem );

  cout << "\n===STATISTICHE SULL'ORGANIZZAZIONE DEL DIZIONARIO===\n";
  cout << "\nIl numero totale di elementi memorizzati e' " << total_elem;
}



