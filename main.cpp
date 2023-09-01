// Turma 04: manhã, terça e quarta
// Luis Fernando Batista Lima - 538134
// Francisco Paulino Arruda Filho- 538451

#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include "binarytree.h"

using namespace std;
//Define as variaveis globais
#define T pair<int, unordered_set<string>>
//Cria o numero de doencas e o numero de sintomas
int n_doencas, n_sintomas;
//Cria um vetor com os nome das doencas e outro com o dos sintomas
vector<string> doencas;
vector<string> sintomas;
//Cria uma mapa para mapear as doencas por meio dos sintomas e da o diagnostico
unordered_map<string, unordered_set<string>> diagnosticos;

void obterDados()
{//Para obter a entrada de dados por meio do txt
  ifstream file("SintomasMenor.txt");
  //Abre o arquivo
  if (file.is_open())
  {
    string line;
    getline(file, line);
    //Transforma as strings de sintomas em um vetor de inteiros e da o devido espacamento
    n_doencas = stoi(line.substr(0, line.find(" ")));
    n_sintomas = stoi(line.substr(line.find(" ") + 1, line.size()));
    //Pega o nome das doencas e adiciona em um vetor
    for (int i = 0; i < n_doencas; i++)
    {
      getline(file, line);
      doencas.push_back(line);
    }
    //Pega o nome dos sintomas e adiciona em um vetor
    for (int i = 0; i < n_sintomas; i++)
    {
      getline(file, line);
      sintomas.push_back(line);
    }

    while (getline(file, line))
    {
      int cod_doenca = stoi(line.substr(0, line.find("\t")));
      string sequencia = line.substr(line.find("\t") + 1);

      string sem_tab;
      for (char c : sequencia)
      {
        if (c != '\t')
        {
          sem_tab += c;
        }
      }
      sequencia = sem_tab;
      diagnosticos[sequencia].insert(doencas[cod_doenca - 1]);
    }
    //Fecha o arquivo
    file.close();
  }
}
//Constroi a arvore de decisao
Node<T> *construirDecisionTree(int value, string doenca)
{
  Node<T> *no = new Node<T>({value, {}}, nullptr, nullptr);

  if (value == n_sintomas)
  {
    no->setValue({value, diagnosticos[doenca]});
    return no;
  }

  no->setLeft(construirDecisionTree(value + 1, doenca + '1'));
  no->setRight(construirDecisionTree(value + 1, doenca + '0'));

  return no;
}
//Da o diagnostico com base nos sintomas passado
void diagnosticar(Node<T> *no)
{
  if (no->getValue().first == n_sintomas)
  {
    if (no->getValue().second.size())
    {
      cout << "\nVoce provavelmente esta com alguma das seguintes doencas:" << endl;
      for (auto it : no->getValue().second)
      {
        cout << it << endl;
      }
      cout << "---------------------------------\n\n";
      return;
    }
    else
    {
      cout << "\nSem diagnostico" << endl;
      cout << "---------------------------------\n\n";
      return;
    }
  }
  //Cria variaveis auxilires para armazenar as respostas
  int pergunta = no->getValue().first;
  cout << "Voce esta sentindo " << sintomas[pergunta] << "? (Sim/Nao) ";
  string resposta;
  cin >> resposta;
  Node<int> *aux;
  //Faz as perguntas e vai contruindo a arvore com base nas respostas
  if (resposta == "Sim" || resposta == "sim" || resposta == "S" || resposta == "s")
  {
    diagnosticar(no->getLeft());
  }
  else
  {
    diagnosticar(no->getRight());
  }
}

int main()
{
  obterDados();
  //Cria a arvore de decisao e o no raiz atribuindo seu valor
  BinaryTree<T> *decisionTree = new BinaryTree<T>();
  Node<T> *root = construirDecisionTree(0, "");
  decisionTree->setRoot(root);
  //Pergunta se a pessoa tem ou nao os sintomas, caso deseje realizar o diagnostico
  do 
  {
    cout << "Voce precisa de um diagnostico? (Sim/Nao) ";
    string resposta;
    cin >> resposta;
    if (resposta == "Sim" || resposta == "sim" || resposta == "S" || resposta == "s")
    {
      cout << "---------------------------------\n";
      diagnosticar(decisionTree->getRoot());
    }
    else
    {
      break;
    }

  } while (true);
}