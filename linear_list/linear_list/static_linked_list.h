#ifndef _STATIC_LINKED_LIST_H_
#define _STATIC_LINKED_LIST_H_

#define MAXSIZE 10		//��̬�������󳤶�

typedef struct {
	int data;
	int next;			//��һ��Ԫ�ص������±�
}SLinkList[MAXSIZE];
/******************************************************
* ������δ����ͬ�ڣ�
* 
*	typedef struct Node {
*		int data;
*		int next;			//��һ��Ԫ�ص������±�
*	};
*	typedef struct Node SLinkList[MAXSIZE];	//�����ֱ��ʹ��SLinkList����һ������Ϊ[MAXSIZE]��Node������
*
******************************************************/


#endif // !_STATIC_LINKED_LIST_H_
