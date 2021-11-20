#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "avl_tree.cpp"

using namespace std;

/*
Main file for testing binary tree and AVL tree.

Known Issues: 
  On their own binary has gotten to 18 and just 'stopped' before reaching 2'20
  AVL chance of completeing chance of just haulting
  AVL has never made it past 2'8

Author: Bradley Henderson
*/

/*Prints an array*/
void printArray(int[], int);

/*Get the height of a binary/AVL tree*/
int getHeight(BST<int>*, int[], int);

int main() 
{
  srand(time(NULL));

  int size;
  for(int i = 1; i <= 20; i++)
  {
    size = pow(2, i);
    int tempArray[size];

    //Doesn't work in a method, return garbage for random
    for(int i = 0; i < size; i++)
      tempArray[i] = (rand() % 100) + 1;

    cout << "2^" << i << " keys: ";
    cout << getHeight(new BST<int>(), tempArray, size) << " ";
    cout << getHeight(new AvlTree<int>(), tempArray, size) << endl;
  }
}

void printArray(int array[], int size)
{
  for(int i = 0; i < size; i++)
    cout << array[i] << " ";
  cout << endl;
}

int getHeight(BST<int>* root, int nodes[], int size)
{
  for(int i = 0; i < size; i++)
    root->insert(nodes[i]);

  int height = root->height();
  root->~BST(); // to make sure it doesn't exist anymore
  return height;
}