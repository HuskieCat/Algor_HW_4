#include <iostream>
#include "bst.h"

using namespace std;

template <typename T>
ostream& operator<<(ostream& out, const BST<T>& currentNode)
{
    print(out, currentNode);
    return out << endl;
}

template <typename T>
void print(ostream& out, Node<T>* currentNode)
{
    Node<T>* localLeft = currentNode->left;
    Node<T>* localRight = currentNode->right;

    if(localLeft != 0)
        print(out, localLeft);

    out << currentNode->data;

    if(localRight != 0)
        print(out, localRight);

    return out;
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

            //Left < Value
            if (data < current->data)
            {
                if (localLeft == 0)
                {
                    localLeft = new Node<T>(data);
                    localLeft->parent = current;
                    break;
                }
                else
                {
                    current = localLeft;
                    continue;
                }
            }
            else if (data >= current->data)
            {
                if (localRight == 0)
                {
                    localRight = new Node<T>(data);
                    localRight->parent = current;
                    break;
                }
                else
                {
                    current = localRight;
                    continue;
                }
            }
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
    Node<T>* localLeft = nodePTR->left;
    Node<T>* localRight = nodePTR->right;

    if(localLeft != 0)
        remove(localLeft);
    if (localRight != 0)
        remove(localRight);
    delete[] nodePTR;

    return;
}