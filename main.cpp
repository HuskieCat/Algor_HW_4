#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "avl_tree.cpp"

using namespace std;

void generateAtSize(int[], int);
void printArray(int[], int);
int test(BST<int>*, int[], int);

int main() 
{
  srand(time(NULL));
  int size;
  for(int i = 1; i <= 20; i++)
  {
    size = pow(2, i);

    //size = 10;
    int tempArray[size];
    //int tempArray[] = {6,7,6,7,6,7,6,7,6,7};

    for(int i = 0; i < size; i++)
      tempArray[i] = (rand() % 100) + 1;

    //printArray(tempArray, size);

    cout << "2^" << i << " keys: ";
    //cout << test(new BST<int>(), tempArray, size) << " ";
    cout << test(new AvlTree<int>(), tempArray, size) << endl;
  }
}

void generateAtSize(int array[], int size)
{
  int tempArray[size];
  for(int i = 0; i < size; i++)
    tempArray[i] = (rand() % 10) + 1;
  array = tempArray;
}

void printArray(int array[], int size)
{
  for(int i = 0; i < size; i++)
    cout << array[i] << " ";
  cout << endl;
}

int test(BST<int>* root, int nodes[], int size)
{
  int height;
  for(int i = 0; i < size; i++)
  {
    //cout << "Inserting " << nodes[i] << ": ";
    root->insert(nodes[i]);
  }
  cout << *root << "(Height = " << root->height() << ")" << endl;
  height = root->height();
  root->~BST();
  return height;
}