'''
Copyright (c) 2022 by you-see-seeyou 434886232@qq.com, All Rights Reserved. 
LastEditors: you-see-seeyou 434886232@qq.com
LastEditTime: 2022-07-22 14:27:13
FilePath: /hq/testgit/7.15.py

Description: 
Date: 2022-07-22 14:10:54
Author: you-see-seeyou 434886232@qq.com
'''

from numpy import true_divide

def fun(name):
        print("this is fun")
        for x in name:
                print(x)

true = 1
i = 5
name = ["hequan","zhangsan","lisi","wangwu"]
xinhuazidian ={
        "h":"hequan",
        "z":"zhangsan",
        "l":"lisi",
        "w":"wangwu",
}
print("this is xinhuazidian")
for x in xinhuazidian:
        print(x,xinhuazidian[x])
it = iter(name)
for it in name:
        print(it)
fun(name)
#this is if-else
if true:
        print("the first file.py")
else:
        print("python must learn more")
while(i > 1):
        print("\n")
        print("i==",i)
        i-=1
     