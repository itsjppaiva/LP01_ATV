#include <iostream>
using namespace std;

int main (){
    
    int armazena[5];
    int i;
    int soma_array = 0;

    for(i=0; i<5; i++){
        cout << "Entre com um valor: ";
        cin >> armazena[i];
    }

    for(i=0; i<5; i++){
        soma_array = soma_array + armazena[i];
    }

    cout << "Soma dos valores informados: " << soma_array;

    return 0;
}