#include "tree.h"

//局部数据类型
typedef struct pair
{
    Trnode * parent;
    Trnode * child;
}Pair;

/*局部函数*/
//创建节点
static Trnode* MakeNode(const Item* pi);
//添加节点
static void AddNode(Trnode* new_node , Trnode* root);
//查找节点
static Pair SeekItem(const Item* pi,const Tree* ptree);
//左子树添加
static bool ToLeft(const Item* i1 ,const Item* i2);
//右子树添加
static bool ToRight(const Item* i1 ,const Item* i2);
/*删除节点
*ptr 指向目标删除节点的父节点指针成员的地址*/
static void DeleteNode(Trnode** ptr);
/*遍历规则  左根右 */
static void InOrder(const Trnode* root, void(*pfun)(Item item));
//删除全部节点
static void DeleteAllNodes(Trnode* root);


void Init_Tree(Tree* ptree)
{
    ptree->root = NULL;
    ptree->size = 0;
}

bool TreeIsEmpty(const Tree* ptree)
{
    if (ptree->root == NULL)
        return true;
    else
        return false;
    
}

bool TreeIsFull(const Tree * ptree)
{
    if (ptree->size == MAXITEMS)
        return true;
    else
        return false;
    
}

int TreeItemCount(const Tree *ptree)
{
    return ptree->size;
}

bool AddItem(const Item* pi , Tree* ptree)
{
    Trnode* new_node;
    if(TreeIsFull(ptree))
    {
        fprintf(stderr,"tree is full\n");
        return false;
    }
    if (SeekItem(pi,ptree).child != NULL)
    {
        fprintf(stderr,"attempted to add duplicate item\n");
        return false;
    }
    new_node = MakeNode(pi);
    if (new_node ==NULL)
    {
        fprintf(stderr,"couldn't create node\n");
        return false;
    }
    //成功创建一个新的节点
    ptree->size++;
    if (ptree->root ==NULL)             /*情况1  空树*/
        ptree->root = new_node;         //新节点即为树的节点
    else                                //情况2 树不为空
        AddNode(new_node,ptree->root);  //在树上添加新节点
    return true;
    
}

bool InTree(const Item * pi , const Tree*ptree)
{
    return (SeekItem(pi ,ptree).child ==NULL) ? false:true;
}

bool DeleteItem(const Item * pi , Tree*ptree)
{
    Pair look;
    look = SeekItem(pi,ptree);
    if(look.child == NULL)
        return false;

    if (look.parent == NULL)               //删除根节点项
        DeleteNode(&ptree->root);
    else if(look.parent->left == look.child)
        DeleteNode(&look.parent->left);
    else
        DeleteNode(&look.parent->right);
    ptree->size--;
    
    return true;
}

void Traverse(const Tree*ptree,void(*pfun)(Item item))
{
    if (ptree != NULL)
        InOrder(ptree->root,pfun);
}

void DeleteAll(Tree * ptree)
{
    if (ptree != NULL)
        DeleteAllNodes(ptree->root);
    ptree->root =NULL;
    ptree->size = 0;
}

static Trnode * MakeNode(const Item * pi)
{
    Trnode * new_node;
    new_node = (Trnode *)malloc(sizeof(Trnode));
    if(new_node != NULL)
    {
        new_node->item = *pi;
        new_node->left = NULL;
        new_node->right = NULL;
    }
    return new_node;
}

static void AddNode(Trnode * new_node , Trnode* root)
{
    if (ToLeft(&new_node->item,&root->item))      //往左树添加
    {
        if(root->left == NULL)                    //左树为空
            root->left = new_node;
        else
            AddNode(new_node,root->left);         //左树非空则添加到左树的子树
    }
    else if(ToRight(&new_node->item,&root->item))//往右树添加
    {
        if(root->right == NULL)                  //右树为空
            root->right = new_node;
        else
            AddNode(new_node,root->right);      //右树非空则添加到右树的子树 
    }
    else                                        //不允许重复项
    {
        fprintf(stderr,"location error in addnode\n");
        exit(1);
    } 
}

static Pair SeekItem(const Item * pi,const Tree * ptree)
{
    Pair look;
    look.parent =NULL;
    look.child =ptree->root;
    if (look.child == NULL)
        return look;
    while (look.child != NULL)
    {
        if (ToLeft(pi,&(look.child->item)))
        {
            look.parent = look.child;
            look.child = look.child->left;
        }
        else if (ToRight(pi,&(look.child->item)))
        {
            look.parent = look.child;
            look.child = look.child->right;
        }
        else
            break;
    }
    return look;
}

static bool ToLeft(const Item * i1 ,const Item *i2)
{
    int comp1;
    if((comp1 = strcmp(i1->petname , i2->petname)) < 0 )
        return true;
    else if(comp1 == 0 && strcmp(i1->petkind,i2->petkind) < 0)
        return true;
    else 
        return false;
}

static bool ToRight(const Item * i1 ,const Item *i2)
{
    int comp1;
    if((comp1 = strcmp(i1->petname , i2->petname)) > 0 )
        return true;
    else if(comp1 == 0 && strcmp(i1->petkind,i2->petkind) > 0)
        return true;
    else 
        return false;
}

static void DeleteNode(Trnode **ptr)
{
    Trnode * temp;
    if ((*ptr)->left ==NULL)
    {
        temp = *ptr;
        *ptr = (*ptr)->right;
        free(temp);
    }
    else if ((*ptr)->right ==NULL)
    {
        temp = *ptr;
        *ptr = (*ptr)->left;
        free(temp);
    }
    else/*被删除节点有两个子树*/
    {
        for (temp  = (*ptr)->left; temp->right != NULL; temp = temp->right)
        {
            continue;
            temp->right = (*ptr)->right;
            temp = *ptr;
            *ptr = (*ptr)->left;
            free(temp);
        }   
    } 
}

static void InOrder(const Trnode * root, void(*pfun)(Item item))
{
    if (root != NULL)
    {
        InOrder(root->left,pfun);
        (*pfun)(root->item);        //打印规则
        InOrder(root->right,pfun);
    }
}

static void DeleteAllNodes(Trnode* root)
{
    Trnode* pright;
    if(root != NULL)
    {
        pright = root->right;
        DeleteAllNodes(root->left);
        free(root);
        DeleteAllNodes(pright);
    }
}
