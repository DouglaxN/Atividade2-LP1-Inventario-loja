#include "produto.h"

Produto::Produto(string nome, string categoria, double preco, int estoque)
    : nome(nome), categoria(categoria), preco(preco), estoque(estoque) {
    if (preco < 0 || estoque < 0)
        throw invalid_argument("❌ Preço e estoque devem ser valores positivos.");
}

// Getters
string Produto::getNome() const { return nome; }
string Produto::getCategoria() const { return categoria; }
double Produto::getPreco() const { return preco; }
int Produto::getEstoque() const { return estoque; }

// Métodos
void Produto::adicionarAoEstoque(int quantidade) {
    if (quantidade <= 0)
        throw invalid_argument("❌ Quantidade a adicionar deve ser positiva.");
    estoque += quantidade;
}

bool Produto::removerDoEstoque(int quantidade) {
    if (quantidade <= 0) {
        cout << "❌ Quantidade inválida para remoção.\n";
        return false;
    }
    if (quantidade > estoque) {
        cout << "⚠️ Estoque insuficiente! Estoque atual: " << estoque << "\n";
        return false;
    }
    estoque -= quantidade;
    cout << "✅ Venda registrada. Novo estoque: " << estoque << "\n";
    return true;
}

void Produto::exibir() const {
    cout << "📦 " << nome
         << " | Categoria: " << categoria
         << " | Preço: R$" << preco
         << " | Estoque: " << estoque << "\n";
}
