/*
 * An AVL tree. Deletions are not supported.
 *
 * Author: Drue Coles
 */
 
#include "bst.cpp"

template <typename T>
class AvlTree : public BST<T> {

public:
    void insert(T data);
     
private:
    Node<T>* trinode_successor(Node<T>*, T);
    Node<T>* trinode_restructure(Node<T>*, Node<T>*, Node<T>*);
    bool unbalanced(Node<T>*);
};