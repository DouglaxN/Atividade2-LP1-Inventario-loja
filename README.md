# 🏪 Sistema de Inventário de Loja (C++17)

> Um sistema simples de **controle de inventário de loja**, desenvolvido em **C++17** usando a **STL (Standard Template Library)**.  
> O projeto simula um fluxo de gerenciamento de estoque e vendas. Este sistema permite cadastrar produtos, controlar estoque, gerenciar categorias e registrar vendas com histórico.  

---

## ⚙️ Funcionalidades

✅ **Adicionar produtos** com nome, categoria, preço e estoque.  
✅ **Atualização automática** caso o produto já exista (estoque é somado).  
✅ **Categorias e nomes insensíveis a maiúsculas/minúsculas**, mas mantêm o formato original.  
✅ **Valores monetários decimais** (aceita `15.90` ou `15,90`).  
✅ **Listar produtos por categoria**.  
✅ **Buscar produto por nome** (case-insensitive).  
✅ **Cálculo automático do valor total do inventário**.  
✅ **Registro de vendas** com atualização de estoque e histórico.  
✅ **Histórico de vendas completo** listando produtos e quantidades vendidas.  

---

## 🧩 Estrutura do Projeto

```

Atividade2-LP1-Inventario-loja/
├── main.cpp        # Código principal e interface de menu
├── produto.cpp     # Implementação da classe Produto
├── produto.h       # Definição da classe Produto
└── README.md       # Documentação do projeto

````

---

## 🧱 Classe `Produto`

A classe `Produto` representa cada item do inventário e implementa operações básicas de estoque.

| Atributo  | Tipo    | Descrição |
|------------|----------|------------|
| `nome` | `string` | Nome do produto |
| `categoria` | `string` | Categoria do produto |
| `preco` | `double` | Preço unitário |
| `estoque` | `int` | Quantidade em estoque |

Principais métodos:
- `adicionarAoEstoque(int quantidade)`
- `removerDoEstoque(int quantidade)`
- `exibir() const`

---

## 💻 Execução

### 🔧 Compilação

> É necessário um compilador compatível com **C++17** (ex: `g++` ou `clang++`).

```bash
g++ -std=c++17 main.cpp produto.cpp -o inventario

# ou

clang++ -std=c++17 main.cpp produto.cpp -o inventario
````

### ▶️ Execução

```bash
./inventario
```

---

## 🧠 Exemplo de Uso

```bash
========= 🏪 INVENTÁRIO DE LOJA =========
1. Adicionar produto
2. Buscar produto por nome
3. Listar produtos por categoria
4. Calcular valor total do inventário
5. Registrar venda
6. Exibir histórico de vendas
0. Sair
=========================================
Escolha uma opção: 1

Nome do produto: Lapis
Categorias existentes:
 (Nenhuma categoria cadastrada ainda)
Digite a categoria (ou nova para criar): Material Escolar
Preço (ex: 15.90 ou 15,90): R$2.00
Estoque a adicionar: 10
✅ Produto "Lapis" adicionado com sucesso!

Escolha uma opção: 1
Nome do produto: lapis
Categorias existentes:
 - Material Escolar
Digite a categoria (ou nova para criar): material escolar
Preço (ex: 15.90 ou 15,90): R$2.00
Estoque a adicionar: 5
🔄 Produto "Lapis" já existia. Estoque atualizado para 15 unidades.
```

---

## 📊 Exemplo de Saída

```bash
📂 Produtos na categoria [Material Escolar]:
📦 Lapis | Categoria: Material Escolar | Preço: R$2.00 | Estoque: 15

💰 Valor total do inventário: R$30.00

📜 Histórico de vendas:
- Lapis (2x)
```

---

## 🧠 Decisões Técnicas

* **C++17:** uso de structured bindings (`auto& [key, value]`) e `std::transform` para conversão de strings.
* **STL Containers:**

  * `vector` → lista de produtos
  * `set` → categorias únicas
  * `map` → controle de valores e contagem
  * `list` → histórico de vendas
* **Case-insensitive handling** via `std::transform` + `tolower`.
* **Formatação monetária** com `std::fixed` e `std::setprecision(2)`.

---

## 🚀 Futuras Implementações (versão corporativa)

### 💾 Persistência de Dados

* Armazenamento em arquivo `.csv` ou `.json`.
* Integração com banco de dados (SQLite, MySQL).
* Sistema de backup automático.

### 🧑‍💼 Usuários e Permissões

* Sistema de login com níveis de acesso (Administrador, Vendedor, Gerente).
* Log de auditoria com rastreamento de ações.

### 🌐 Interface Gráfica e Web

* Interface GUI com **Qt** ou **ImGui**.
* API REST com **C++ REST SDK** ou backend em Flask/Python.
* Dashboard web com gráficos em tempo real.

### 📈 Relatórios e Análises

* Ranking de produtos mais vendidos.
* Alertas automáticos de baixo estoque.
* Exportação de relatórios para PDF/Excel.

### 🧩 Modularização e Testes

* Separar módulos: Inventário / Vendas / Relatórios / UI.
* Implementar **testes unitários (Google Test)**.
* Gerar documentação automática com **Doxygen**.

### 🔐 Segurança e Resiliência

* Validação rigorosa de entradas do usuário.
* Criptografia de dados sensíveis.
* Logs persistentes e tratamento avançado de exceções.

---

## 👨🏻‍💻 Autor

**Douglas Silva**
Desenvolvedor e pesquisador em Bioinformática
📧 Contato: [GitHub](https://github.com/) • [LinkedIn](https://linkedin.com/)

Projeto desenvolvido como parte da disciplina **Linguagem de Programação I**, com foco em **STL e boas práticas em C++**.
