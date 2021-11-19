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

        cout << " C: " << current->data;
        if(localParent != 0)
            cout << " P: " << localParent->data;
        if(localLeft != 0)
            cout << " L: " << localLeft->data;
        if(localRight != 0)
            cout << " R: " << localRight->data;
        cout << endl;

        if(data == current->data && localRight == 0)
        {
            current = localParent;
            break;
        }

        if(localLeft != 0 && data < current->data)
        {
            current = localLeft;
        }
        else if (localRight != 0 && data > current->data)
        {
            current = localRight;
        }
    }

    //Walk Tree
    while(current != 0)
    {
        cout << "Checking Balance!" << endl;
        cout << "Current: " << current->data << endl;
        if(unbalanced(current))
        {
            cout << "They are unworthy" << endl;

            cout << "X: " << current->data << endl;
            Node<T>* directChild = trinode_successor(current, -1);
            cout << "Y: " << directChild->data << endl;

            Node<T>* childsChild = trinode_successor(directChild, -1);
            cout << "Z: " << childsChild->data << endl;

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
    {
        leftHeight = current->left->height;
        leftHeight++;
    }

    if(current->right != 0)
    {
        rightHeight = current->right->height;
        leftHeight++;
    }

    if(leftHeight > rightHeight)
    {
        return current->left;
    }
    
    return current->right;
}

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
            cout << "LEFT - LEFT" << endl;
            if(y->right != 0)
                babysitter = y->right;

            if(x->parent != 0)
                y->parent = x->parent;
            else
                y->parent = 0;
            
            y->right = x;
            x->parent = y;
            x->left = babysitter;
            babysitter->parent = x;

            //X
            if(x->parent != 0)  cout << "Xp: " << x->parent << endl;
            else cout << "Xp: " << "No Parent" << endl;
            if(x->left != 0)  cout << "Xl: " << x->left << endl;
            else cout << "Xl: " << "No left" << endl;
            if(x->right != 0)  cout << "Xr: " << x->right << endl;
            else cout << "Xr: " << "No right" << endl;

            //Y
            if(y->parent != 0)  cout << "Yp: " << x->parent << endl;
            else cout << "Yp: " << "No Parent" << endl;
            if(y->left != 0)  cout << "Yl: " << x->left << endl;
            else cout << "Yl: " << "No left" << endl;
            if(y->right != 0)  cout << "Yr: " << x->right << endl;
            else cout << "Yr: " << "No right" << endl;

            //Z
            if(z->parent != 0)  cout << "Zp: " << x->parent << endl;
            else cout << "Zp: " << "No Parent" << endl;
            if(z->left != 0)  cout << "Zl: " << x->left << endl;
            else cout << "Zl: " << "No left" << endl;
            if(z->right != 0)  cout << "Zr: " << x->right << endl;
            else cout << "Zr: " << "No right" << endl;
        }
        else //Right
        {
            cout << "LEFT - RIGHT" << endl;
        }
    }
    else //Right
    {
        cout << "RIGHT - LEFT" << endl;
        if(z->data < y->data) //Left
        {
            
        }
        else //Right
        {
            cout << "RIGHT - RIGHT" << endl;
            
        }
    }



    return new Node<T>(-1);
}

template <typename T>
bool AvlTree<T>::unbalanced(Node<T>* current)
{
    int left = 0;
    int right = 0;
    if(current->left != 0)
    {
        left = current->left->height;
        left++;
    }
    if(current->right != 0)
    {
        right = current->right->height;
        right++;
    }

    cout << "Left Height: " << left << endl;
    cout << "Right Height: " << right << endl;

    int difference = abs(left - right);
    cout << "Diff: " << difference << endl;
    if(difference > 1)
        return true;
    return false;
}