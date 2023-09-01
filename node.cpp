#ifndef NODE_CPP
#define NODE_CPP

#include "node.h"
//Cria o no com seus dois filhos
template <typename T>
Node<T>::Node(T val, Node<T> *l, Node<T> *r)
{
  value = val;
  left = l;
  right = r;
}
//Retorna o valor armazenado no no
template <typename T>
T Node<T>::getValue()
{
  return this->value;
}
//Atualiza o valor do no
template <typename T>
void Node<T>::setValue(T newValue)
{
  this->value = newValue;
}
//Retorna o filho da esquerda
template <typename T>
Node<T> *Node<T>::getLeft()
{
  return this->left;
}
//Atualiza o no da esquerda
template <typename T>
void Node<T>::setLeft(Node<T> *newLeft)
{
  this->left = newLeft;
}
//Retorna valor do no da direita
template <typename T>
Node<T> *Node<T>::getRight()
{
  return this->right;
}
//Atualiza o valor do no da direita
template <typename T>
void Node<T>::setRight(Node<T> *newRight)
{
  this->right = newRight;
}
//Retorna o conteudo do no
template <typename T>
string Node<T>::getCode()
{
  return this->code;
}
//Atualiza o conteudo do no
template <typename T>
void Node<T>::setCode(string newCode)
{
  this->code = newCode;
}

#endif