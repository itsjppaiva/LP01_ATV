#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <list>
#include <algorithm>
#include <numeric>
#include <iomanip>

using namespace std;

class Produto {
private:
    string nome;
    string categoria;
    double preco;
    int estoque;

public:
    Produto(string n, string c, double p, int e)
        : nome(std::move(n)), categoria(std::move(c)), preco(p), estoque(e) {}

    const string& getNome() const { return nome; }
    const string& getCategoria() const { return categoria; }
    double getPreco() const { return preco; }
    int getEstoque() const { return estoque; }
    void setEstoque(int e) { estoque = e; }
};

class Inventario {
private:
    vector<Produto> produtos;               // Lista de produtos
    set<string> categorias;                 // Categorias únicas
    map<string, int> contagemPorCategoria;  // Contagem de produtos por categoria
    map<string, double> valorPorCategoria;  // Valor total por categoria
    list<string> historicoVendas;           // Histórico de vendas

public:
    // Adiciona um novo produto ao inventário e atualiza estatísticas
    void adicionarProduto(const Produto& p) {
        produtos.push_back(p);
        categorias.insert(p.getCategoria());
        contagemPorCategoria[p.getCategoria()]++;
        valorPorCategoria[p.getCategoria()] += p.getPreco() * p.getEstoque();
    }

    // Procura um produto pelo nome
    Produto* buscarProduto(const string& nome) {
        for (auto& p : produtos) {
            if (p.getNome() == nome) return &p;
        }
        return nullptr;
    }

    // Lista produtos que pertencem a uma categoria específica
    void listarPorCategoria(const string& cat) const {
        cout << "Produtos da categoria '" << cat << "':\n";
        bool achou = false;
        for (const auto& p : produtos) {
            if (p.getCategoria() == cat) {
                achou = true;
                cout << "- " << p.getNome() << " | Preco: R$ "
                     << fixed << setprecision(2) << p.getPreco()
                     << " | Estoque: " << p.getEstoque() << "\n";
            }
        }
        if (!achou) cout << "Nenhum produto nesta categoria.\n";
    }

    // Registra uma venda, atualiza estoque e valor da categoria
    bool registrarVenda(const string& nome, int quantidade) {
        Produto* p = buscarProduto(nome);
        if (!p) {
            cout << "Produto nao encontrado.\n";
            return false;
        }
        if (p->getEstoque() < quantidade) {
            cout << "Estoque insuficiente.\n";
            return false;
        }

        p->setEstoque(p->getEstoque() - quantidade);
        valorPorCategoria[p->getCategoria()] -= p->getPreco() * quantidade;
        historicoVendas.push_back(nome + " x" + to_string(quantidade));

        cout << "Venda registrada! Novo estoque: " << p->getEstoque() << "\n";
        return true;
    }

    // Soma o valor total do inventário
    double calcularValorTotal() const {
        double total = 0;
        for (const auto& p : produtos)
            total += p.getPreco() * p.getEstoque();
        return total;
    }

    // Mostra o valor total agrupado por categoria
    void listarValorPorCategoria() const {
        cout << "\nValor por categoria:\n";
        for (const auto& par : valorPorCategoria) {
            cout << par.first << ": R$ " << fixed << setprecision(2) << par.second << "\n";
        }
    }

    // Exibe o histórico de vendas realizadas
    void listarHistoricoVendas() const {
        cout << "\nHistorico de vendas:\n";
        if (historicoVendas.empty()) {
            cout << "Nenhuma venda registrada.\n";
            return;
        }
        for (const auto& item : historicoVendas)
            cout << "- " << item << "\n";
    }
};

int main() {
    Inventario inv;

    inv.adicionarProduto({"Notebook", "Eletronicos", 3500.0, 10});
    inv.adicionarProduto({"Mouse", "Eletronicos", 80.0, 50});
    inv.adicionarProduto({"Camiseta", "Vestuario", 50.0, 100});

    inv.listarPorCategoria("Eletronicos");

    cout << "\n--- Registrar Venda ---\n";
    inv.registrarVenda("Mouse", 5);
    inv.registrarVenda("Camiseta", 10);

    cout << "\n--- Resumo ---\n";
    inv.listarValorPorCategoria();
    cout << "Valor total do inventario: R$ " << fixed << setprecision(2)
         << inv.calcularValorTotal() << "\n";

    inv.listarHistoricoVendas();
}
