#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Structures.h"

int Binary_Search(SqList* L, int key);
int Binary_Search_Recursion(SqList* L, int key);
BSTNode* BST_Search(BiTree T, int key);
int BST_Insert(BiTree* T, int key);
BiTree BST_Init(int* key, int n);
int BST_Delete(BiTree* T, int key);
int BST_Delete_Path(BiTree* T, int key, BiTree* path, int* top);
int isBST(BiTree T);
AVLNode* AVL_Search(BiTree T, int key);
BiTree AVL_Rotate(BiTree T, char* mode);
int AVL_Insert(BiTree* T, int key);
BiTree AVL_Init(int* key, int n);
int isAVL(BiTree T);
int AVL_Delete(BiTree* T, int key);
int AVL_Delete_Test(BiTree* T, int key);
