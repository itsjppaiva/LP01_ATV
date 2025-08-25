#include <iostream>
using namespace std;

int main (){

    int numero;
    cout << "Entre com um valor: ";
    cin >> numero;

    if(numero%2==0){
        cout << "O numero " << numero << " e par";
    }
    else{
        cout << "O numero " << numero << " e impar";
    }
    

    return 0;
}