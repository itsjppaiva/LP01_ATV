#include <iostream>
#include <string>
using namespace std;

class Retangulo {
public:  
    float largura;    
    float altura;      
    
    void calcularArea() {
        cout << "Area: " << largura*altura << endl;
    }
};

int main() {
    Retangulo retangulo1;
    
    retangulo1.largura = 20;
    retangulo1.altura = 10;
    
    retangulo1.calcularArea();
    
    return 0;
}
