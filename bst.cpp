#include <iostream>
#include "bst.h"

using namespace std;

template <typename T>
ostream& operator<<(ostream& out, const BST<T>& currentNode)
{
    print(out, currentNode.root);
    return out;
}

template <typename T>
void print(ostream& out, Node<T>* currentNode)
{
    if(currentNode->left != 0)
        print(out, currentNode->left);

    out << currentNode->data << " ";

    if(currentNode->right != 0)
        print(out, currentNode->right);

    return;
}

template <typename T>
void BST<T>::insert(T data)
{
    if (root != NULL)
    {
        Node<T>* current = root;
        Node<T>* localParent = current->parent;
        Node<T>* localLeft = current->left;
        Node<T>* localRight = current->right;

        while(true)
        {
            localParent = current->parent;
            localLeft = current->left;
            localRight = current->right;

            if (data < current->data) //Travel Left
            {
                if (localLeft == 0)
                {
                    localLeft = new Node<T>(data);
                    current->left = localLeft;
                    localLeft->parent = current;
                    current = localLeft;
                    break;
                }
                else
                {
                    current = localLeft;
                    continue;
                }
            }
            else if (data >= current->data) //Travel Right
            {
                if (localRight == 0)
                {
                    localRight = new Node<T>(data);
                    current->right = localRight;
                    localRight->parent = current;
                    current = localRight;
                    break;
                }
                else
                {
                    current = localRight;
                    continue;
                }
            }
        }

        while(current->parent != 0) //Add
        {
            int parentHeight = current->parent->height;
            int heightPlus = (current->height + 1);
            if(heightPlus > parentHeight)
            {
                current->parent->height = heightPlus;
            }
            else if (heightPlus == parentHeight)
                break;
            current = current->parent;
        }
    }
    else
    {
        root = new Node<T>(data);
    }

    return;
}

template <typename T>
int BST<T>::height(Node<T>* nodePTR)
{
    if(root != NULL)
        return nodePTR->height;
    return -1;
}

template <typename T>
void BST<T>::remove(Node<T>* nodePTR)
{
    if(nodePTR == 0)
        return;

    remove(nodePTR->left);
    remove(nodePTR->right);

    delete nodePTR;

    return;
}