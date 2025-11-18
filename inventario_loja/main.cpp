#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <algorithm>
#include <numeric>
#include <iomanip>

using namespace std;

class Produto {
private:
    string nome_;
    string categoria_;
    double preco_;
    int estoque_;

public:
    // Armazena dados básicos do produto
    Produto(string n, string c, double p, int e)
        : nome_(std::move(n)), categoria_(std::move(c)), preco_(p), estoque_(e) {}

    const string& getNome() const { return nome_; }
    const string& getCategoria() const { return categoria_; }
    double getPreco() const { return preco_; }
    int getEstoque() const { return estoque_; }

    void setEstoque(int novoEstoque) { estoque_ = novoEstoque; }
};

class Inventario {
private:
    map<string, Produto> produtos_;        // Produtos indexados pelo nome
    map<string, double> valorPorCategoria_; // Valor total por categoria
    list<string> historicoVendas_;          // Registro simples das vendas

public:
    void adicionarProduto(Produto p) {
        string nome = p.getNome();
        string categoria = p.getCategoria();

        if (produtos_.count(nome)) {
            cerr << "Erro: Produto '" << nome << "' já existe." << endl;
            return;
        }

        double valor = p.getPreco() * p.getEstoque();
        produtos_.emplace(std::move(nome), std::move(p));
        valorPorCategoria_[categoria] += valor;
    }

    const Produto* buscarProduto(const string& nome) const {
        auto it = produtos_.find(nome);
        if (it != produtos_.end()) return &(it->second);
        return nullptr;
    }

    bool registrarVenda(const string& nome, int quantidade) {
        auto it = produtos_.find(nome);
        if (it == produtos_.end()) {
            cout << "Produto nao encontrado.\n";
            return false;
        }

        Produto& p = it->second;

        if (p.getEstoque() < quantidade) {
            cout << "Estoque insuficiente. Disponível: " << p.getEstoque() << "\n";
            return false;
        }

        p.setEstoque(p.getEstoque() - quantidade);
        valorPorCategoria_[p.getCategoria()] -= p.getPreco() * quantidade;
        historicoVendas_.push_back(nome + " x" + to_string(quantidade));

        cout << "Venda registrada! Novo estoque de " << nome << ": " << p.getEstoque() << "\n";
        return true;
    }

    void listarPorCategoria(const string& cat) const {
        cout << "Produtos da categoria '" << cat << "':\n";
        bool encontrado = false;

        for (const auto& pair : produtos_) {
            const Produto& p = pair.second;
            if (p.getCategoria() == cat) {
                encontrado = true;
                cout << "- " << p.getNome() << " | Preco: R$ "
                     << fixed << setprecision(2) << p.getPreco()
                     << " | Estoque: " << p.getEstoque() << "\n";
            }
        }
        if (!encontrado) cout << "(Nenhum produto encontrado nesta categoria.)\n";
    }

    double calcularValorTotal() const {
        return accumulate(
            produtos_.begin(), produtos_.end(), 0.0,
            [](double total, const auto& pair) {
                const Produto& p = pair.second;
                return total + (p.getPreco() * p.getEstoque());
            }
        );
    }

    void listarValorPorCategoria() const {
        cout << "\n## Valor Total do Inventario por Categoria ##\n";
        for (const auto& pair : valorPorCategoria_) {
            cout << pair.first << ": R$ " << fixed << setprecision(2) << pair.second << "\n";
        }
    }

    void listarHistoricoVendas() const {
        cout << "\n## Historico de Vendas ##\n";
        if (historicoVendas_.empty()) {
            cout << "(Nenhuma venda registrada.)\n";
            return;
        }
        for (const auto& item : historicoVendas_) cout << "- " << item << "\n";
    }
};

int main() {
    Inventario inv;

    inv.adicionarProduto(Produto("Notebook", "Eletronicos", 3500.0, 10));
    inv.adicionarProduto(Produto("Mouse", "Eletronicos", 80.0, 50));
    inv.adicionarProduto(Produto("Camiseta", "Vestuario", 50.0, 100));

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