/*
 * Test program for AvlTree class. See execution snapshot below at end of file.
 *
 * Author: Drue Coles
 */

#include <iostream>
#include <ctime>
#include <vector>
#include <cmath> 
#include "avl_tree.cpp"
using namespace std;

void test(BST<int>*, int[], int);

int main() {
    //int keys[] = {80, 70, 60, 85, 10, 75, 50, 65, 66, 67, 68, 69};
    //int keys[] = {80, 70, 60, 85, 10, 75, 50/*, 65, 66, 67, 68*/};
    int keys[] = {63,97,98,91,48,78,47,13,85,80,5,16,1,34,81,28,38,40,81,16,2,20,17,29,99,80,25,4,15,5,20,65,25,100,59,96,20,2,23,27,87,25,79,48,9,45,85,96,94,20,7,44,85,70,5,72,23,75,93,89,15,78,26,35,40,82,36,94,52,47,44,40,83,12,12,52,84,50,82,70,5,11,77,27,37,28,42,50,25,8,92,11,59,94,43,94,87,64,54,71,82,5,100,17,69,80,7,9,90,22,82,1,45,98,68,24,78,35,93,59,9,62,30,33,9,25,11,43};
    //int keys[] = {1,2,1,2,1,2,1,2,1,2};

    const int n = 127;
    
    /*cout << "Non-rebalancing BST:" << endl;
    test(new BST<int>(), keys, n);*/

    cout << "\nAVL tree:" << endl;
    test(new AvlTree<int>(), keys, n);

    return 0;
}

void test(BST<int>* p, int keys[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "Inserting " << keys[i] << ": ";
        p->insert(keys[i]);
        cout << *p << "(height = " << p->height() << ")" << endl;
        cout << endl;
        cout << endl;
        cout << endl;
    }
}

/*
Non-rebalancing BST:
Inserting 80: 80 (height = 0)
Inserting 70: 70 80 (height = 1)
Inserting 60: 60 70 80 (height = 2)
Inserting 85: 60 70 80 85 (height = 2)
Inserting 10: 10 60 70 80 85 (height = 3)
Inserting 75: 10 60 70 75 80 85 (height = 3)
Inserting 50: 10 50 60 70 75 80 85 (height = 4)
Inserting 65: 10 50 60 65 70 75 80 85 (height = 4)
Inserting 66: 10 50 60 65 66 70 75 80 85 (height = 4)
Inserting 67: 10 50 60 65 66 67 70 75 80 85 (height = 5)
Inserting 68: 10 50 60 65 66 67 68 70 75 80 85 (height = 6)
Inserting 69: 10 50 60 65 66 67 68 69 70 75 80 85 (height = 7)

AVL tree:
Inserting 80: 80 (height = 0)
Inserting 70: 70 80 (height = 1)
Inserting 60: 60 70 80 (height = 1)
Inserting 85: 60 70 80 85 (height = 2)
Inserting 10: 10 60 70 80 85 (height = 2)
Inserting 75: 10 60 70 75 80 85 (height = 2)
Inserting 50: 10 50 60 70 75 80 85 (height = 2)
Inserting 65: 10 50 60 65 70 75 80 85 (height = 3)
Inserting 66: 10 50 60 65 66 70 75 80 85 (height = 3)
Inserting 67: 10 50 60 65 66 67 70 75 80 85 (height = 3)
Inserting 68: 10 50 60 65 66 67 68 70 75 80 85 (height = 3)
Inserting 69: 10 50 60 65 66 67 68 69 70 75 80 85 (height = 3)
*/