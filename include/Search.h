#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Structures.h"

#define MAX_LEN 15

int Binary_Search(SqList* L, int key);
int Binary_Search_Recursion(SqList* L, int key);

BSTNode* BST_Search(BSTTree T, int key);
int BST_Insert(BSTTree* T, int key);
BSTTree BST_Init(int* key, int n);
int BST_Delete(BSTTree* T, int key);
int BST_Delete_Path(BSTTree* T, int key, BSTTree* path, int* top);
int isBST(BSTTree T);

int SgetHeight(SearchTree T);
AVLNode* AVL_Search(AVLTree T, int key);
SearchTree Rotate(SearchTree T, char* mode);
int AVL_Insert(AVLTree* T, int key);
AVLTree AVL_Init(int* key, int n);
int isAVL(AVLTree T);
int AVL_Delete(AVLTree* T, int key);
int AVL_Delete_Test(AVLTree* T, int key);

RBNode* RB_Search(RBTree T, int key);
int RB_Insert(RBTree* T, int key);
RBTree RB_Init(int* key, int n);
int isRB(RBTree T);
