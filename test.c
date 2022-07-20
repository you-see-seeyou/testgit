/*
 * Copyright (c) 2022 by you-see-seeyou 434886232@qq.com, All Rights Reserved. 
 * @LastEditors: you-see-seeyou 434886232@qq.com
 * @LastEditTime: 2022-07-20 17:41:19
 * @FilePath: /hq/testgit/test.c
 * 
 * @Description: 
 * @Date: 2022-07-20 17:40:50
 * @Author: you-see-seeyou 434886232@qq.com
 */

#include<stdio.h>
#define world  "hahaha"
#define num  10000

extern int extern_a;
/**
 * @description: 
 * @param {int} a
 * @param {int} n
 * @return {*}
 */
int change_a(int a[],int n)
{
    for (int i = 0; i < n; i++)
    {
        a[i]+=1;
    }
}
int change_p(int *a,int n)
{
    for (int i = 0; i < n; i++)
    {
        a[i]+=1;
    }
}

int main(int argc, char const *argv[])
{
    int a[5] = {1,2,3,4,5};
    const int *p = a;
    p++;
    int * const q = a;
    (*q)++;
    //change_a(a,5);
    change_p(a,5);
    for (int i = 0; i < 5; i++)
    {
        printf("a[%d] = %d\n",i,a[i]);
    }
    char str[] = "hello world";
    str[0] = 'H';
    char * pstr = world;
    printf("sizeof(%s)  = %ld \n",str,sizeof(str));
    printf("extern_a = %d \n",extern_a);
    
    return 0;
}
