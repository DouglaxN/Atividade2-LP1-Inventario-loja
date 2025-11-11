#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <algorithm>
#include <iomanip>
#include <cctype>
#include "produto.h"

using namespace std;

// Função auxiliar para converter string para minúsculas
string toLowerCase(string s) {
    transform(s.begin(), s.end(), s.begin(),
              [](unsigned char c){ return tolower(c); });
    return s;
}

void mostrarCategorias(const set<string>& categorias) {
    if (categorias.empty()) {
        cout << "(Nenhuma categoria cadastrada ainda)\n";
        return;
    }
    cout << "Categorias existentes:\n";
    for (const auto& cat : categorias)
        cout << " - " << cat << "\n";
}

// Buscar produto (case-insensitive)
Produto* buscarProduto(vector<Produto>& produtos, const string& nome, const string& categoria = "") {
    string nomeLower = toLowerCase(nome);
    string categoriaLower = toLowerCase(categoria);

    for (auto& p : produtos) {
        if (toLowerCase(p.getNome()) == nomeLower) {
            if (categoria.empty() || toLowerCase(p.getCategoria()) == categoriaLower)
                return &p;
        }
    }
    return nullptr;
}

void adicionarProduto(vector<Produto>& produtos,
                      set<string>& categorias,
                      map<string,int>& contagem,
                      map<string,double>& valorTotal,
                      map<string,string>& categoriaMap,
                      const Produto& novoProduto) {
    string catLower = toLowerCase(novoProduto.getCategoria());

    // Se a categoria não existe ainda, registra versão original
    if (categoriaMap.find(catLower) == categoriaMap.end()) {
        categoriaMap[catLower] = novoProduto.getCategoria();
        categorias.insert(novoProduto.getCategoria());
    }

    // Verifica se o produto já existe (nome e categoria)
    Produto* existente = buscarProduto(produtos, novoProduto.getNome(), novoProduto.getCategoria());

    if (existente) {
        existente->adicionarAoEstoque(novoProduto.getEstoque());
        cout << "🔄 Produto \"" << existente->getNome() 
             << "\" já existia. Estoque atualizado para "
             << existente->getEstoque() << " unidades.\n";

        // Atualiza o valor total
        valorTotal[categoriaMap[catLower]] += novoProduto.getPreco() * novoProduto.getEstoque();
    } else {
        produtos.push_back(novoProduto);
        contagem[categoriaMap[catLower]]++;
        valorTotal[categoriaMap[catLower]] += novoProduto.getPreco() * novoProduto.getEstoque();
        cout << "✅ Produto \"" << novoProduto.getNome() << "\" adicionado com sucesso!\n";
    }
}

void listarPorCategoria(const vector<Produto>& produtos,
                        const string& categoria,
                        map<string,string>& categoriaMap) {
    string catLower = toLowerCase(categoria);

    if (categoriaMap.find(catLower) == categoriaMap.end()) {
        cout << "⚠️ Categoria não encontrada!\n";
        return;
    }

    string catOriginal = categoriaMap[catLower];
    cout << "\n📂 Produtos na categoria [" << catOriginal << "]:\n";

    bool encontrou = false;
    for (const auto& p : produtos)
        if (toLowerCase(p.getCategoria()) == catLower) {
            p.exibir();
            encontrou = true;
        }

    if (!encontrou) cout << "⚠️ Nenhum produto encontrado nessa categoria.\n";
}

double calcularValorTotal(const map<string, double>& valorTotal) {
    double soma = 0.0;
    for (auto& [cat, valor] : valorTotal)
        soma += valor;
    return soma;
}

void registrarVenda(vector<Produto>& produtos,
                    list<string>& historico,
                    map<string,double>& valorTotal,
                    map<string,string>& categoriaMap,
                    const string& nome, int quantidade) {
    Produto* p = buscarProduto(produtos, nome);
    if (p) {
        if (p->removerDoEstoque(quantidade)) {
            historico.push_back(p->getNome() + " (" + to_string(quantidade) + "x)");
            string catLower = toLowerCase(p->getCategoria());
            valorTotal[categoriaMap[catLower]] -= p->getPreco() * quantidade;
        }
    } else {
        cout << "❌ Produto \"" << nome << "\" não encontrado!\n";
    }
}

void exibirHistorico(const list<string>& historico) {
    cout << "\n📜 Histórico de vendas:\n";
    if (historico.empty()) {
        cout << "Nenhuma venda registrada.\n";
        return;
    }
    for (const auto& item : historico)
        cout << "- " << item << "\n";
}

void menu() {
    cout << "\n========= 🏪 INVENTÁRIO DE LOJA =========\n";
    cout << "1. Adicionar produto\n";
    cout << "2. Buscar produto por nome\n";
    cout << "3. Listar produtos por categoria\n";
    cout << "4. Calcular valor total do inventário\n";
    cout << "5. Registrar venda\n";
    cout << "6. Exibir histórico de vendas\n";
    cout << "0. Sair\n";
    cout << "=========================================\n";
    cout << "Escolha uma opção: ";
}

int main() {
    vector<Produto> produtos;
    set<string> categorias;
    map<string, int> contagem;
    map<string, double> valorTotal;
    map<string, string> categoriaMap;
    list<string> historico;

    cout << fixed << setprecision(2);

    int opcao;
    do {
        menu();
        cin >> opcao;
        cin.ignore();

        if (opcao == 1) {
            string nome, categoria, precoStr;
            double preco;
            int estoque;

            cout << "Nome do produto: ";
            getline(cin, nome);

            mostrarCategorias(categorias);
            cout << "Digite a categoria (ou nova para criar): ";
            getline(cin, categoria);

            string catLower = toLowerCase(categoria);
            string catFinal = (categoriaMap.find(catLower) != categoriaMap.end())
                                ? categoriaMap[catLower] : categoria;

            cout << "Preço (ex: 15.90 ou 15,90): R$";
            getline(cin, precoStr);
            replace(precoStr.begin(), precoStr.end(), ',', '.');
            preco = stod(precoStr);

            cout << "Estoque a adicionar: ";
            cin >> estoque;

            try {
                Produto p(nome, catFinal, preco, estoque);
                adicionarProduto(produtos, categorias, contagem, valorTotal, categoriaMap, p);
            } catch (exception& e) {
                cout << e.what() << "\n";
            }

        } else if (opcao == 2) {
            string nome;
            cout << "Digite o nome do produto: ";
            getline(cin, nome);
            Produto* p = buscarProduto(produtos, nome);
            if (p)
                p->exibir();
            else
                cout << "❌ Produto não encontrado.\n";

        } else if (opcao == 3) {
            mostrarCategorias(categorias);
            string categoria;
            cout << "Escolha a categoria: ";
            getline(cin, categoria);
            listarPorCategoria(produtos, categoria, categoriaMap);

        } else if (opcao == 4) {
            cout << "\n💰 Valor total do inventário: R$" << calcularValorTotal(valorTotal) << "\n";

        } else if (opcao == 5) {
            string nome;
            int qtd;
            cout << "Produto: ";
            getline(cin, nome);
            cout << "Quantidade vendida: ";
            cin >> qtd;
            registrarVenda(produtos, historico, valorTotal, categoriaMap, nome, qtd);

        } else if (opcao == 6) {
            exibirHistorico(historico);

        } else if (opcao == 0) {
            cout << "👋 Saindo...\n";

        } else {
            cout << "❌ Opção inválida!\n";
        }

    } while (opcao != 0);

    return 0;
}
