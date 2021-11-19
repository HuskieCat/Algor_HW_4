#include <cstdlib>
#include <cmath>
#include "avl_tree.h"

template <typename T>
void AvlTree<T>::insert(T data)
{
    cout << endl;

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

        cout << "C: " << current->data;
        if(localParent != 0)
            cout << " P: " << localParent->data;
        if(localLeft != 0)
            cout << " L: " << localLeft->data;
        if(localRight != 0)
            cout << " R: " << localRight->data;
        cout << " H: " << current->height;
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
    Node<T>* output = 0;
    while(current != 0)
    {
        if(unbalanced(current))
        {
            cout << "They are unworthy" << endl;

            cout << "X: " << current->data << endl;
            Node<T>* directChild = trinode_successor(current, -1);
            cout << "Y: " << directChild->data << endl;

            Node<T>* childsChild = trinode_successor(directChild, -1);
            cout << "Z: " << childsChild->data << endl;

            current = trinode_restructure(current, directChild, childsChild);
            this->root = current;

            cout << "Current after restructure: " << current->data << endl;
            if(current->left != 0)
                cout << "l1:" << current->left->data << endl;
            if(current->right != 0)
                cout << "l2:" << current->right->data << endl;
            cout << "Curr height: " << current->height << endl;
            if(current->parent != 0 && current->parent->height <= current->height)
            {
                current->parent->height = current->height + 1;
            }
            if(current->parent != 0)
            {
                cout << "Curr height parent: " << current->parent->height << endl;
            }
        }

        current = current->parent;
        
        if(current != 0)
        {
            this->root = current;
            cout << "Root: " << current->data << endl;
            cout << "Height: " ;
            if(current->left != 0)
            {
                cout << "Left: " << current->left->data << " ";
                cout << current->left->height;
            }
            else cout << "Left 0 :";
            if(current->right != 0)
            {
                cout << " : " << "Right: " << current->right->data << " " << current->right->height << endl;

            }
            else cout << " 0 " << endl;
            cout << "Root height: " << current->height << endl;

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

    cout << endl;
    cout << endl;
    cout << endl;

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
            if(y->right != 0)
                babysitter = y->right;

            if(x->parent != 0)
            {
                if(x->parent->left == x)
                {
                    y->parent = x->parent;
                    y->parent->left = y;
                }
                else
                {
                    y->parent = x->parent;
                    y->parent->right = y;
                }
            }
            else
            {
                y->parent = 0;
            }
            
            x->parent = y;
            y->right = x;

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
            return y;
        }
        else //Right
        {
            cout << "LEFT - RIGHT" << endl;
            if(z->right != 0)
                babysitter = z->right;

            if(x->parent != 0)
            {
                if(x->parent->left == x)
                {
                    z->parent = x->parent;
                    z->parent->left = z;
                }
                else
                {
                    z->parent = x->parent;
                    z->parent->right = z;
                }
            }
            else
                z->parent = 0;

            x->parent = z;
            z->right = x;

            if(z->left != 0)
                y->right = z->left;
            else
                y->right = 0;

            z->left = y;
            y->parent = z;

            if(babysitter != 0)
                x->left = babysitter;
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

            return z;
        }
    }
    else //Right
    {
        if(z->data < y->data) //Left
        {
            cout << "RIGHT - LEFT" << endl;
            if(z->left != 0)
                babysitter = z->left;

            if(x->parent != 0)
            {
                if(x->parent->left == x)
                {
                    z->parent = x->parent;
                    z->parent->left = z;
                }
                else
                {
                    z->parent = x->parent;
                    z->parent->right = z;
                }
            }
            else
                z->parent = 0;

            x->parent = z;
            z->left = x;

            if(z->right != 0)
                y->left = z->right;
            else
                y->left = 0;

            z->right = y;
            y->parent = z;

            if(babysitter != 0)
                x->right = babysitter;
            else
                x->right = 0;
            
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
            if(y->parent !=0)
            {
                cout << "R: " << y->parent->data << endl;
                if(y->parent->left != 0) cout << "Rl: " << y->parent->left->data << endl;
                else cout << "Rl: No Left" << endl;
                if(y->parent->right != 0) cout << "Rr: " << y->parent->right->data << endl;
                else cout << "Rr: No Right" << endl;

            }

            return z;
        }
        else //Right
        {
            cout << "RIGHT - RIGHT" << endl;
            //Y child into storage
            if(y->left != 0) 
                babysitter = y->left;

            //Parent of X is now Y's Parent
            if(x->parent != 0)
            {
                if(x->parent->left == x)
                {
                    y->parent = x->parent; //Get parent
                    y->parent->left = y; //Replace left child
                }
                else
                {
                    y->parent = x->parent; //Get parent
                    y->parent->right = y; //Replace left child
                }
            }
            else
                y->parent = 0;

            //Set x Parent to Y
            x->parent = y;
            y->left = x;

            if(babysitter != 0)
                x->right = babysitter; //Give X y's child
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
            if(y->parent !=0)
            {
                cout << "R: " << y->parent->data << endl;
                if(y->parent->left != 0) cout << "Rl: " << y->parent->left->data << endl;
                else cout << "Rl: No Left" << endl;
                if(y->parent->right != 0) cout << "Rr: " << y->parent->right->data << endl;
                else cout << "Rr: No Right" << endl;

            }

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

        cout << "Checking: " << current->left->data << ":" << current->right->data << endl;

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

    difference = abs(difference);
    cout << "Height Check : " << current->data << " L:" << left << " R:"<<right<<endl;
    cout << "Diff:" << difference << endl;

    if(difference > 1)
        return true;
    return false;
}