#include "avl_tree.h"

template <typename T>
void AvlTree<T>::insert(T data)
{
    BST<T>::insert(data);

    Node<T>* current = this->root;
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
    while(localParent != 0)
    {
        if(unbalanced(current))
        {
            Node<T>* directChild = trinode_successor(current, -1);
            Node<T>* childsChild = trinode_successor(directChild, -1);
            current = trinode_restructure(current, directChild, childsChild);
        }

        current = current->parent;
    }

    return;
}

template <typename T>
Node<T>* AvlTree<T>::trinode_successor(Node<T>* current, T data)
{
    int leftHeight = 0;
    int rightHeight = 0;

    if(current->left != 0)
        leftHeight = current->left->height;

    if(current->right != 0)
        rightHeight = current->right->height;

    if(leftHeight > rightHeight)
        return current->left;
    
    return current->right;
}

template <typename T>
Node<T>* AvlTree<T>::trinode_restructure(Node<T>* unbalancedNode, 
                                         Node<T>* directChild, 
                                         Node<T>* childsChild)
{
    if(directChild->data < unbalancedNode->data) //Left
    {
        if(childsChild->data < directChild->data) //Left
        {

        }
        else //Right
        {

        }
    }
    else //Right
    {
        if(childsChild->data < directChild->data) //Left
        {

        }
        else //Right
        {

        }
    }



    return new Node<T>(-1);
}

template <typename T>
bool AvlTree<T>::unbalanced(Node<T>* current)
{
    int difference = abs(current->left->height - current->right->height);
    if(difference > 1)
        return true;
    return false;
}