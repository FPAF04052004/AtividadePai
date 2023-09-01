#ifndef BINARYTREE_CPP
#define BINARYTREE_CPP

#include <iostream>
#include "binarytree.h"
using namespace std;
//Inicializa a arvore com o no raiz vazio
template <typename T>
BinaryTree<T>::BinaryTree()
{
  root = nullptr;
}
//Inicializa a arvore atribuindo valor para a no raiz
template <typename T>
BinaryTree<T>::BinaryTree(T value)
{
  root = new Node<T>(value, nullptr, nullptr);
}

template <typename T>
BinaryTree<T>::BinaryTree(T value, BinaryTree<T> &l, BinaryTree<T> &r)
{
  root = new Node<T>(value, l.getRoot(), r.getRoot());
  // As duas árvores ficarão vazias, pois os nós raizes delas serão filhas da árvore criada
  l.setRoot(nullptr);
  r.setRoot(nullptr);
}
//Retorna o valor do no desejado
template <typename T>
Node<T> *BinaryTree<T>::getRoot()
{
  return root;
}
//Atualiza o valor do no desejado
template <typename T>
void BinaryTree<T>::setRoot(Node<T> *newRoot)
{
  root = newRoot;
}
// Implementei uma função recursiva para liberar os nós de forma recursiva
template <typename T>
void clear_rec(Node<T> *node)
{
  if (node != nullptr)
  {
    clear_rec(node->getLeft());
    clear_rec(node->getRight());
    delete node;
  }
}
//Chama a funcao de liberar memoria
template <typename T>
void BinaryTree<T>::clear()
{
  clear_rec(root);
  root = nullptr;
}
//Destrutor chama a funcoa que libera memoria
template <typename T>
BinaryTree<T>::~BinaryTree()
{
  clear();
}
//Retorna se o no esta vazio
template <typename T>
bool BinaryTree<T>::is_empty()
{
  return root == nullptr;
}
//Printa arvore usando pre-ordem
template <typename T>
void print_values_rec(Node<T> *node)
{
  if (node != nullptr)
  {
    cout << node->getValue() << " ";
    print_values_rec(node->getLeft());
    print_values_rec(node->getRight());
  }
}
//Chama a funcao recursiva para fazer a impressao
template <typename T>
void BinaryTree<T>::print_values()
{
  print_values_rec(root);
  cout << endl;
}
//Se o no nao estiver vazio e nem tiver filho, ele e folha
template <typename T>
bool BinaryTree<T>::is_leaf()
{
  return !is_empty() && root->getLeft() == nullptr && root->getRight() == nullptr;
}

template <typename T>
bool contains_rec(Node<T> *node, T value)
{
  if (node == nullptr)
    return false; // subárvore vazia
  else//Checa se a arvore contem determinado valor, percorrendo de forma  recursiva
    return node->getValue() == value ||
           contains_rec(node->getLeft(), value) ||
           contains_rec(node->getRight(), value);
}
//Chama o metodo de percorrimento recursivo
template <typename T>
bool BinaryTree<T>::contains(T value)
{
  return contains_rec(root, value);
}

#endif