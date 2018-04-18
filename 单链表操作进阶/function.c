#include "index.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#pragma once

struct SList{
    DataType data;
    struct SList * next;
};


PNode AddNode(DataType data)    //���ӽ��
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

void SListPushBack(PNode *pHead, DataType data) // β�� 
{
    assert(pHead);
    if (*pHead == NULL) //����Ϊ������,��ֱ������һ�����
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


void SListPrint(PNode pHead)    //��ӡ����
{
    PNode p = pHead;
    while(p)
    {
        printf("%d-->", p->data);
        p = p->next;
    }
    printf("NULL\n");
}
PNode SListFind(PNode pHead, DataType data) // �������в���ֵΪdata��Ԫ�أ��ҵ��󷵻�ֵΪdata�Ľ�� 
{ 
    if (pHead == NULL) //������Ϊ�գ��򷵻�NULL
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
        }   //���Ҳ������򷵻�NULL��
        return NULL;    
    }
}


// �����ӡ������
void PrintSListFromTail2Head(PNode pHead)
{
    if (pHead != NULL)
    {
        PrintSListFromTail2Head(pHead->next);
        printf("%d<--", pHead->data);
    }
    else printf("NULL<--");
}

// ɾ������ķ�β��㣬Ҫ�󣺲��ܱ������� 
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
        printf("�ý��Ϊβ��㣬�޷��ô˷���ɾ��\n");
    }
}

// ������posλ��ǰ����ֵΪdata�Ľ�� 
void InesrtPosFront(PNode pos, DataType data)
{
    PNode pNext = NULL;
    PNode pNew = NULL;
    if (pos == NULL)
    {    
        printf("����ʧ�ܣ���λ�ò�����\n");
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

// ����������м��㣬Ҫ��ֻ�ܱ���һ������ 
PNode FindMiddleNode(PNode pHead)
{
    PNode pFast = pHead;
    PNode pSlow = pHead;
    if (pHead == NULL)  //������Ϊ�գ��򷵻ؿ�
    {
        return NULL;
    }
    if (pFast->next == NULL) //������ֻ��һ����㣬��ô�ͷ��ظý��
    {
        return pHead;
    }
    while(pFast->next && pFast->next->next) //�����������1�������������м��㣬ż�������м�ƫ����
    {
        pFast = pFast->next->next;
        pSlow = pSlow->next;
    }
    return pSlow;
}

// ��������ĵ�����K����㣬Ҫ��ֻ�ܱ���һ������ 
PNode FindLastKNode(PNode pHead, int K)
{
    PNode pBef = NULL;
    PNode pAft = NULL;
    if (pHead == NULL || K<=0)  //��Ϊ�����������Ƿ����򷵻ؿ�
    {
        return NULL;
    }
    pBef = pHead;
    pAft = pHead;
    while(K>1 && pBef)  //��pBef���ƶ�K-1����pBef���ƶ�������Ϊ�գ������ѭ��
    {
        pBef = pBef->next;
        K--;
    }
    if (pBef == NULL)   //��pBef���ƶ�������Ϊ�գ�˵��K��ȡֵ���󣬲��������ء�
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

// ɾ������ĵ�����K����㣬Ҫ��ֻ�ܱ���һ������ 
PNode DeleteLastKNode(PNode pHead, int K)
{
    PNode pDel = NULL;
    PNode pPre = NULL;
    PNode pBef = NULL;
    if (pHead == NULL || K<=0)  //��Ϊ�����������Ƿ����򷵻�
    {
        return pHead;
    }
    pDel = pHead;
    pPre = pHead;
    pBef = pHead;
    while(K>1 && pBef)  //��pBef���ƶ�K-1����pBef���ƶ�������Ϊ�գ������ѭ��
    {
        pBef = pBef->next;
        K--;
    }
    if (pBef == NULL)   //��pBef���ƶ�������Ϊ�գ�˵��K��ȡֵ���󣬲��������ء�
    {
        return pHead;
    }
    while(pBef->next)
    {
        pBef = pBef->next;
        pPre = pDel;
        pDel = pDel->next;
    }
     if (pPre == pDel && pDel->next == NULL) //���ý�����ͷ���Ҳ��β��㣬����free����������
     {
         pHead = NULL;
     }
     else if (pPre == pDel)   //��������ͷ��㣬
     {
         pHead = pHead->next;
     }
     if (pDel->next == NULL) //��������β���
    {
        pPre->next = NULL;
    }
    else                        //�����м���
    {
        pPre->next = pDel->next;
    }
    free(pDel);
    return pHead;
    
}

// �õ�����ʵ��Լɪ�� 
void JosephCircle(PNode* pHead, const int M)
{
    PNode pBef = NULL;
    PNode pAft = NULL;
    assert(pHead);
    if (*pHead == NULL || (*pHead)->next == NULL)   //������Ϊ�ջ���������ֻ��һ����㣬��ɶ������
    {
        return;
    }
    pBef = *pHead;
    pAft = *pHead;
    while(pBef->next)       //��������β����
    {
        pBef = pBef->next;
    }
    pBef->next = *pHead;
    pBef = *pHead;
    while(1)                //��Ϸ��ʼ��ֱ��ʣ���һ�����Ž���
    {
        PNode pPRint = NULL;
        int i = 1;
        if (pBef->next == pBef)     //��ʣ�����һ����㣬�����
        {
            printf("%d\n", pBef->data);
            return;
        }
        while(i<M)      //Լɪ������˱���
        {
            pAft = pBef;
            pBef = pBef->next;
            i++;
        }
        pAft->next = pBef->next;    //���˳����˳�
        free(pBef);                 
        pAft = pAft->next;          //������
        pBef = pAft;
        
        pPRint = pBef;              //��ӡÿһ�εĽ��
        while(pPRint->next != pBef)
        {
            printf("%d-->", pPRint->data);
            pPRint = pPRint->next;
        }
        printf("%d-->", pPRint->data);
        printf("\n");
    }
}

// ���������--����ָ�� 
void ReverseSList(PNode* pHead)
{
    PNode pBef = NULL;
    PNode pCur = NULL;
    PNode pAft = NULL;
    assert(pHead);
    if (*pHead == NULL || (*pHead)->next == NULL)   //������Ϊ�ջ���������ֻ��һ����㣬��ɶ������
    {
        return;
    }
    
    pBef = (*pHead)->next;      //����ָ��ĳ�ʼ��
    pCur = *pHead;
    pAft = NULL;
    while(pBef)                 //�������һ��������ÿ�������֮ǰ�Ľ������
    {
        pCur->next = pAft;
        pAft = pCur;
        pCur = pBef;
        pBef = pBef->next;
    }
    pCur->next = pAft;      //�����һ������뵹���ڶ����������
    *(pHead) = pCur;        //�޸�ͷָ��
}

// ���������--ͷ�巨
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

// ��ð������˼��Ե������������ 
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

// �ϲ��������������ϲ�����Ȼ���� 
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

// �ж������������Ƿ��ཻ---�������� 
int IsSListCross(PNode pHead1, PNode pHead2)
{   
    PNode pTail1 = NULL;
    PNode pTail2 = NULL;
    if (pHead1 == NULL || pHead2 == NULL)   //������һ������Ϊ�գ������
    {
        return -1;
    }
    pTail1 = pHead1;
    pTail2 = pHead2;
    while(pTail1)       //�ҵ���һ���������β��
    {
        pTail1 = pTail1->next;
    }
    while(pTail2)       //�ҵ��ڶ����������β��
    {
        pTail2 = pTail2->next;
    }
    if (pTail1 == pTail2)   //�Ƚ����������β���Ƿ���ͬ
    {
        return 1
    }
    return 0;
}

// �������������ཻ�Ľ���---�������� 
PNode GetCorssNode(PNode pHead1, PNode pHead2)
{
    PNode pN1 = pHead1;
    PNode pN2 = pHead2;
    int len1 = 0;
    int len2 = 0;
    if (pHead1 == NULL || pHead2 == NULL)   //������һ������Ϊ�գ������
    {
        return NULL
    }
    while(pN1)  //���һ������ĳ���
    {
        len1++;
        pN1 = pN1->next;
    }
    while(pN2)  //��ڶ�������ĳ���
    {
        len2++;
        pN2 = pN2->next;
    }
    if (pN1 == pN2) //����н��㣬���󽻵㡣û�н����򷵻�NULL
    {
        int count = len1-len2;
        pN1 = pHead1;
        pN2 = pHead2;
        if (len1>=len2) //����һ�����������õ�һ�������ָ������
        { 
            while(count>0)
            {
                pN1 = pN1->next;
                count--;
            }
        }
        else            //���ڶ������������õڶ��������ָ������
        {
            while(count<0)
            {
                pN2 = pN2->next;
                count++;
            }
        }
        while(pN1 && pN2)   //��ָ��ͬ���ߣ��ߵ�����ͷ���
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