#include "index.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#pragma once

struct SList{
    DataType data;
    struct SList * next;
};


PNode AddNode(DataType data)    //增加结点
{
    PNode p = (PNode)malloc(sizeof(Node));
    if (p != NULL)
    {
        p->data = data;
        p->next = NULL;
        return p;
    }
    assert(p);
    return NULL;
}

void SListPushBack(PNode *pHead, DataType data) // 尾插 
{
    assert(pHead);
    if (*pHead == NULL) //链表为空链表,则直接增加一个结点
    {
        *pHead = AddNode(data);
    }
    else    
    {
        PNode p = *pHead;
        while (p->next)
        {
            p = p->next;
        }
        p->next = AddNode(data);
    }
}


void SListPrint(PNode pHead)    //打印链表
{
    PNode p = pHead;
    while(p)
    {
        printf("%d-->", p->data);
        p = p->next;
    }
    printf("NULL\n");
}
PNode SListFind(PNode pHead, DataType data) // 在链表中查找值为data的元素，找到后返回值为data的结点 
{ 
    if (pHead == NULL) //若链表为空，则返回NULL
    {
        return NULL;         
    }
    else
    {
        PNode pCur = pHead;
        while(pCur)
        {
            if (pCur->data == data)
            {
                return pCur;
            }
            pCur = pCur->next;
        }   //若找不到，则返回NULL。
        return NULL;    
    }
}


// 逆序打印单链表
void PrintSListFromTail2Head(PNode pHead)
{
    if (pHead != NULL)
    {
        PrintSListFromTail2Head(pHead->next);
        printf("%d<--", pHead->data);
    }
    else printf("NULL<--");
}

// 删除链表的非尾结点，要求：不能遍历链表 
void DeleteListNotTailNode(PNode pos)
{
    if (pos->next)
    {
        PNode pNex = pos->next;
        pos->data = pNex->data;
        pos->next = pNex->next;
        free(pNex);
    }
    else
    {
        printf("该结点为尾结点，无法用此方法删除\n");
    }
}

// 在链表pos位置前插入值为data的结点 
void InesrtPosFront(PNode pos, DataType data)
{
    PNode pNext = NULL;
    PNode pNew = NULL;
    if (pos == NULL)
    {    
        printf("插入失败，该位置不存在\n");
        return;
    }
    pNew = AddNode(data);
    if (pos->next == NULL)
    {
        pos->next = pNew;
    }
    else
    {
        pNext = pos->next;
        pos->next = pNew;
        pNew->next = pNext;
    }
    pos->data ^= pNew->data;
    pNew->data ^= pos->data;
    pos->data ^= pNew->data;
}

// 查找链表的中间结点，要求只能遍历一次链表 
PNode FindMiddleNode(PNode pHead)
{
    PNode pFast = pHead;
    PNode pSlow = pHead;
    if (pHead == NULL)  //若链表为空，则返回空
    {
        return NULL;
    }
    if (pFast->next == NULL) //若链表只有一个结点，那么就返回该结点
    {
        return pHead;
    }
    while(pFast->next && pFast->next->next) //若结点数多于1，则奇数返回中间结点，偶数返回中间偏左结点
    {
        pFast = pFast->next->next;
        pSlow = pSlow->next;
    }
    return pSlow;
}

// 查找链表的倒数第K个结点，要求只能遍历一次链表 
PNode FindLastKNode(PNode pHead, int K)
{
    PNode pBef = NULL;
    PNode pAft = NULL;
    if (pHead == NULL || K<=0)  //若为空链表或输入非法，则返回空
    {
        return NULL;
    }
    pBef = pHead;
    pAft = pHead;
    while(K>1 && pBef)  //当pBef先移动K-1步或pBef在移动过程中为空，则结束循环
    {
        pBef = pBef->next;
        K--;
    }
    if (pBef == NULL)   //若pBef在移动过程中为空，说明K的取值过大，不合理，返回。
    {
        return NULL;
    }
    while(pBef->next)
    {
        pBef = pBef->next;
        pAft = pAft->next;
    }
    return pAft;
}

// 删除链表的倒数第K个结点，要求只能遍历一次链表 
PNode DeleteLastKNode(PNode pHead, int K)
{
    PNode pDel = NULL;
    PNode pPre = NULL;
    PNode pBef = NULL;
    if (pHead == NULL || K<=0)  //若为空链表或输入非法，则返回
    {
        return pHead;
    }
    pDel = pHead;
    pPre = pHead;
    pBef = pHead;
    while(K>1 && pBef)  //当pBef先移动K-1步或pBef在移动过程中为空，则结束循环
    {
        pBef = pBef->next;
        K--;
    }
    if (pBef == NULL)   //若pBef在移动过程中为空，说明K的取值过大，不合理，返回。
    {
        return pHead;
    }
    while(pBef->next)
    {
        pBef = pBef->next;
        pPre = pDel;
        pDel = pDel->next;
    }
     if (pPre == pDel && pDel->next == NULL) //若该结点既是头结点也是尾结点，在则free掉整个链表
     {
         pHead = NULL;
     }
     else if (pPre == pDel)   //若仅仅是头结点，
     {
         pHead = pHead->next;
     }
     if (pDel->next == NULL) //若仅仅是尾结点
    {
        pPre->next = NULL;
    }
    else                        //若是中间结点
    {
        pPre->next = pDel->next;
    }
    free(pDel);
    return pHead;
    
}

// 用单链表实现约瑟夫环 
void JosephCircle(PNode* pHead, const int M)
{
    PNode pBef = NULL;
    PNode pAft = NULL;
    assert(pHead);
    if (*pHead == NULL || (*pHead)->next == NULL)   //若链表为空或者链表中只有一个结点，则啥都不干
    {
        return;
    }
    pBef = *pHead;
    pAft = *pHead;
    while(pBef->next)       //将链表首尾相连
    {
        pBef = pBef->next;
    }
    pBef->next = *pHead;
    pBef = *pHead;
    while(1)                //游戏开始，直到剩最后一个结点才结束
    {
        PNode pPRint = NULL;
        int i = 1;
        if (pBef->next == pBef)     //若剩下最后一个结点，则结束
        {
            printf("%d\n", pBef->data);
            return;
        }
        while(i<M)      //约瑟夫环里的人报数
        {
            pAft = pBef;
            pBef = pBef->next;
            i++;
        }
        pAft->next = pBef->next;    //该退出的退出
        free(pBef);                 
        pAft = pAft->next;          //调整环
        pBef = pAft;
        
        pPRint = pBef;              //打印每一次的结果
        while(pPRint->next != pBef)
        {
            printf("%d-->", pPRint->data);
            pPRint = pPRint->next;
        }
        printf("%d-->", pPRint->data);
        printf("\n");
    }
}

// 链表的逆置--三个指针 
void ReverseSList(PNode* pHead)
{
    PNode pBef = NULL;
    PNode pCur = NULL;
    PNode pAft = NULL;
    assert(pHead);
    if (*pHead == NULL || (*pHead)->next == NULL)   //若链表为空或者链表中只有一个结点，则啥都不干
    {
        return;
    }
    
    pBef = (*pHead)->next;      //三个指针的初始化
    pCur = *pHead;
    pAft = NULL;
    while(pBef)                 //将除最后一个结点外的每个结点与之前的结点逆序
    {
        pCur->next = pAft;
        pAft = pCur;
        pCur = pBef;
        pBef = pBef->next;
    }
    pCur->next = pAft;      //将最后一个结点与倒数第二个结点逆序
    *(pHead) = pCur;        //修改头指针
}

// 链表的逆置--头插法
PNode ReverseSListOP(PNode pHead)
{
    PNode pCur = NULL;
    PNode pNext = NULL;
    if (pHead == NULL || pHead->next == NULL)
    {
        return pHead;
    }
    pCur = pHead;
    pNext = pHead->next;
    pHead->next = NULL;
    while(pNext)
    {
        pCur = pNext;
        pNext = pNext->next;
        pCur->next = pHead;
        pHead = pCur;
    }
    return pHead;
}   

// 用冒泡排序思想对单链表进行排序 
void BubbleSort(PNode pHead)
{
    PNode pMax = NULL;
    PNode pNex = NULL;
    PNode pSim = NULL;
    if (pHead == NULL || pHead->next == NULL)  
    {
        return;
    }
    pMax = pHead;
    pNex = pMax->next;
    while(pHead->next != pSim)
    {
        while(pNex->next != pSim)
        {
            if(pMax->data > pNex->data)
            {
                pMax->data ^= pNex->data;
                pNex->data ^= pMax->data;
                pMax->data ^= pNex->data;
            }
                pMax = pNex;
                pNex = pNex->next;
        }
        if (pNex->next == pSim)
        {
            if(pMax->data > pNex->data)
            {
                pMax->data ^= pNex->data;
                pNex->data ^= pMax->data;
                pMax->data ^= pNex->data;
            }
        }
        pSim = pNex;
        pMax = pHead;
        pNex = pMax->next;
    }
    SListPrint(pHead);
}

// 合并两个有序单链表，合并后依然有序 
PNode MergeSList(PNode pHead1, PNode pHead2)
{
    PNode p1 = NULL;
    PNode p2 = NULL;
    PNode pRes = NULL;
    int sign = 0;
    if (pHead1 == NULL && pHead2 == NULL)
    {
        return NULL;
    }
    if (pHead1 == NULL)
    {
        return pHead2;
    }
    if (pHead2 == NULL)
    {
        return pHead1;
    }
    p1 = pHead1;
    p2 = pHead2;
    if (p1->data <= p2->data)
    {
        pRes = p1;
        p1 = p1->next;
        sign = 1;
    }
    else
    {
        pRes = p2;
        p2 = p2->next;
        sign = 2;
    }
    while(p1 && p2)
    {
        if (p1->data <= p2->data)
        {
            pRes->next = p1;
            p1 = p1->next;
            pRes = pRes->next;
        }
        else
        {
            pRes->next = p2;
            p2 = p2->next;
            pRes = pRes->next;
        }
    }
    if (p1 == NULL)
    {
        pRes->next = p2;
    }
    if (p2 == NULL)
    {
        pRes->next = p1;
    }
    if (sign == 1)
    {
        return pHead1;
    }
    else return pHead2;
}

// 判断两个单链表是否相交---链表不带环 
int IsSListCross(PNode pHead1, PNode pHead2)
{   
    PNode pTail1 = NULL;
    PNode pTail2 = NULL;
    if (pHead1 == NULL || pHead2 == NULL)   //若其中一个链表为空，则错误
    {
        return -1;
    }
    pTail1 = pHead1;
    pTail2 = pHead2;
    while(pTail1)       //找到第一个单链表的尾部
    {
        pTail1 = pTail1->next;
    }
    while(pTail2)       //找到第二个单链表的尾部
    {
        pTail2 = pTail2->next;
    }
    if (pTail1 == pTail2)   //比较两个链表的尾部是否相同
    {
        return 1
    }
    return 0;
}

// 求两个单链表相交的交点---链表不带环 
PNode GetCorssNode(PNode pHead1, PNode pHead2)
{
    PNode pN1 = pHead1;
    PNode pN2 = pHead2;
    int len1 = 0;
    int len2 = 0;
    if (pHead1 == NULL || pHead2 == NULL)   //若其中一个链表为空，则错误
    {
        return NULL
    }
    while(pN1)  //求第一个链表的长度
    {
        len1++;
        pN1 = pN1->next;
    }
    while(pN2)  //求第二个链表的长度
    {
        len2++;
        pN2 = pN2->next;
    }
    if (pN1 == pN2) //如果有交点，则求交点。没有交点则返回NULL
    {
        int count = len1-len2;
        pN1 = pHead1;
        pN2 = pHead2;
        if (len1>=len2) //若第一个链表长，就让第一个链表的指针先走
        { 
            while(count>0)
            {
                pN1 = pN1->next;
                count--;
            }
        }
        else            //若第二个链表长，就让第二个链表的指针先走
        {
            while(count<0)
            {
                pN2 = pN2->next;
                count++;
            }
        }
        while(pN1 && pN2)   //两指针同步走，走到交点就返回
        {
            if (pN1 == pN2)
            {
                return pN1;
            }
            pN1 = pN1->next;
            pN2 = pN2->next;
        } 
    }
    return NULL;
}