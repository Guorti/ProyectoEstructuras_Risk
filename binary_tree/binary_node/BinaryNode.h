#ifndef BINARY_NODE_H
#define BINARY_NODE_H

#include <ostream>
#include <memory>

using namespace std;

template <typename T>
class BinaryNode{

protected:
    T data;
    BinaryNode<T> *leftChild;
    BinaryNode<T> *rightChild;

public:

    struct BinaryNodeComparator {
        bool operator()(const BinaryNode<T>* lhs, const BinaryNode<T>* rhs) const {
            return *lhs > *rhs; // Use the > operator you've defined for BinaryNode.
        }
    };

    /* Constructor and Destructor */
    explicit BinaryNode(T data);
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