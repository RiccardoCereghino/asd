#include "dictionary.h"

#include <math.h> // sqrt()

using namespace dict;

struct dict::node {
  Elem	elem;
  node  *left_child;
  node  *right_child;
};

/****************************************************************/
/*              FUNZIONE     IMPLEMENTATA                       */
/****************************************************************/

bool dict::is_empty(const Dictionary& s)
{
  return s == empty_node;
}

/****************************************************************/
/*              FUNZIONE NON IMPLEMENTATA                       */
/****************************************************************/

Elem dict::delete_min(Dictionary &s){
  Elem v;
  Dictionary aux = s;

  while( aux->left_child != empty_node )
  {
    aux = aux->left_child;
  }

  v.key = aux->elem.key;
  v.value = aux->elem.value;
  aux = aux->right_child;

  return v;
}

Error dict::deleteElem(const Key k, Dictionary& s)
{
  if( is_empty(s) )
    return FAIL;
  if( k < s->elem.key )
    return deleteElem( k, s->left_child );
  if( k > s->elem.key )
    return deleteElem( k, s->right_child );

  if( ( s->left_child == empty_node ) && ( s->right_child == empty_node ) )
    s = empty_node;
  else if( s->left_child == empty_node )
    s = s->right_child;
  else if( s->right_child == empty_node )
    s = s->left_child;
  else
    s->elem = delete_min( s->right_child );
  return OK;
}


/****************************************************************/
/*              FUNZIONE NON IMPLEMENTATA                       */
/****************************************************************/
Value dict::search(const Key k, const Dictionary& s)
{	
  if( s == empty_node )
    return emptyValue;
  if( s->elem.key == k )
    return s->elem.value;
  if( k < s->elem.key )
    return search( k, s->left_child );
  else
    return search( k, s->right_child );
}

/****************************************************************/
/*              FUNZIONE NON IMPLEMENTATA                       */
/****************************************************************/
Error dict::insertElem(const Key k, const Value v,  Dictionary& s)
{
  
  if( is_empty(s) )
  {
    s = new node;
    s->elem.key = k;
    s->elem.value = v;
    s->left_child = empty_node;
    s->right_child = empty_node;
    return OK;
  }

  else if( k < s->elem.key )
  {
    return insertElem( k, v, s->left_child );
  }

  else if( k > s->elem.key )
  {
    return insertElem( k, v, s->right_child );
  }

  return FAIL;
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

void dict::print_node(const dict::Dictionary& s)
{
  cout << "KEY: "   << s -> elem.key   << endl;
  cout << "VALUE: " << s -> elem.value << endl; 
}

/****************************************************************/
void dict::print_aux(const dict::Dictionary& s, int& total_elem )
// stampa il contenuto del dizionario ed anche informazioni su come sono stati organizzati gli elementi
{
  if( dict::is_empty(s) ) return;
  
  ++total_elem;
  if( !dict::is_empty(s->left_child) )
    print_node( s->left_child );
  print_node( s );
  if( !dict::is_empty(s->right_child) )
    print_node( s->right_child );

  print_aux( s->left_child , total_elem );
  print_aux( s->right_child , total_elem );
  return;
}

void print(const dict::Dictionary& s)
{
  int total_elem = 0;
  print_aux( s, total_elem );

  cout << "\n===STATISTICHE SULL'ORGANIZZAZIONE DEL DIZIONARIO===\n";
  cout << "\nIl numero totale di elementi memorizzati e' " << total_elem;
}
