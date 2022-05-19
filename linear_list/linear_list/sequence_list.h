#ifndef _SEQUENCE_LIST_H_
#define _SEQUENCE_LIST_H_
#include "data.h"

#define	MAXSIZE		10

typedef struct {
	ElemType data[MAXSIZE];
	ElemType length;
}SqList;

#endif // !_SEQUENCE_LIST_H_
