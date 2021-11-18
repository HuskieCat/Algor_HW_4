#include "avl_tree.h"

template <typename T>
void AvlTree<T>::insert(T data)
{
    BST<T>::insert(data);

    Node<T>* current = root;
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
    Node<T>* babysitter = 0;
    if(directChild->data < unbalancedNode->data) //Left
    {
        if(childsChild->data < directChild->data) //Left
        {
            if(directChild->right != 0)
                babysitter = directChild->right;

            //Y
            directChild->parent = unbalancedNode->parent;
            directChild->right = unbalancedNode;

            //X
            unbalancedNode->parent = directChild;
            unbalancedNode->left = babysitter;

            //Heights
            Node<T>* balanceHeights = unbalancedNode;
            int counter = 0;
            while(counter < 2)
            {
                if(balanceHeights->left != 0)
                {
                    if(balanceHeights->right != 0)
                    {
                        if(balanceHeights->left->height > balanceHeights->right->height)
                            balanceHeights->height = balanceHeights->left->height + 1;
                        else
                            balanceHeights->height = balanceHeights->right->height + 1;
                    }
                    else
                        balanceHeights->height = balanceHeights->left->height + 1;
                }
                else if (balanceHeights->right != 0)
                    balanceHeights->height = balanceHeights->right->height + 1;
                else
                    balanceHeights->height = 0;

                counter++;
                if(counter == 1)
                    balanceHeights = directChild;
            }

            return directChild;
        }
        else //Right
        {
            if(childsChild->right != 0)
                babysitter = childsChild->right;

            //Z & Y
            if(childsChild->left != 0)
            {
                directChild->right = childsChild->left;
                childsChild->left->parent = directChild;
            }
            else
                directChild->right = 0;

            //Z
            childsChild->parent = unbalancedNode->parent;
            childsChild->left = directChild;
            childsChild->right = unbalancedNode;

            //X
            unbalancedNode->parent = childsChild;
            unbalancedNode->left = babysitter;

            //Heights
            Node<T>* balanceHeights = unbalancedNode;
            int counter = 0;
            while(counter < 3)
            {
                if(balanceHeights->left != 0)
                {
                    if(balanceHeights->right != 0)
                    {
                        if(balanceHeights->left->height > balanceHeights->right->height)
                            balanceHeights->height = balanceHeights->left->height + 1;
                        else
                            balanceHeights->height = balanceHeights->right->height + 1;
                    }
                    else
                        balanceHeights->height = balanceHeights->left->height + 1;
                }
                else if (balanceHeights->right != 0)
                    balanceHeights->height = balanceHeights->right->height + 1;
                else
                    balanceHeights->height = 0;

                counter++;
                if(counter == 1)
                    balanceHeights = directChild;
                else if (counter == 2)
                    balanceHeights = childsChild;
            }
            
            return childsChild;
        }
    }
    else //Right
    {
        if(childsChild->data < directChild->data) //Left
        {
            if(childsChild->left != 0)
                babysitter = childsChild->left;

            //Z & Y
            if(childsChild->right != 0)
            {
                directChild->left = childsChild->right;
                childsChild->right->parent = directChild;
            }
            else
                directChild->left = 0;

            //Z
            childsChild->parent = unbalancedNode->parent;
            childsChild->left = unbalancedNode;
            childsChild->right = directChild;

            //X
            unbalancedNode->parent = childsChild;
            unbalancedNode->right = babysitter;

            //Heights
            Node<T>* balanceHeights = unbalancedNode;
            int counter = 0;
            while(counter < 3)
            {
                if(balanceHeights->left != 0)
                {
                    if(balanceHeights->right != 0)
                    {
                        if(balanceHeights->left->height > balanceHeights->right->height)
                            balanceHeights->height = balanceHeights->left->height + 1;
                        else
                            balanceHeights->height = balanceHeights->right->height + 1;
                    }
                    else
                        balanceHeights->height = balanceHeights->left->height + 1;
                }
                else if (balanceHeights->right != 0)
                    balanceHeights->height = balanceHeights->right->height + 1;
                else
                    balanceHeights->height = 0;

                counter++;
                if(counter == 1)
                    balanceHeights = directChild;
                else if (counter == 2)
                    balanceHeights = childsChild;
            }

            return childsChild;
        }
        else //Right
        {
            if(directChild->left != 0)
                babysitter = directChild->left;

            //Y
            directChild->parent = unbalancedNode->parent;
            directChild->left = unbalancedNode;

            //X
            unbalancedNode->parent = directChild;
            unbalancedNode->right = babysitter;

            Node<T>* balanceHeights = unbalancedNode;
            int counter = 0;
            while(counter < 2)
            {
                if(balanceHeights->left != 0)
                {
                    if(balanceHeights->right != 0)
                    {
                        if(balanceHeights->left->height > balanceHeights->right->height)
                            balanceHeights->height = balanceHeights->left->height + 1;
                        else
                            balanceHeights->height = balanceHeights->right->height + 1;
                    }
                    else
                        balanceHeights->height = balanceHeights->left->height + 1;
                }
                else if (balanceHeights->right != 0)
                    balanceHeights->height = balanceHeights->right->height + 1;
                else
                    balanceHeights->height = 0;

                counter++;
                if(counter == 1)
                    balanceHeights = directChild;
            }

            return directChild;
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