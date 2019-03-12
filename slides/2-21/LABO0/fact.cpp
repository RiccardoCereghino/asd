#include "fact.h" 

int main()
{
   try {
   cout << "\nInserire un numero naturale\n> ";
   int n;
   cin >> n;
   cout << "\nIl fattoriale del numero inserito e' " << fact(n) << endl;
   return 0;
   } 
catch (runtime_error &msg) 
   {cerr << "Errore a runtime: " << msg.what() << endl;} 
catch (...) 
   {cerr << "Eccezione non riconosciuta\n";}
}

