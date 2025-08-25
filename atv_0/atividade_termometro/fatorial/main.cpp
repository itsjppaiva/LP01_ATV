#include <iostream>
using namespace std;

int main (){

    int valor, numero, fatorial;
    cout << "Entre com um valor: ";
    cin >> valor;
    fatorial = valor;       
    numero = valor - 1;

    while(numero != 1){
        fatorial = fatorial * numero; 
        numero = numero - 1;
    }
    
    cout << fatorial;

    return 0;
}
