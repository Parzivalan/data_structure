#include "sequence_list.h"
#include <iostream>

/******************************************************************
* T1
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
* T2
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
* T3
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
* T4
* ɾ������˳�����ֵΪs-t������Ԫ��(s<t);
* ��Ϊ��������ʿ����ҵ���һ��Ҫɾ����Ԫ�أ����ҵ����һ��Ҫɾ����Ԫ�أ�
* �ٽ����һ��Ҫɾ����Ԫ�غ��Ԫ��ǰ�Ƽ���;
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
* T5
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
* T6
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
* T7
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

/******************************************************************
* T8
* ���ܣ�������A�д�ŵ��������Ա�(a1...am),(b1...bn)λ�û���������(b1...bn)�ŵ�(a1...am)��ǰ��;
* �������Ƚ�����ԭ�����õõ�(bn...b1,am...a1)��Ȼ���ٷֱ�ǰn��Ԫ�ء���m��Ԫ��ԭ�����á�
******************************************************************/
bool Reverse_SqList(ElemType A[], int left, int right, int arraySize) {
	if (left >= right || right >= arraySize)
		return false;
	int mid = (left + right) / 2;
	for (int i = 0; i <= mid - left; i++) {
		ElemType temp = A[left + i];
		A[left + i] = A[right - i];
		A[right - i] = temp;
	}
	return true;
}
void Exchange_SqList(ElemType A[], int m, int n, int arraySize) {
	//����A[m+n]�У���0~m-1������Ա�a,��m~m+n-1������Ա�b���㷨�����������λ�û�����
	Reverse_SqList(A, 0, m + n - 1, arraySize);
	Reverse_SqList(A, 0, n - 1, arraySize);
	Reverse_SqList(A, n, m + n - 1, arraySize);
}

/******************************************************************
* T9
* ���ܣ��ӵ�����˳������ҵ�ֵΪx��Ԫ�أ�����������Ԫ�ؽ��������Ҳ��������䰴˳����뵽����;
* ������ʹ�ö��ֲ���������ֵΪx��Ԫ�أ����ҵ��򽻻���δ�ҵ�����롣
******************************************************************/
void SerchExchangeInsert_SqList(ElemType A[], int n, ElemType x) {
	int low = 0, high = n - 1, mid = 0,i=0;
	ElemType temp;
	while (low <= high) {
		mid = (low + high) / 2;	//���м�λ��
		if (A[mid] == x)		//�ҵ�x���˳�ѭ��
			break;
		else if(A[mid] < x)		//��xС����mid�Ұ벿��ȥ��
			low = mid + 1;
		else
			high = mid - 1;		//��x�󣬵�mid��벿��ȥ��
	}
	//ֻ������������if����е������Ҫô�ҵ��ˣ�Ҫôû�ҵ�
	if (A[mid] == x && mid != n - 1) {	//��������һ��Ԫ����x��ȣ���û�б�Ҫִ�н�������
		temp = A[mid];
		A[mid] = A[mid + 1];
		A[mid + 1] = temp;
	}
	if (low > high) {
		for (i = n - 1; i > high; i--)
			A[i + 1] = A[i];
		A[i + 1] = x;
	}
}

/******************************************************************
* T10
* ���ܣ�������n��������һά����R�б��������ѭ������p(0<p<n)λ,��(X0,X1...Xp,Xp+1...Xn-1)�任Ϊ(Xp,Xp+1..Xn-1...X0,X1...Xp-1);
* �������ɽ���������Ϊ������abת��������ba(a���������ǰp��Ԫ�أ�b�������������µ�n-p��Ԫ��)��
* ʱ�临�Ӷȵļ��㣺����Reverse������ʱ�临�Ӷȷֱ�Ϊ��O(p/2),O((n-p)/2),O(n/2)���ʸ÷�����ʱ�临�Ӷ�ΪO(n),�ռ临�Ӷ�ΪO(1)��
******************************************************************/
void Reverse_SqList2(ElemType R[], int from, int to) {
	int i, temp;
	for (i = 0; i < (from + to - 1) / 2; i++) {
		temp = R[from+i];
		R[from+i] = R[to - i];
		R[to - i] = temp;
	}
}
void Converse_SqList(ElemType R[], int n, int p) {
	Reverse_SqList2(R, 0, p - 1);
	Reverse_SqList2(R, p, n - 1);
	Reverse_SqList2(R, 0, n - 1);
}

/******************************************************************
* T11
* ���ܣ��������ȳ���������A��B����λ��
* ��������A��B��λ���ֱ�Ϊa,b��
******************************************************************/
ElemType Median_Search_SqList(ElemType A[], ElemType B[], int n) {
	int s1 = 0, d1 = n - 1, m1, s2 = 0, d2 = n - 1, m2;	//�ֱ��ʾ����A,B����λ����ĩλ������λ��
	while (s1 != d1 || s2 != d2) {
		m1 = (s1 + d1) / 2;
		m2 = (s2 + d2) / 2;
		if (A[m1] == B[m2])		//��a=b
			return A[m1];
		if (A[m1] < B[m2]) {	//��a<b������A�н�С��һ�룬����B�нϴ��һ�룬�����������
			if ((s1 + d1) % 2 == 0) {	//��Ԫ�ظ���Ϊ����
				s1 = m1;
				d2 = m2;
			}
			else {
				s1 = m1 + 1;
				d2 = m2;
			}
		}
		else {					//��a>b������A�нϴ��һ�룬����B�н�С��һ�룬�����������
			if ((s1 + d1) % 2 == 0) {
				d1 = m1;
				s2 = m2;
			}
			else {
				d1 = m1;
				s2 = m2 + 1;
			}
		}
	}

	return A[s2] < B[s2] ? A[s2] : B[s2];
}

/******************************************************************
* T12
* ���ܣ��ҳ�һλ�����д��n��Ԫ�ص���Ԫ�ء����У���Ԫ�صĸ���m>n/2��
* ��������������Ԫ�أ������������ȥ��ʣ�µ��Ǹ�Ϊ��Ԫ�أ�������ɨ�裬��m>n/2,��ȷ����
******************************************************************/
ElemType Majority_SqList(ElemType A[], int n) {
	int count=1;
	ElemType temp = A[0];
	for (int i = 1; i < n; i++) {
		if (temp == A[i]) {
			count++;
		}
		else {
			if(count > 0)
				count--;
			else {				//������Ԫ�أ����¼���
				temp = A[i];
				count = 1;
			}
		}
	}
	if (count > 0) {			//�ٴ�ɨ��ͳ��ȷ���Ƿ�Ϊ��Ԫ��
		for (int i = 0; i < n; i++) {
			count = 0;
			if (temp == A[i])
				count++;
		}
		return count > n / 2 ? temp : -1;
	}
}

/******************************************************************
* T13
* ���ܣ��ҳ���n�������������е���С������x��
* ������x�ķ�ΧΪ[1,n+1],����һ����СΪn+2������B(�±�Ϊ0�Ĳ���)����¼��
* �ֵ���������Ϊ1�����ɨ��B���ҵ���һ��Ϊ0��Ԫ���±ꡣ
******************************************************************/
int FindMissMin_SqList(int A[], int n) {
	int i, * B;
	B = (int*)malloc(sizeof(int) * (n + 2));
	for (i = 1; i < n + 2; i++)
		B[i] = 0;			//��ʼ��BΪ��

	for (i = 0; i < n; i++) { 
		if (A[i] > 0 && A[i] <= n + 1) {
			B[A[i]] = 1;
		}
	}
	for (i = 1; i < n + 2; i++) {
		if (B[i] == 0)
			break;
	}

	return i;
}

/******************************************************************
* T14
* ���ܣ��ҳ���������Ԫ�����С���롣
* �������ȼ���һ���ǳ������С����D���̶��������е��������Ѱ���������ӽ�����ʹ�þ�����С��
******************************************************************/
int abs_(int a) {			//�������ֵ
	return a < 0 ? -a : a;
}
bool xls_min(int a, int b, int c) {	//a�Ƿ�Ϊ�������е���Сֵ
	return a <= b && a <= c ? true : false;
}
int FindMinOfTrip_SqList(int A[], int n, int B[], int m, int C[], int p) {
	int i = 0, j = 0, k = 0, D_min = INT_MAX, D;
	while (i < n && j < m && k < p) {
		if (A[i] <= 0) i++;
		if (B[i] <= 0) j++;
		if (C[i] <= 0) k++;

		D = abs_(A[i] - B[j]) + abs_(B[j] - C[k]) + abs_(A[i] - C[k]);
		D_min = D < D_min ? D : D_min;

		if (xls_min(A[i], B[j], C[k])) i++;
		else if (xls_min(B[j], A[i], C[k])) j++;
		else k++;
	}

	return D_min;
}