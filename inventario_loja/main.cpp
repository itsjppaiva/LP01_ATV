#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <algorithm>
#include <numeric>
#include <iomanip>

using namespace std;

// Representa um único item no inventário
class Produto {
private:
    string nome_;
    string categoria_;
    double preco_;
    int estoque_;

public:
    // Construtor: usa move semantics para eficiência com strings
    explicit Produto(string n, string c, double p, int e)
        : nome_(std::move(n)), categoria_(std::move(c)), preco_(p), estoque_(e) {}

    // Getters constantes para acessar os dados do produto
    const string& getNome() const { return nome_; }
    const string& getCategoria() const { return categoria_; }
    double getPreco() const { return preco_; }
    int getEstoque() const { return estoque_; }

    // Única forma de modificar o estoque
    void setEstoque(int novoEstoque) { estoque_ = novoEstoque; }
};

class Inventario {
private:
    // Armazena produtos. Usamos map para busca rápida pelo nome (O(log N)).
    map<string, Produto> produtos_;
    
    // Total de valor em estoque, agrupado por categoria.
    map<string, double> valorPorCategoria_;
    
    // Lista para registrar as vendas. List é eficiente para inserção no final.
    list<string> historicoVendas_;

public:
    // Adiciona um novo produto ao inventário.
    void adicionarProduto(Produto p) {
        string nome = p.getNome();
        string categoria = p.getCategoria();
        
        // Evita duplicatas
        if (produtos_.count(nome)) {
            cerr << "Erro: Produto '" << nome << "' já existe." << endl;
            return;
        }

        double valor = p.getPreco() * p.getEstoque();
        
        // Insere o produto no map usando move semantics
        produtos_.emplace(std::move(nome), std::move(p)); 

        valorPorCategoria_[categoria] += valor;
    }

    // Busca um produto pelo nome. Retorna ponteiro constante para evitar modificação externa.
    const Produto* buscarProduto(const string& nome) const {
        auto it = produtos_.find(nome);
        if (it != produtos_.end()) {
            return &(it->second);
        }
        return nullptr;
    }

    // Registra uma venda, atualizando o estoque e o valor por categoria.
    bool registrarVenda(const string& nome, int quantidade) {
        auto it = produtos_.find(nome);
        if (it == produtos_.end()) {
            cout << "Produto nao encontrado.\n";
            return false;
        }
        
        Produto& p = it->second; // Obtém a referência mutável
        
        if (p.getEstoque() < quantidade) {
            cout << "Estoque insuficiente. Disponível: " << p.getEstoque() << "\n";
            return false;
        }

        p.setEstoque(p.getEstoque() - quantidade);
        
        // Atualiza o valor total da categoria após a venda
        valorPorCategoria_[p.getCategoria()] -= p.getPreco() * quantidade;
        
        historicoVendas_.push_back(nome + " x" + to_string(quantidade));

        cout << "Venda registrada! Novo estoque de " << nome << ": " << p.getEstoque() << "\n";
        return true;
    }

    // Lista todos os produtos de uma categoria específica.
    void listarPorCategoria(const string& cat) const {
        cout << "Produtos da categoria '" << cat << "':\n";
        bool encontrado = false;
        
        for (const auto& pair : produtos_) {
            const Produto& p = pair.second;
            if (p.getCategoria() == cat) {
                encontrado = true;
                // Formata a saída do preço com duas casas decimais
                cout << "- " << p.getNome() << " | Preco: R$ " 
                     << fixed << setprecision(2) << p.getPreco() 
                     << " | Estoque: " << p.getEstoque() << "\n";
            }
        }
        if (!encontrado) {
            cout << "(Nenhum produto encontrado nesta categoria.)\n";
        }
    }

    // Calcula o valor total de todos os produtos no inventário.
    double calcularValorTotal() const {
        // Usa std::accumulate para calcular o total de forma concisa
        return accumulate(
            produtos_.begin(), produtos_.end(), 0.0,
            [](double total, const auto& pair) {
                const Produto& p = pair.second;
                return total + (p.getPreco() * p.getEstoque());
            }
        );
    }
    
    // Exibe o valor total do inventário para cada categoria.
    void listarValorPorCategoria() const {
        cout << "\n## Valor Total do Inventario por Categoria ##\n";
        for (const auto& pair : valorPorCategoria_) {
            cout << pair.first << ": R$ " << fixed << setprecision(2) << pair.second << "\n";
        }
    }

    // Exibe o histórico de vendas.
    void listarHistoricoVendas() const {
        cout << "\n## Historico de Vendas ##\n";
        if (historicoVendas_.empty()) {
            cout << "(Nenhuma venda registrada.)\n";
            return;
        }
        for (const auto& item : historicoVendas_)
            cout << "- " << item << "\n";
    }
};

int main() {
    Inventario inv;

    // Adicionando produtos para teste
    inv.adicionarProduto(Produto("Notebook", "Eletronicos", 3500.0, 10));
    inv.adicionarProduto(Produto("Mouse", "Eletronicos", 80.0, 50));
    inv.adicionarProduto(Produto("Camiseta", "Vestuario", 50.0, 100));

    // Exemplos de uso
    inv.listarPorCategoria("Eletronicos");

    cout << "\n--- Registrar Venda ---\n";
    inv.registrarVenda("Mouse", 5);
    inv.registrarVenda("Camiseta", 10);

    cout << "\n--- Resumo ---\n";
    inv.listarValorPorCategoria();
    cout << "Valor total do inventario: R$ " 
         << fixed << setprecision(2) << inv.calcularValorTotal() << "\n";

    inv.listarHistoricoVendas();

    return 0;
}