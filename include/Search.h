#include <stdio.h>
#include <stdlib.h>
#include "Structures.h"

int Binary_Search(SqList* L, int key);
int Binary_Search_Recursion(SqList* L, int key);
BSTNode* BST_Search(BiTree T, int key);
int BST_Insert(BiTree* T, int key);
BiTree BST_Init(int* key, int n);
int BST_Delete(BiTree T, int key);
int isBST(BiTree T);
