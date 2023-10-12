#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <list>
#include <deque>
#include <unordered_map>

#include "binary_node/BinaryNode.h"

using namespace std;

template <typename T>
class BinaryTree
{
protected:
    BinaryNode<T> *root;

private:
    bool addNodeAux(T const &data, BinaryNode<T> *&node);
    void preOrderAux(BinaryNode<T> *node, list<T> &list) const;
    void inOrderAux(BinaryNode<T> *node, list<T> &list) const;
    void postOrderAux(BinaryNode<T> *node, list<T> &list) const;
    void mapHuffmanAux(BinaryNode<T> *node, unordered_map<char, string> &mapHuff, deque<char> &dequeLeaf);
    string huffRoute(deque<char> dequeLeaf);

public:
    /* Constructor and Destructor */
    explicit BinaryTree(T const &data);
    explicit BinaryTree(BinaryNode<T> *&node);
    BinaryTree();
    ~BinaryTree();

    /* Getters and Setters */
    T getRoot() const;
    BinaryNode<T>* getRootNode() const;

    // No tiene sentido implementar un setter para el nodo raíz, ya que
    // no se deberia poder cambiar el nodo raíz de un árbol binario.
    // void setRoot(BinaryNode<T> *root);

    void huffCodification(std::ostringstream &ss);



    bool isEmpty() const;

    bool addNode(T const &data);

    void mapHuffman(unordered_map<char, string> &mapHuff);

    list<T> preOrder() const;
    list<T> inOrder() const;
    list<T> postOrder() const;
};

#include "BinaryTree.hxx"
#endif //BINARY_TREE_HPP
