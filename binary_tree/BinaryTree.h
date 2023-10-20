#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <list>
#include <deque>
#include <queue>
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

    string binaryToCharAux(std::queue<char> &ordenBinarios, BinaryNode<T> *&node);

public:
    /* Constructor and Destructor */
    explicit BinaryTree(T const &data);
    explicit BinaryTree(BinaryNode<T> *&node);
    BinaryTree();
    ~BinaryTree();

    /* Getters and Setters */
    T getRoot() const;
    BinaryNode<T>* getRootNode() const;


    void setRoot(BinaryNode<T> *node);

    std::ostringstream binaryToChar(std::queue<char> &ordenBinarios);

    bool isEmpty() const;

    void mapHuffman(unordered_map<char, string> &mapHuff);

    bool addNode(T const &data);

    list<T> preOrder() const;
    list<T> inOrder() const;
    list<T> postOrder() const;
};

#include "BinaryTree.hxx"
#endif //BINARY_TREE_HPP
