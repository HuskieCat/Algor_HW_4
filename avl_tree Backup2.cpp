#include <cstdlib>
#include <cmath>
#include "avl_tree.h"

template <typename T>
void AvlTree<T>::insert(T data)
{
    BST<T>::insert(data);

    cout << "INSERTED: " << data << "---------------" << endl;

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

        cout << "Current: " << current->data << " ";
        if(localParent != 0)
            cout << "Parent: " << localParent->data << " ";
        if(localLeft != 0)
            cout << "Left: " << localLeft->data << " ";
        if(localRight != 0)
            cout << "Right: " << localRight->data << " ";
        cout << " Height: " << current->height;
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
        else if (localRight != 0 && data >= current->data)
        {
            current = localRight;
        }
    }

    //Walk Tree
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
                else
                    cout << "There is no parent" << endl;
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
                    babysitter = z;
                if(count == 2)
                    babysitter = y;
            }

            //X
            cout << "X: " << x->data << endl;
            if(x->parent != 0)  cout << "Xp: " << x->parent->data << endl;
            else cout << "Xp: " << "No Parent" << endl;
            if(x->left != 0)  cout << "Xl: " << x->left->data << endl;
            else cout << "Xl: " << "No left" << endl;
            if(x->right != 0)  cout << "Xr: " << x->right->data << endl;
            else cout << "Xr: " << "No right" << endl;
            cout << "Xh: " << x->height << endl;

            //Y
            cout << "Y: " << y->data << endl;
            if(y->parent != 0)  cout << "Yp: " << y->parent->data << endl;
            else cout << "Yp: " << "No Parent" << endl;
            if(y->left != 0)  cout << "Yl: " << y->left->data << endl;
            else cout << "Yl: " << "No left" << endl;
            if(y->right != 0)  cout << "Yr: " << y->right->data << endl;
            else cout << "Yr: " << "No right" << endl;
            cout << "Yh: " << y->height << endl;

            //Z
            cout << "Z: " << z->data << endl;
            if(z->parent != 0)  cout << "Zp: " << z->parent->data << endl;
            else cout << "Zp: " << "No Parent" << endl;
            if(z->left != 0)  cout << "Zl: " << z->left->data << endl;
            else cout << "Zl: " << "No left" << endl;
            if(z->right != 0)  cout << "Zr: " << z->right->data << endl;
            else cout << "Zr: " << "No right" << endl;
            cout << "Zh: " << z->height << endl;

            //Root
            if(y->parent !=0)
            {
                cout << "R: " << y->parent->data << endl;
                if(y->parent->left != 0) cout << "Rl: " << y->parent->left->data << endl;
                else cout << "Rl: No Left" << endl;
                if(y->parent->right != 0) cout << "Rr: " << y->parent->right->data << endl;
                else cout << "Rr: No Right" << endl;
            }
            else
                cout << "This is root" << endl;

            return y;
        }
        else //Right
        {
            cout << "LEFT - RIGHT" << endl;
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
                else
                    cout << "There is no parent" << endl;
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

            //X
            cout << "X: " << x->data << endl;
            if(x->parent != 0)  cout << "Xp: " << x->parent->data << endl;
            else cout << "Xp: " << "No Parent" << endl;
            if(x->left != 0)  cout << "Xl: " << x->left->data << endl;
            else cout << "Xl: " << "No left" << endl;
            if(x->right != 0)  cout << "Xr: " << x->right->data << endl;
            else cout << "Xr: " << "No right" << endl;
            cout << "Xh: " << x->height << endl;

            //Y
            cout << "Y: " << y->data << endl;
            if(y->parent != 0)  cout << "Yp: " << y->parent->data << endl;
            else cout << "Yp: " << "No Parent" << endl;
            if(y->left != 0)  cout << "Yl: " << y->left->data << endl;
            else cout << "Yl: " << "No left" << endl;
            if(y->right != 0)  cout << "Yr: " << y->right->data << endl;
            else cout << "Yr: " << "No right" << endl;
            cout << "Yh: " << y->height << endl;

            //Z
            cout << "Z: " << z->data << endl;
            if(z->parent != 0)  cout << "Zp: " << z->parent->data << endl;
            else cout << "Zp: " << "No Parent" << endl;
            if(z->left != 0)  cout << "Zl: " << z->left->data << endl;
            else cout << "Zl: " << "No left" << endl;
            if(z->right != 0)  cout << "Zr: " << z->right->data << endl;
            else cout << "Zr: " << "No right" << endl;
            cout << "Zh: " << z->height << endl;

            //Root
            if(z->parent !=0)
            {
                cout << "R: " << z->parent->data << endl;
                if(z->parent->left != 0) cout << "Rl: " << z->parent->left->data << endl;
                else cout << "Rl: No Left" << endl;
                if(z->parent->right != 0) cout << "Rr: " << z->parent->right->data << endl;
                else cout << "Rr: No Right" << endl;
            }
            else
                cout << "This is root" << endl;

            return z;
        }
    }
    else //Right
    {
        if(z->data < y->data) //Left
        {
            cout << "RIGHT - LEFT" << endl;
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
                else
                    cout << "There is no parent" << endl;
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
                babysitter->parent = x;
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

            //X
            cout << "X: " << x->data << endl;
            if(x->parent != 0)  cout << "Xp: " << x->parent->data << endl;
            else cout << "Xp: " << "No Parent" << endl;
            if(x->left != 0)  cout << "Xl: " << x->left->data << endl;
            else cout << "Xl: " << "No left" << endl;
            if(x->right != 0)  cout << "Xr: " << x->right->data << endl;
            else cout << "Xr: " << "No right" << endl;
            cout << "Xh: " << x->height << endl;

            //Y
            cout << "Y: " << y->data << endl;
            if(y->parent != 0)  cout << "Yp: " << y->parent->data << endl;
            else cout << "Yp: " << "No Parent" << endl;
            if(y->left != 0)  cout << "Yl: " << y->left->data << endl;
            else cout << "Yl: " << "No left" << endl;
            if(y->right != 0)  cout << "Yr: " << y->right->data << endl;
            else cout << "Yr: " << "No right" << endl;
            cout << "Yh: " << y->height << endl;

            //Z
            cout << "Z: " << z->data << endl;
            if(z->parent != 0)  cout << "Zp: " << z->parent->data << endl;
            else cout << "Zp: " << "No Parent" << endl;
            if(z->left != 0)  cout << "Zl: " << z->left->data << endl;
            else cout << "Zl: " << "No left" << endl;
            if(z->right != 0)  cout << "Zr: " << z->right->data << endl;
            else cout << "Zr: " << "No right" << endl;
            cout << "Zh: " << z->height << endl;

            //Root
            if(z->parent !=0)
            {
                cout << "R: " << z->parent->data << endl;
                if(z->parent->left != 0) cout << "Rl: " << z->parent->left->data << endl;
                else cout << "Rl: No Left" << endl;
                if(z->parent->right != 0) cout << "Rr: " << z->parent->right->data << endl;
                else cout << "Rr: No Right" << endl;
            }
            else
                cout << "This is root" << endl;

            return z;
        }
        else //Right
        {
            cout << "RIGHT - RIGHT" << endl;
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
                else
                    cout << "There is no parent" << endl;
            }
            else
                y->parent = 0;
            
            x->parent = y; // x parent is now y.
            y->left = x;

            if(babysitter != 0) //Get that other piece thats missing
            {
                x->right = babysitter;
                babysitter->parent = x;
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

            //X
            cout << "X: " << x->data << endl;
            if(x->parent != 0)  cout << "Xp: " << x->parent->data << endl;
            else cout << "Xp: " << "No Parent" << endl;
            if(x->left != 0)  cout << "Xl: " << x->left->data << endl;
            else cout << "Xl: " << "No left" << endl;
            if(x->right != 0)  cout << "Xr: " << x->right->data << endl;
            else cout << "Xr: " << "No right" << endl;
            cout << "Xh: " << x->height << endl;

            //Y
            cout << "Y: " << y->data << endl;
            if(y->parent != 0)  cout << "Yp: " << y->parent->data << endl;
            else cout << "Yp: " << "No Parent" << endl;
            if(y->left != 0)  cout << "Yl: " << y->left->data << endl;
            else cout << "Yl: " << "No left" << endl;
            if(y->right != 0)  cout << "Yr: " << y->right->data << endl;
            else cout << "Yr: " << "No right" << endl;
            cout << "Yh: " << y->height << endl;

            //Z
            cout << "Z: " << z->data << endl;
            if(z->parent != 0)  cout << "Zp: " << z->parent->data << endl;
            else cout << "Zp: " << "No Parent" << endl;
            if(z->left != 0)  cout << "Zl: " << z->left->data << endl;
            else cout << "Zl: " << "No left" << endl;
            if(z->right != 0)  cout << "Zr: " << z->right->data << endl;
            else cout << "Zr: " << "No right" << endl;
            cout << "Zh: " << z->height << endl;

            //Root
            if(y->parent !=0)
            {
                cout << "R: " << y->parent->data << endl;
                if(y->parent->left != 0) cout << "Rl: " << y->parent->left->data << endl;
                else cout << "Rl: No Left" << endl;
                if(y->parent->right != 0) cout << "Rr: " << y->parent->right->data << endl;
                else cout << "Rr: No Right" << endl;
            }
            else
                cout << "This is root" << endl;

            return y;
        }
    }

    return new Node<T>(-1);
}

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

    difference = abs(difference);

    if(difference > 1)
        return true;
    return false;
}