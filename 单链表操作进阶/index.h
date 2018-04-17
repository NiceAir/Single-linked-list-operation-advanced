#include <stdio.h>

typedef int DataType;


typedef struct SList * PNode, Node;


void PrintSListFromTail2Head(PNode pHead);  // �����ӡ������ 
void DeleteListNotTailNode(PNode pos);  // ɾ������ķ�β��㣬Ҫ�󣺲��ܱ�������  
void InesrtPosFront(PNode pos, DataType data);  // ������posλ��ǰ����ֵ��data�Ľ�� 
PNode FindMiddleNode(PNode pHead);  // ����������м��㣬Ҫ��ֻ�ܱ���һ������ 
PNode FindLastKNode(PNode pHead, int K);    // ��������ĵ�����K����㣬Ҫ��ֻ�ܱ���һ������ 
PNode DeleteLastKNode(PNode pHead, int K);  // ɾ������ĵ�����K����㣬Ҫ��ֻ�ܱ���һ������    
void JosephCircle(PNode* pHead, const int M);   // �õ�����ʵ��Լɪ�� 
void ReverseSList(PNode* pHead);    // ���������--����ָ��  
PNode ReverseSListOP(PNode pHead);  // ���������--ͷ�巨 
void BubbleSort(PNode pHead);   // ��ð������˼��Ե������������ 
PNode MergeSList(PNode pHead1, PNode pHead2);   // �ϲ��������������ϲ�����Ȼ���� 
int IsSListCross(PNode pHead1, PNode pHead2);   // �ж������������Ƿ��ཻ---�������� 
PNode GetCorssNode(PNode pHead1, PNode pHead2); // �������������ཻ�Ľ���---�������� 

