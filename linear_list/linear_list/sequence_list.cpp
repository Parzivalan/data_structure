#include "sequence_list.h"
#include <iostream>

/******************************************************************
* 删除顺序表中值最小的元素，并用表中最后一个元素的值填充
* 返回被删除元素的值
******************************************************************/
bool Del_Min_SqList(SqList& L, ElemType& value) {
	if (L.length == 0)		//使用的是L.length而不是L->length的原因：引用相当于是直接拿到了该变量，而不是它的指针
		return false;
	value = L.data[0];
	int pos = 0;
	for (int i = 1; i < L.length; i++) {
		if (L.data[i] < value) {
			value = L.data[i];
			pos = i;
		}
	}
	L.data[pos] = L.data[L.length - 1];		//这两句如果放在if中，如果最小值刚好是在表尾，则要执行多次，浪费性能！
	L.length--;
	
	return true;
}

/******************************************************************
* 顺序表的逆置
******************************************************************/
void Reverse_SqList(SqList& L) {
	ElemType temp;
	for (int i = 0; i < L.length / 2; i++) {
		temp = L.data[i];
		L.data[i] = L.data[L.length - 1 - i];
		L.data[L.length - 1 - i] = temp;
	}
}

/******************************************************************
* 顺序表的按值删除
* 用k记录顺序表中不等于x的元素个数，扫描时将不等于x的元素移动到下标k的位置
* 另一种方法是用k记录顺序表中等于x的元素个数，边扫描边统计，并将不等于x的元素前移k个位置
* 时间复杂度为O(n)，空间复杂度为O(1)
******************************************************************/
bool Delete_SqList(SqList& L, ElemType x) {
	int k = 0;
	for (int i = 0; i < L.length; i++) {
		if (L.data[i] != x) {
			L.data[k] = L.data[i];
			k++;
		}
	}
	L.length = k;

	return true;
}

/******************************************************************
* 删除有序顺序表中值为s-t的所有元素(s<t);
* 因为是有序表，故可先找到第一个要删除的元素，再找到最后一个要删除的元素，
* 再将最后一个要删除的元素前移即可;
******************************************************************/
bool Delete_SqList_From_s_to_t1(SqList& L, ElemType s, ElemType t) {
	int i, j;
	if (s >= t || !L.length)
		return false;
	for (i = 0; i < L.length && L.data[i] < s; i++);	//找到第一个大于等于s的值
	if (i > L.length)
		return false;		//所有值都小于s，返回
	for (j = i; j < L.length && L.data[j] <= t; j++);	//找到第一个大于t的值
	for (; j < L.length; i++, j++)
		L.data[i] = L.data[j];
	L.length = i;

	return true;
}

/******************************************************************
* 功能：删除顺序表中值为s-t的所有元素(包含s和t，且s<t);
* 方法：从前向后扫描，用k记录符合条件的值的个数，若不符合条件则该值前移k位
******************************************************************/
bool Delete_SqList_From_s_to_t2(SqList& L, ElemType s, ElemType t) {
	int i=0,k = 0;
	if (s >= t || !L.length)
		return false;
	while (i < L.length) {
		if (L.data[i] >= s && L.data[i] <= t) {	//统计符合要求的值的个数
			k++;
		}
		else {
			L.data[i - k] = L.data[i];			//将当前值前移k位
			i++;
		}
	}
	L.length -= k;

	return true;
}

/******************************************************************
* 功能：从有序顺序表中删除重复的元素;
* 方法：开始时将第一个元素视为非重复的有序表，之后一次判断后面的元素是否与前面非重复有序表的最后一个元素相同，
* 若相同，则继续向后判断，若不同，则插入前面的非重复有序表的最后，直至判断到表尾为止。
******************************************************************/
bool Delete_SqList_Same(SqList& L) {
	int i, j;
	if (!L.length)
		return false;
	for (i = 0, j = 1; j < L.length; j++)	//i存储第一个不相同的元素，j作为工作指针
		if (L.data[i] != L.data[j])
			L.data[++i] = L.data[j];
	L.length = i + 1;

	return true;
}

/******************************************************************
* 功能：将两个有序顺序表合并为一个新有序顺序表，并返回该顺序表;
* 方法：按顺序取两个表中表头较小的结点存入新的顺序表中。然后看哪个表还有剩余，将余下的部分加入到新表的后面。
******************************************************************/
bool Merge_SqList(SqList A, SqList B, SqList &C) {
	if (A.length + B.length > C.length)
		return false;
	int i = 0, j = 0, k = 0;
	while (i < A.length && j < B.length) {	//循环，两两比较，小者存入结果表
		if (A.data[i] <= B.data[j])
			C.data[k++] = A.data[i++];
		else
			C.data[k++] = B.data[j++];
	}
	while (i < A.length)
		C.data[k++] = A.data[i++];
	while (j < B.length)
		C.data[k++] = B.data[j++];
	C.length = k;

	return true;
}