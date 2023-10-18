#ifndef BINARY_TREE_HXX
#define BINARY_TREE_HXX

#include <deque>
#include <queue>
#include <sstream>
#include "BinaryTree.h"
#include "binary_node/BinaryNode.h"
#include "../huffman_data/HuffmanData.h"


template <typename T>
std::ostringstream BinaryTree<T>::binaryToChar(std::queue<char> &ordenBinarios){
    std::ostringstream returnString;

    while(!ordenBinarios.empty()){
        returnString << binaryToCharAux(ordenBinarios, root);
    }
    return returnString;
}
template <typename T>
string BinaryTree<T>::binaryToCharAux(std::queue<char> &ordenBinarios, BinaryNode<T> *&node){
    std::stringstream stringAux;

    if(node == nullptr){
        return "";
    }

    if(node->isLeaf()){
        stringAux << HuffmanData(node->data).getSymbol();
        //ss << stringAux.str();
        //ss << stringAux.str();
        std::cout << stringAux.str();
        return stringAux.str();
    }

    if(ordenBinarios.front()== '1'){
        ordenBinarios.pop();
        return binaryToCharAux(ordenBinarios, node->rightChild);
    }

    if(ordenBinarios.front()== '0'){
        ordenBinarios.pop();
        return binaryToCharAux(ordenBinarios, node->leftChild);
    }

    return "";
}

template <typename T>
bool BinaryTree<T>::addNodeAux(T const &data, BinaryNode<T> *&node)
{
    if (node == nullptr)
    {
        node = new BinaryNode<T>(data);
        return true;
    }
    else if (data < node->data)
    {
        return addNodeAux(data, node->leftChild);
    }
    else if (data > node->data)
    {
        return addNodeAux(data, node->rightChild);
    }

    // Se supone que un arbol binario no puede tener dos nodos con el mismo valor
    // por lo que si se llega a este punto, se retorna false.
    // Depende de la implementacion necesaria y el problema.
    return false;
}

template <typename T>
void BinaryTree<T>::preOrderAux(BinaryNode<T> *node, list<T> &list) const
{
    if (node == nullptr)
    {
        return;
    }

    list.push_back(node->data);
    preOrderAux(node->leftChild, list);
    preOrderAux(node->rightChild, list);
}

template <typename T>
void BinaryTree<T>::inOrderAux(BinaryNode<T> *node, list<T> &list) const
{
    if (node == nullptr)
    {
        return;
    }

    inOrderAux(node->leftChild, list);
    list.push_back(node->data);
    inOrderAux(node->rightChild, list);
}

template <typename T>
void BinaryTree<T>::postOrderAux(BinaryNode<T> *node, list<T> &list) const
{
    if (node == nullptr)
    {
        return;
    }

    postOrderAux(node->leftChild, list);
    postOrderAux(node->rightChild, list);
    list.push_back(node->data);
}



//Constructor con dato
template <typename T>
BinaryTree<T>::BinaryTree(T const &data)
{
    root = new BinaryNode<T>(data);
}
//Constructor con nodo
template <typename T>
BinaryTree<T>::BinaryTree(BinaryNode<T> *&node)
{
    root = node;
}
//Constructor defecto
template <typename T>
BinaryTree<T>::BinaryTree()
{
    root = nullptr;
}
//Destructor
template <typename T>
BinaryTree<T>::~BinaryTree()
{
    delete root;
    root = nullptr;
}

template <typename T>
T BinaryTree<T>::getRoot() const
{
    return root->data;
}

template <typename T>
BinaryNode<T>* BinaryTree<T>::getRootNode() const {
    return root;
}

template <typename T>
bool BinaryTree<T>::isEmpty() const
{
    return root == nullptr;
}

template <typename T>
void BinaryTree<T>::setRoot(BinaryNode<T> *node){
    root = node;
}


template <typename T>
bool BinaryTree<T>::addNode(T const &data)
{
    if (isEmpty())
    {
        root = new BinaryNode<T>(data);
        return true;
    }

    return addNodeAux(data, root);
}

template <typename T>
list<T> BinaryTree<T>::preOrder() const
{
    // Creamos una lista vacia para almacenar los datos del arbol
    // en preorden.
    list<T> list;

    // Llamamos a la funcion auxiliar para recorrer el arbol en preorden.
    // Recibe por referencia la lista vacia para ir agregando los datos
    // del arbol.
    preOrderAux(root, list);

    return list;
}

template <typename T>
void BinaryTree<T>::mapHuffman(unordered_map<char, string> &mapHuff)
{

    // Creamos una pila vacia para almacenar el recorrido hasta cada hoja del arbol
    deque<char> dequeLeaf;

    mapHuffmanAux(root, mapHuff, dequeLeaf);
    return;
}

template <typename T>
void BinaryTree<T>::mapHuffmanAux(BinaryNode<T> *node, unordered_map<char, string> &mapHuff, deque<char> &dequeLeaf)
{
    if(node == nullptr){
        return;
    }
    if (node->isLeaf())
    {
        //MODIFICAR EL VALOR DE LA LLAVE X EL RECORRIDO ACTUAL Y REMOVER ULTIMO DIGITO O EL TOP DEL DEQUE

        mapHuff[node->data.getSymbol()]= huffRoute(dequeLeaf);


        //Dado que encontramos la hoja, removemos el ultimo digito, debido a que cambiaremos de ruta.
        dequeLeaf.pop_front();
        return;
    }

    dequeLeaf.push_front('0');
    mapHuffmanAux(node->leftChild, mapHuff,dequeLeaf);
    dequeLeaf.push_front('1');
    mapHuffmanAux(node->rightChild,mapHuff,dequeLeaf);
    //Si ya acabamos el recorrido por hijo izquiero y derecho, cambiaremos de nodo, por lo que removemos el ultimo digito del recorrido actual.
    dequeLeaf.pop_front();
}

template <typename T>
string BinaryTree<T>::huffRoute(deque<char> dequeLeaf)
{
    string routeHuffString;
    deque<char> dequeAux;

    while(!dequeLeaf.empty()){
        dequeAux.push_front(dequeLeaf.front());
        dequeLeaf.pop_front();
    }
    while(!dequeAux.empty()){
        routeHuffString.push_back(dequeAux.front());
        dequeAux.pop_front();
    }

    return routeHuffString;
}

template <typename T>
list<T> BinaryTree<T>::inOrder() const
{
    list<T> list;

    inOrderAux(root, list);

    return list;
}

template <typename T>
list<T> BinaryTree<T>::postOrder() const
{
    list<T> list;

    postOrderAux(root, list);

    return list;
}

#endif
