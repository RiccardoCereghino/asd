#include "esiste_perogni.h" 

int main()
{
try {

/* int inizio = 3; 
int fine = 12;
srand(time(NULL));
cout << inizio+rand()%(fine-inizio+1) << endl;

srand(34);
cout << " " << rand() << " " << rand() << " " << rand() << " " << rand() << " " << rand() << " " << rand() << " " << rand() << " " << rand() << endl; 

srand(49);
cout << " " << rand() << " " << rand() << " " << rand() << " " << rand() << " " << rand() << " " << rand() << " " << rand() << " " << rand() << endl; 

srand(34);
cout << " " << rand() << " " << rand() << " " << rand() << " " << rand() << " " << rand() << " " << rand() << " " << rand() << " " << rand() << endl; 

srand(49);
cout << " " << rand() << " " << rand() << " " << rand() << " " << rand() << " " << rand() << " " << rand() << " " << rand() << " " << rand() << endl; 
*/

Elem n;
Seq l;
string nome_file;

createEmpty(l);
cout << "Inserire nome file da cui leggere la sequenza: ";
cin >> nome_file;
l = seqReadFromFile(nome_file);
cout << "\nSequenza inserita: ";
seqPrint(l);
cout << "\nSomma: " << sumRec(l);
cout << "\nProdotto: " << prodRec(l);
cout << "\nInserire numero n per verifica se esiste nella sequenza un numero < n: ";
cin >> n;
cout << "  " << isThereLesserThanRec(n, l) << endl;
cout << "\nInserire numero n per verifica se tutti i numeri nella sequenza sono >= n: ";
cin >> n;
cout << "  " << areAllGreaterEqThan(n, l) << endl;

return 0; 
} 
catch (runtime_error &msg) 
   {cerr << "Errore a runtime: " << msg.what() << endl;} 
catch (...) 
   {cerr << "Eccezione non riconosciuta\n";}
}

