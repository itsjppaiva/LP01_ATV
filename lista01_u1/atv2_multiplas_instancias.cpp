#include <iostream>
#include <string>
using namespace std;

class Livro {
public:
    string titulo;
    string autor;
    int paginas;
    
    void exibirLivro() {
        cout << "Titulo: " << titulo << endl;
        cout << "Autor: " << autor << endl; 
        cout << "Paginas: " << paginas << endl;
        cout << endl;
    }
};

int main() {
    Livro livro1, livro2, livro3;
    
    livro1.titulo = "A volta dos que nao foram";
    livro1.autor = "Joao Paulo";
    livro1.paginas = 239;
    
    livro2.titulo = "Sextou";
    livro2.autor = "Aquele que vos fala";
    livro2.paginas = 61;
    
    livro3.titulo = "Macacos me mordam";
    livro3.autor = "Anonimus";
    livro3.paginas = 81;
    
    livro1.exibirLivro();
    livro2.exibirLivro();
    livro3.exibirLivro();
    
    return 0;
}
