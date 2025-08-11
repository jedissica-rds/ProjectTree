# Tabela Hash com Árvores AVL em Cada Bucket

[![C++](https://img.shields.io/badge/C%2B%2B-11-blue.svg)](https://isocpp.org/)

[![Estruturas de Dados](https://img.shields.io/badge/Estruturas%20de%20Dados-AVL%20Tree-green)](#)

[![Status](https://img.shields.io/badge/Status-Concluído-success)](#)


Este projeto foi desenvolvido para a disciplina **Algoritmos e Estrutura de Dados I**  e implementa uma **Tabela Hash** onde **cada posição é uma árvore AVL**.  
Essa abordagem mantém os dados ordenados e garante operações de inserção e busca rápidas mesmo com colisões.

---

## Funcionalidades

- Inserção de palavras normalizadas (somente letras)  
- Busca de palavras na tabela hash  
- Cálculo da **altura da AVL** onde a palavra está armazenada  
- Impressão das palavras de um bucket em **ordem alfabética**  
- Estrutura otimizada para textos grandes  

---

## Estrutura do Projeto
```
main.cpp
│
├── template<class T> Node # Nó da árvore AVL
├── template<class T> BinarySearchTreeAVL
│ ├── insert / remove # Inserção e remoção balanceada
│ ├── balance / rotateLeft / rotateRight
│ ├── search # Busca em O(log n)
│ ├── inorder/preorder/postorder
│
├── template<class T> HashTable
│ ├── SIZE = 151
│ ├── insert / search / empty / length
│ ├── hash() # Função de dispersão
│
├── Funções auxiliares
│ ├── normalizeKey # Remove caracteres não alfabéticos
│ ├── processLine # Processa texto e insere palavras
│ ├── getKey # Extrai chave de busca após "###"

---
```

## Diagrama Simplificado
```
Tabela Hash [151 posições]
        │
        ├── Bucket[0] → (AVL Tree) → [palavras ordenadas]
        ├── Bucket[1] → (AVL Tree) → [palavras ordenadas]
        ├── ...
        └── Bucket[150] → (AVL Tree) → [palavras ordenadas]
```

## Autoria
```
Jessica Rodrigues
Ana Klissia Furtado Martins
```
