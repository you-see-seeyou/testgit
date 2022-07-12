#ifndef _TREE_H_
#define _TREE_H_
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#define SLEN 20
#define MAXITEMS 10
//定义项
typedef struct item
{
    char petname[SLEN];
    char petkind[SLEN];
}Item;
//定义节点
typedef struct trnode
{
    Item item;
    struct trnode * left;
    struct trnode * right;
}Trnode;
//定义树
typedef struct tree
{
    Trnode * root;
    int size;
}Tree;


//初始化树
void Init_Tree(Tree* ptree);
//确定树是否空
bool TreeIsEmpty(const Tree* ptree);
//确定树是否满
bool TreeIsFull(const Tree* ptree);
//返回树项数
int TreeItemCount(const Tree* ptree);
//添加一个项
bool AddItem(const Item* pi , Tree* ptree);
//查找一个项
bool InTree(const Item* pi , const Tree* ptree);
//删除一个项
bool DeleteItem(const Item* pi , Tree* ptree);
//遍历一个树
void Traverse(const Tree*ptree,void(* pfun)(Item item));
//清空树
void DeleteAll(Tree* ptree);

#endif