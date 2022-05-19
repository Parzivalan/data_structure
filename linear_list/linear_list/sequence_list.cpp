#include "sequence_list.h"
#include <iostream>

/******************************************************************
* ɾ��˳�����ֵ��С��Ԫ�أ����ñ������һ��Ԫ�ص�ֵ���
* ���ر�ɾ��Ԫ�ص�ֵ
******************************************************************/
bool Del_Min_SqList(SqList& L, ElemType& value) {
	if (L.length == 0)		//ʹ�õ���L.length������L->length��ԭ�������൱����ֱ���õ��˸ñ���������������ָ��
		return false;
	value = L.data[0];
	int pos = 0;
	for (int i = 1; i < L.length; i++) {
		if (L.data[i] < value) {
			value = L.data[i];
			pos = i;
		}
	}
	L.data[pos] = L.data[L.length - 1];		//�������������if�У������Сֵ�պ����ڱ�β����Ҫִ�ж�Σ��˷����ܣ�
	L.length--;
	
	return true;
}

/******************************************************************
* ˳��������
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
* ˳���İ�ֵɾ��
* ��k��¼˳����в�����x��Ԫ�ظ�����ɨ��ʱ��������x��Ԫ���ƶ����±�k��λ��
* ��һ�ַ�������k��¼˳����е���x��Ԫ�ظ�������ɨ���ͳ�ƣ�����������x��Ԫ��ǰ��k��λ��
* ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(1)
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
* ɾ������˳�����ֵΪs-t������Ԫ��(s<t);
* ��Ϊ��������ʿ����ҵ���һ��Ҫɾ����Ԫ�أ����ҵ����һ��Ҫɾ����Ԫ�أ�
* �ٽ����һ��Ҫɾ����Ԫ��ǰ�Ƽ���;
******************************************************************/
bool Delete_SqList_From_s_to_t1(SqList& L, ElemType s, ElemType t) {
	int i, j;
	if (s >= t || !L.length)
		return false;
	for (i = 0; i < L.length && L.data[i] < s; i++);	//�ҵ���һ�����ڵ���s��ֵ
	if (i > L.length)
		return false;		//����ֵ��С��s������
	for (j = i; j < L.length && L.data[j] <= t; j++);	//�ҵ���һ������t��ֵ
	for (; j < L.length; i++, j++)
		L.data[i] = L.data[j];
	L.length = i;

	return true;
}

/******************************************************************
* ���ܣ�ɾ��˳�����ֵΪs-t������Ԫ��(����s��t����s<t);
* ��������ǰ���ɨ�裬��k��¼����������ֵ�ĸ��������������������ֵǰ��kλ
******************************************************************/
bool Delete_SqList_From_s_to_t2(SqList& L, ElemType s, ElemType t) {
	int i=0,k = 0;
	if (s >= t || !L.length)
		return false;
	while (i < L.length) {
		if (L.data[i] >= s && L.data[i] <= t) {	//ͳ�Ʒ���Ҫ���ֵ�ĸ���
			k++;
		}
		else {
			L.data[i - k] = L.data[i];			//����ǰֵǰ��kλ
			i++;
		}
	}
	L.length -= k;

	return true;
}

/******************************************************************
* ���ܣ�������˳�����ɾ���ظ���Ԫ��;
* ��������ʼʱ����һ��Ԫ����Ϊ���ظ��������֮��һ���жϺ����Ԫ���Ƿ���ǰ����ظ����������һ��Ԫ����ͬ��
* ����ͬ�����������жϣ�����ͬ�������ǰ��ķ��ظ����������ֱ���жϵ���βΪֹ��
******************************************************************/
bool Delete_SqList_Same(SqList& L) {
	int i, j;
	if (!L.length)
		return false;
	for (i = 0, j = 1; j < L.length; j++)	//i�洢��һ������ͬ��Ԫ�أ�j��Ϊ����ָ��
		if (L.data[i] != L.data[j])
			L.data[++i] = L.data[j];
	L.length = i + 1;

	return true;
}

/******************************************************************
* ���ܣ�����������˳���ϲ�Ϊһ��������˳��������ظ�˳���;
* ��������˳��ȡ�������б�ͷ��С�Ľ������µ�˳����С�Ȼ���ĸ�����ʣ�࣬�����µĲ��ּ��뵽�±�ĺ��档
******************************************************************/
bool Merge_SqList(SqList A, SqList B, SqList &C) {
	if (A.length + B.length > C.length)
		return false;
	int i = 0, j = 0, k = 0;
	while (i < A.length && j < B.length) {	//ѭ���������Ƚϣ�С�ߴ�������
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