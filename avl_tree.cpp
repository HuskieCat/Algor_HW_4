#include <cstdlib>
#include <cmath>
#include "avl_tree.h"

/*
CPP of avl_tree for making AVL trees

Known Issues: Chance of working with lists of numbers but can also fail: Reason (Unknown)

Author: Bradley Henderson
*/

/*
Inserts the node into the AVL and balances
*/
template <typename T>
void AvlTree<T>::insert(T data)
{
    BST<T>::insert(data);

    //Temporary variables to help locate the node
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
        {
            current = localParent;
            break;
        }

        if(localLeft != 0 && data < current->data)
        {
            current = localLeft;
        }
        else if (localRight != 0 && data >= current->data)
        {
            current = localRight;
        }
    }

    //Walk Tree and rebalance
    Node<T>* output = 0;
    while(current != 0)
    {
        if(unbalanced(current))
        {
            Node<T>* directChild = trinode_successor(current, -1);
            Node<T>* childsChild = trinode_successor(directChild, -1);
            current = trinode_restructure(current, directChild, childsChild);

            this->root = current;
            if(current->parent != 0 && current->parent->height <= current->height)
            {
                current->parent->height = current->height + 1;
            }
        }

        current = current->parent;
        
        //Fix heights
        if(current != 0)
        {
            this->root = current;

            if(current->left != 0 && current->right != 0)
            {
                if(current->left->height > current->right->height)
                {
                    current->height = current->left->height + 1;
                }
                else if (current->left->height < current->right->height)
                {
                    current->height = current->right->height + 1;
                }
                else
                    current->height = current->left->height + 1;
            }
            else if (current->left != 0)
            {
                current->height = current->left->height + 1;
            }
            else if (current->right != 0)
            {
                current->height = current->right->height + 1;
            }
            else
            {
                current->height = 0;
            }
        }
    }

    return;
}

/*
Gets the biggest child height of children if they exist
*/
template <typename T>
Node<T>* AvlTree<T>::trinode_successor(Node<T>* current, T data)
{
    int leftHeight = 0;
    int rightHeight = 0;

    if(current->left != 0)
    {
        leftHeight = current->left->height;
        leftHeight++;
    }

    if(current->right != 0)
    {
        rightHeight = current->right->height;
        rightHeight++;
    }

    if(leftHeight > rightHeight)
    {
        return current->left;
    }
    
    return current->right;
}


/*
Rotates the noted so they comply with the AVL standard
*/
template <typename T>
Node<T>* AvlTree<T>::trinode_restructure(Node<T>* x, 
                                         Node<T>* y, 
                                         Node<T>* z)
{
    Node<T>* babysitter = 0;
    if(y->data < x->data) //Left
    {
        if(z->data < y->data) //Left
        {
            if(y->right != 0) //Get Y's child
                babysitter = y->right;

            //Set Parents
            if(x->parent != 0)
            {
                if(x->parent->left == x)
                {
                    x->parent->left = y; // Set x parent to Y
                    y->parent = x->parent; // Set y parent to x's parent
                }
                else if (x->parent->right == x)
                {
                    x->parent->right = y; // Set x parent to Y
                    y->parent = x->parent; // Set y parent to x's parent
                }
            }
            else
                y->parent = 0;
            
            x->parent = y; // x parent is now y.
            y->right = x;

            if(babysitter != 0) //Get that other piece thats missing
            {
                x->left = babysitter;
                babysitter->parent = x;
            }
            else
                x->left = 0;

            //Height fixing
            int left = 0;
            int right = 0;
            int count = 0;
            babysitter = x;
            while(count < 3)
            {
                if(babysitter->left != 0)
                {
                    left = babysitter->left->height;
                    if(babysitter->right != 0)
                    {
                        right = babysitter->right->height;
                        if(left > right)
                            babysitter->height = left + 1;
                        else
                            babysitter->height = right + 1;
                    }
                    babysitter->height = left + 1;
                }
                else if (babysitter->right != 0)
                {
                    right = babysitter->right->height;
                    babysitter->height = right + 1;
                }
                else
                    babysitter->height = 0;
                
                count++;
                if(count == 1)
                    babysitter = z;
                if(count == 2)
                    babysitter = y;
            }

            return y;
        }
        else //Right
        {
            if(z->right != 0) // get child for moving
                babysitter = z->right;

            if(x->parent != 0)
            {
                if(x->parent->left == x)
                {
                    x->parent->left = z;
                    z->parent = x->parent;
                }
                else if (x->parent->right == x)
                {
                    x->parent->right = z;
                    z->parent = x->parent;
                }
            }
            else
                z->parent = 0;

            if(z->left != 0)
            {
                y->right = z->left;
                y->right->parent = y;
            }
            else
                y->right = 0;

            x->parent = z;
            z->right = x;

            y->parent = z;
            z->left = y;

            if(babysitter != 0)
            {
                x->left = babysitter;
                babysitter->parent = x;
            }
            else
                x->left = 0;

            //Height
            int left = 0;
            int right = 0;
            int count = 0;
            babysitter = x;
            while(count < 3)
            {
                if(babysitter->left != 0)
                {
                    left = babysitter->left->height;
                    if(babysitter->right != 0)
                    {
                        right = babysitter->right->height;
                        if(left > right)
                            babysitter->height = left + 1;
                        else
                            babysitter->height = right + 1;
                    }
                    babysitter->height = left + 1;
                }
                else if (babysitter->right != 0)
                {
                    right = babysitter->right->height;
                    babysitter->height = right + 1;
                }
                else
                    babysitter->height = 0;
                
                count++;
                if(count == 1)
                    babysitter = y;
                if(count == 2)
                    babysitter = z;
            }

            return z;
        }
    }
    else //Right
    {
        if(z->data < y->data) //Left
        {
            if(z->left != 0) // get child for moving
                babysitter = z->left;

            if(x->parent != 0)
            {
                if(x->parent->left == x)
                {
                    x->parent->left = z;
                    z->parent = x->parent;
                }
                else if(x->parent->right == x)
                {
                    x->parent->right = z;
                    z->parent = x->parent;
                }
            }
            else
            z->parent = 0;

            if(z->right != 0)
            {
                y->left = z->right;
                y->left->parent = y;
            }
            else
                y->left = 0;

            x->parent = z;
            z->left = x;

            y->parent = z;
            z->right = y;

            if(babysitter != 0)
            {
                x->right = babysitter;
                x->right->parent = x;
            }
            else
                x->right = 0;
            
            //Height
            int left = 0;
            int right = 0;
            int count = 0;
            babysitter = y;
            while(count < 3)
            {
                if(babysitter->left != 0)
                {
                    left = babysitter->left->height;
                    if(babysitter->right != 0)
                    {
                        right = babysitter->right->height;
                        if(left > right)
                            babysitter->height = left + 1;
                        else
                            babysitter->height = right + 1;
                    }
                    babysitter->height = left + 1;
                }
                else if (babysitter->right != 0)
                {
                    right = babysitter->right->height;
                    babysitter->height = right + 1;
                }
                else
                    babysitter->height = 0;
                
                count++;
                if(count == 1)
                    babysitter = x;
                if(count == 2)
                    babysitter = z;
            }

            return z;
        }
        else //Right
        {
            //Y child into storage
            if(y->left != 0) //Get Y's child
                babysitter = y->left;

            //Set Parents
            if(x->parent != 0)
            {
                if(x->parent->left == x)
                {
                    x->parent->left = y; // Set x parent to Y
                    y->parent = x->parent; // Set y parent to x's parent
                }
                else if (x->parent->right == x)
                {
                    x->parent->right = y; // Set x parent to Y
                    y->parent = x->parent; // Set y parent to x's parent
                }
            }
            else
                y->parent = 0;
            
            x->parent = y; // x parent is now y.
            y->left = x;

            if(babysitter != 0) //Get that other piece thats missing
            {
                x->right = babysitter;
                x->right->parent = x;
            }
            else
                x->right = 0;

            //Height
            int left = 0;
            int right = 0;
            int count = 0;
            babysitter = z;
            while(count < 3)
            {
                if(babysitter->left != 0)
                {
                    left = babysitter->left->height;
                    if(babysitter->right != 0)
                    {
                        right = babysitter->right->height;
                        if(left > right)
                            babysitter->height = left + 1;
                        else
                            babysitter->height = right + 1;
                    }
                    babysitter->height = left + 1;
                }
                else if (babysitter->right != 0)
                {
                    right = babysitter->right->height;
                    babysitter->height = right + 1;
                }
                else
                    babysitter->height = 0;
                
                count++;
                if(count == 1)
                    babysitter = x;
                if(count == 2)
                    babysitter = y;
            }

            return y;
        }
    }

    return new Node<T>(-1);
}


/*
Checks the left and right children of a node to see if they are balanced or not.
If not it returns true for not balanced
*/
template <typename T>
bool AvlTree<T>::unbalanced(Node<T>* current)
{
    int left = -1;
    int right = -1;
    int difference = 0;

    if(current->left != 0 && current->right != 0)
    {
        left = current->left->height;
        right = current->right->height;

        if(left > right)
            difference = left - right;
        else if(right > left)
            difference = right - left;
        else
            return false;
    }
    else if(current->left != 0)
    {
        left = current->left->height;
        difference = abs(left - right);
    }
    else if(current->right != 0)
    {
        right = current->right->height;
        difference = abs(right - left);
    }
    else
        return false;

    difference = abs(difference); //just for extra make sureing ness it possitive

    if(difference > 1)
        return true;
    return false;
}