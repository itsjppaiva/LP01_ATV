#include <iostream>
using namespace std;

int main (){
    
    int valor, numero;
    cout << "Entre com um valor: ";
    cin >> valor;

    for(numero=1; numero<=valor; numero++){
        cout << " " << numero;
    }

    return 0;
}