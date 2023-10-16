#ifndef BINARY_NODE_H
#define BINARY_NODE_H

#include <ostream>
#include <memory>
#include "../../huffman_data/HuffmanData.h"

using namespace std;

template <typename T>
class BinaryNode{

protected:
    T data;
    BinaryNode<T> *leftChild;
    BinaryNode<T> *rightChild;

public:

    int getFrecuencia() const;
    void setFrecuencia(int frecuencia);


    struct BinaryNodeComparator {
        bool operator()( BinaryNode<T>* lhs,  BinaryNode<T>* rhs) const {
            return lhs->data > rhs->data;
        }
    };

    /* Constructor and Destructor */
    explicit BinaryNode(T data);
    explicit BinaryNode(T data, int frecuencia);
    BinaryNode(T data, BinaryNode<T> *left, BinaryNode<T> *right);
    BinaryNode(T data, BinaryNode<T> left, BinaryNode<T> right);
    //~BinaryNode();

    /* Getters and Setters */
    T getData() const;
    void setData(T data);

    BinaryNode<T> *getLeft() const;
    void setLeft(BinaryNode<T> *left);
    void setLeft(BinaryNode<T> left);

    BinaryNode<T> *getRight() const;
    void setRight(BinaryNode<T> *right);
    void setRight(BinaryNode<T> right);

    /* Operators */
    bool operator==(const BinaryNode &otherBinaryNode) const;

    bool operator!=(const BinaryNode &otherBinaryNode) const;

    bool operator<(const BinaryNode &otherBinaryNode) const;

    bool operator>(const BinaryNode &otherBinaryNode) const;

    bool operator<(const BinaryNode<T>* otherBinaryNode) const;

    bool operator>(const BinaryNode<T>* otherBinaryNode) const;



    template <typename U>
    friend ostream &operator<<(ostream &os, const BinaryNode<U> &binaryNode);

    /* Methods */
    bool isLeaf() const;

    bool addLeftNode(BinaryNode<T> *left);
    bool addRightNode(BinaryNode<T> *Right);

    /* Friends */
    template <typename U>
    friend class BinaryTree;

};
#include "BinaryNode.hxx"
#endif //BINARY_NODE_HPP