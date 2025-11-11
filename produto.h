#ifndef PRODUTO_H
#define PRODUTO_H

#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class Produto {
private:
    string nome;
    string categoria;
    double preco;
    int estoque;

public:
    Produto(string nome, string categoria, double preco, int estoque);

    // Getters
    string getNome() const;
    string getCategoria() const;
    double getPreco() const;
    int getEstoque() const;

    // Métodos
    void adicionarAoEstoque(int quantidade);
    bool removerDoEstoque(int quantidade);
    void exibir() const;
};

#endif
