#include <iostream>
#include <string>
using namespace std;

// // Criação do modelo de cliente
class Cliente {
private:
    string nome; 
    string cpf;  

public:
    // Construtor que inicializa o nome e o CPF
    Cliente(string n, string c) {
        nome = n;
        cpf = c;
    }

    // Retorna o nome do cliente
    string getNome() const {
        return nome;
    }

    // Retorna o CPF do cliente
    string getCpf() const {
        return cpf;
    }
};

// Criação do modelo de conta bancária
class ContaBancaria {
private:
    int numero;       
    double saldo;      
    Cliente titular;   

public:
    // Construtor com saldo opcional (padrão = 0)
    ContaBancaria(int num, Cliente t, double s = 0.0)
        : numero(num), titular(t), saldo(s) {}

    // Método para depositar um valor na conta
    void depositar(double valor) {
        if (valor > 0) {
            saldo += valor;
        }
    }

    // Método para verificar saldo e realizar saque
    void sacar(double valor) {
        if (valor > 0 && saldo >= valor) {
            saldo -= valor;
        } else {
            cout << "Saldo insuficiente para saque na conta " << numero << endl;
        }
    }

    // Método para transferir valor para outra conta
    void transferir(double valor, ContaBancaria &destino) {
        if (valor > 0 && saldo >= valor) {
            saldo -= valor;
            destino.depositar(valor);
            cout << "Transferido: R$ " << valor << " da conta " << numero
                 << " para a conta " << destino.numero << endl;
        } else {
            cout << "Saldo insuficiente para transferir R$ " << valor
                 << " da conta " << numero << endl;
        }
    }

    // Sobrecarga do método transferir para duas contas destino
    void transferir(double valor, ContaBancaria &destino1, ContaBancaria &destino2) {
        double metade = valor / 2.0;
        if (valor > 0 && saldo >= valor) {
            saldo -= valor;
            destino1.depositar(metade);
            destino2.depositar(metade);
            cout << "Transferido: R$ " << metade
                 << " para cada conta (" << destino1.numero
                 << " e " << destino2.numero << ") da conta " << numero << endl;
        } else {
            cout << "Saldo insuficiente para transferir R$ " << valor
                 << " da conta " << numero << endl;
        }
    }

    // Exibe o saldo atual da conta
    void exibirSaldo() const {
        cout << "Saldo atual da conta " << numero << ": R$ " << saldo << endl;
    }

    // Exibe todas as informações da conta e do titular
    void exibirInformacoes() const {
        cout << "Titular: " << titular.getNome()
             << ", CPF: " << titular.getCpf() << endl;
        cout << "Numero da Conta: " << numero
             << ", Saldo: R$ " << saldo << endl;
    }
};

int main() {
    // Criação dos clientes
    Cliente cliente1("Ana", "111.111.111-11");
    Cliente cliente2("Bruno", "222.222.222-22");
    Cliente cliente3("Carla", "333.333.333-33");

    // Criação das contas bancárias com saldos iniciais
    ContaBancaria conta1(1001, cliente1, 1000.0);
    ContaBancaria conta2(1002, cliente2);
    ContaBancaria conta3(1003, cliente3);

    // Exibe o saldo inicial da conta de Ana
    conta1.exibirSaldo();

    // Ana transfere R$200 para Bruno
    conta1.transferir(200.0, conta2);

    // Ana transfere R$300 divididos entre Bruno e Carla
    conta1.transferir(300.0, conta2, conta3);

    // Exibe os saldos finais
    cout << endl;
    conta1.exibirInformacoes();
    conta2.exibirInformacoes();
    conta3.exibirInformacoes();

    return 0;
}
