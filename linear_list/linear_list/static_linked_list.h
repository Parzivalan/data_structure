#ifndef _STATIC_LINKED_LIST_H_
#define _STATIC_LINKED_LIST_H_

#define MAXSIZE 10		//静态链表的最大长度

typedef struct {
	int data;
	int next;			//下一个元素的数组下标
}SLinkList[MAXSIZE];
/******************************************************
* 上面这段代码等同于：
* 
*	typedef struct Node {
*		int data;
*		int next;			//下一个元素的数组下标
*	};
*	typedef struct Node SLinkList[MAXSIZE];	//后面可直接使用SLinkList定义一个长度为[MAXSIZE]的Node型数组
*
******************************************************/


#endif // !_STATIC_LINKED_LIST_H_
