#ifndef _SEQUENCE_LIST_H_
#define _SEQUENCE_LIST_H_
#include "data.h"

#define	MAXSIZE		10
#define	INT_MAX		0x7fffffff

typedef struct {
	ElemType data[MAXSIZE];
	ElemType length;
}SqList;

#endif // !_SEQUENCE_LIST_H_
