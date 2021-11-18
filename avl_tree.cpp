#include "avl_tree.h"

template <typename T>
void AvlTree<T>::insert(T data)
{
    BST<T>::insert(data);

    Node<T>* current = BST<T>::root;
    Node<T>* localParent = current->parent;
    Node<T>* localLeft = current->left;
    Node<T>* localRight = current->right;

    //Get parent of newly inserted node
    while (true)
    {
        localParent = current->parent;
        localLeft = current->left;
        localRight = current->right;

        if(data == current->data && localRight == 0)
            current = localParent;

        if(data < localLeft->data)
        {
            current = localLeft;
        }
        else if (data >= localRight->data)
        {
            current = localRight;
        }
    }

    //Walk Tree
    

    return;
}