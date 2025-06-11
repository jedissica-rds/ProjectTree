// main.cpp
// ProjectTree
// Created by Jessica Rodrigues on 07/06/25.

#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

template<typename T>
class Node {
private:
    T item;

public:
    int bal;
    Node<T>* right;
    Node<T>* left;
    Node(): right(nullptr), left(nullptr) {}
    Node(T it): item(it), bal(0), right(nullptr), left(nullptr) {}
    T getItem();
    void setItem(const T& value);
};

template<typename T>
T Node<T>::getItem() {
    return item;
}

template<typename T>
void Node<T>::setItem(const T& value) {
    item = value;
}

template<typename T>
class BinarySearchTreeAVL {
private:
    Node<T>* root;
    void insert(T item, Node<T>*& p);
    void remove(T& item, Node<T>*& p);
    bool search(T& item, Node<T>*& p);
    void preorderTraversal(Node<T>* node);
    void inorderTraversal(Node<T>* node);
    void postorderTraversal(Node<T>* node);

public:
    BinarySearchTreeAVL() : root(nullptr) {}
    void create();
    void insert(T item);
    void remove(T& item);
    void remove_aux(Node<T>*& q, Node<T>*& r);
    bool search(T& item);
    void preorderTraversal();
    void inorderTraversal();
    void postorderTraversal();
    Node<T>* getRoot();
    int size(Node<T>* node);
    int size();
    int getHeight();
    int height(Node<T>* p);
    void updateBalance(Node<T>* p);
    Node<T>* rotateLeft(Node<T>* p);
    Node<T>* rotateRight(Node<T>* p);
    Node<T>* balance(Node<T>* p);
};

template<typename T>
void BinarySearchTreeAVL<T>::create() {
    root = nullptr;
}

template<typename T>
Node<T>* BinarySearchTreeAVL<T>::getRoot() {
    return root;
}

template<typename T>
bool BinarySearchTreeAVL<T>::search(T& x, Node<T>*& p) {
    if (p == nullptr) return false;
    else if (x < p->getItem()) return search(x, p->left);
    else if (x > p->getItem()) return search(x, p->right);
    else {
        x = p->getItem();
        return true;
    }
}

template<typename T>
bool BinarySearchTreeAVL<T>::search(T& x) {
    return search(x, root);
}

template<typename T>
void BinarySearchTreeAVL<T>::preorderTraversal() {
    preorderTraversal(root);
}

template<typename T>
void BinarySearchTreeAVL<T>::preorderTraversal(Node<T>* p) {
    if (p != nullptr) {
        cout << p->getItem() << " ";
        preorderTraversal(p->left);
        preorderTraversal(p->right);
    }
}

template<typename T>
void BinarySearchTreeAVL<T>::inorderTraversal() {
    inorderTraversal(root);
}

template<typename T>
void BinarySearchTreeAVL<T>::inorderTraversal(Node<T>* p) {
    if (p != nullptr) {
        inorderTraversal(p->left);
        cout << p->getItem() << " ";
        inorderTraversal(p->right);
    }
}

template<typename T>
void BinarySearchTreeAVL<T>::postorderTraversal() {
    postorderTraversal(root);
}

template<typename T>
void BinarySearchTreeAVL<T>::postorderTraversal(Node<T>* p) {
    if (p != nullptr) {
        postorderTraversal(p->left);
        postorderTraversal(p->right);
        cout << p->getItem() << " ";
    }
}

template<typename T>
void BinarySearchTreeAVL<T>::insert(T x, Node<T>*& p) {
    if (p == nullptr) {
        p = new Node<T>(x);
    } else if (x < p->getItem()) {
        insert(x, p->left);
        p = balance(p);
    } else if (x > p->getItem()) {
        insert(x, p->right);
        p = balance(p);
    }
}

template<typename T>
void BinarySearchTreeAVL<T>::insert(T item) {
    insert(item, root);
}

template<typename T>
void BinarySearchTreeAVL<T>::remove_aux(Node<T>*& q, Node<T>*& r) {
    if (r->right != nullptr) {
        remove_aux(q, r->right);
        r = balance(r);
    } else {
        q->setItem(r->getItem());
        Node<T>* aux = r;
        r = r->left;
        delete aux;
    }
}

template<typename T>
void BinarySearchTreeAVL<T>::remove(T& x, Node<T>*& p) {
    if (p == nullptr) return;
    else if (x < p->getItem()) {
        remove(x, p->left);
        p = balance(p);
    } else if (x > p->getItem()) {
        remove(x, p->right);
        p = balance(p);
    } else if (p->right == nullptr) {
        Node<T>* aux = p;
        p = p->left;
        delete aux;
    } else if (p->left == nullptr) {
        Node<T>* aux = p;
        p = p->right;
        delete aux;
    } else {
        remove_aux(p, p->left);
        p = balance(p);
    }
}

template<typename T>
void BinarySearchTreeAVL<T>::remove(T& item) {
    remove(item, root);
}

template<typename T>
int BinarySearchTreeAVL<T>::height(Node<T>* p) {
    if (p == nullptr) return 0;
    int hl = height(p->left);
    int hr = height(p->right);
    return 1 + max(hl, hr);
}

template<typename T>
void BinarySearchTreeAVL<T>::updateBalance(Node<T>* p) {
    if (p != nullptr) {
        int hl = height(p->left);
        int hr = height(p->right);
        p->bal = hr - hl;
    }
}

template<typename T>
Node<T>* BinarySearchTreeAVL<T>::rotateLeft(Node<T>* p) {
    Node<T>* q = p->right;
    p->right = q->left;
    q->left = p;
    updateBalance(p);
    updateBalance(q);
    return q;
}

template<typename T>
Node<T>* BinarySearchTreeAVL<T>::rotateRight(Node<T>* p) {
    Node<T>* q = p->left;
    p->left = q->right;
    q->right = p;
    updateBalance(p);
    updateBalance(q);
    return q;
}

template<typename T>
Node<T>* BinarySearchTreeAVL<T>::balance(Node<T>* p) {
    updateBalance(p);
    if (p->bal == 2) {
        if (p->right->bal < 0) p->right = rotateRight(p->right);
        p = rotateLeft(p);
    } else if (p->bal == -2) {
        if (p->left->bal > 0) p->left = rotateLeft(p->left);
        p = rotateRight(p);
    }
    return p;
}

template<typename T>
int BinarySearchTreeAVL<T>::size(Node<T>* node) {
    if (node == nullptr) return 0;
    return 1 + size(node->left) + size(node->right);
}

template<typename T>
int BinarySearchTreeAVL<T>::size() {
    return size(root);
}

template<typename T>
int BinarySearchTreeAVL<T>::getHeight() {
    return height(root);
}

string normalizeKey(const string& key) {
    string normalized;
    for (char c : key) {
        if (isalpha(c)) normalized += c;
    }
    return normalized;
}

#define SIZE 151

template <typename T>
struct HashTable {
private:
    BinarySearchTreeAVL<T> t[SIZE];

public:
    void insert(const string& key, T item);
    bool search(const string& key, T& item);
    int length();
    bool empty();
    void print(int index);
    BinarySearchTreeAVL<T> getTree(int index);
    int getAVLHeight(const string& key);
    unsigned long int hash(const string& key, unsigned long int m);
};

template <typename T>
BinarySearchTreeAVL<T> HashTable<T>::getTree(int index) {
    return t[index];
}

template <typename T>
void HashTable<T>::insert(const string& key, T item) {
    string normKey = normalizeKey(key);
    size_t index = hash(normKey, SIZE);
    if constexpr (is_same<T, string>::value) {
        T normItem = normalizeKey(item);
        t[index].insert(normItem);
    }
}

template <typename T>
bool HashTable<T>::search(const string& key, T& result) {
    string normKey = normalizeKey(key);
    size_t index = hash(normKey, SIZE);
    if constexpr (is_same<T, string>::value) {
        result = normalizeKey(result);
    }
    return t[index].search(result);
}

template <typename T>
int HashTable<T>::length() {
    int total = 0;
    for (int i = 0; i < SIZE; ++i) total += t[i].size();
    return total;
}

template <typename T>
bool HashTable<T>::empty() {
    return length() == 0;
}

template <typename T>
unsigned long int HashTable<T>::hash(const string& key, unsigned long int m) {
    unsigned long int hashValue = 0;
    unsigned long int n = key.length();
    for (size_t i = 0; i < n; ++i) {
        hashValue += key[i] * static_cast<unsigned long int>(pow(128, n - i - 1));
        hashValue %= m;
    }
    return hashValue;
}

template<typename T>
int HashTable<T>::getAVLHeight(const string& key) {
    string normKey = normalizeKey(key);
    size_t index = hash(normKey, SIZE);
    T temp = normKey;
    if (t[index].search(temp)) {
        return t[index].getHeight();
    }
    return -1;
}

template <typename T>
void HashTable<T>::print(int index) {
    if (t[index].size() > 0) {
        cout << "Index " << index << ": ";
        t[index].inorderTraversal();
        cout << endl;
    }
}

template <typename T>
string getKey(const string& line) {
    size_t pos = line.find("###");
    if (pos != string::npos) {
        string searchKey = line.substr(pos + 3);
        searchKey.erase(0, searchKey.find_first_not_of(" \t\n\r"));
        searchKey.erase(searchKey.find_last_not_of(" \t\n\r") + 1);
        return searchKey;
    }
    return "";
}

void processLine(HashTable<string>& table, const string& linha) {
    size_t i = 0;
    while (i < linha.size()) {
        while (i < linha.size() && !isalpha(linha[i])) i++;
        if (i >= linha.size()) break;
        size_t start = i;
        while (i < linha.size() && (isalpha(linha[i]) || linha[i] == '\'' || linha[i] == '-')) i++;
        string palavra = linha.substr(start, i - start);
        string cleaned = normalizeKey(palavra);
        if (!cleaned.empty()) table.insert(cleaned, cleaned);
    }
}

int main() {
    HashTable<string> avl;
    string linha;
    string searchLine;
    while (getline(cin, linha)) {
        if (linha.find("###") != string::npos) {
            searchLine = linha;
            break;
        }
        processLine(avl, linha);
    }
    string key = getKey<string>(searchLine);
    string result = normalizeKey(key);
    if (!result.empty()) {
        int h = avl.getAVLHeight(result);
        if (h != -1) cout << h << endl;
        else cout << "Nao encontrado" << endl;
    }
    return 0;
}
