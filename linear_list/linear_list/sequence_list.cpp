#include "sequence_list.h"
#include <iostream>

/******************************************************************
* T1
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
* T2
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
* T3
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
* T4
* 删除有序顺序表中值为s-t的所有元素(s<t);
* 因为是有序表，故可先找到第一个要删除的元素，再找到最后一个要删除的元素，
* 再将最后一个要删除的元素后的元素前移即可;
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
* T5
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
* T6
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
* T7
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

/******************************************************************
* T8
* 功能：将依次A中存放的两个线性表(a1...am),(b1...bn)位置互换，即将(b1...bn)放到(a1...am)的前面;
* 方法：先将整体原地逆置得到(bn...b1,am...a1)，然后再分别将前n个元素、后m个元素原地逆置。
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
	//数组A[m+n]中，从0~m-1存放线性表a,从m~m+n-1存放线性表b，算法将这两个表的位置互换。
	Reverse_SqList(A, 0, m + n - 1, arraySize);
	Reverse_SqList(A, 0, n - 1, arraySize);
	Reverse_SqList(A, n, m + n - 1, arraySize);
}

/******************************************************************
* T9
* 功能：从递增的顺序表中找到值为x的元素，并将其与后继元素交换，若找不到，则将其按顺序插入到表中;
* 方法：使用二分查找来查找值为x的元素，若找到则交换，未找到则插入。
******************************************************************/
void SerchExchangeInsert_SqList(ElemType A[], int n, ElemType x) {
	int low = 0, high = n - 1, mid = 0,i=0;
	ElemType temp;
	while (low <= high) {
		mid = (low + high) / 2;	//找中间位置
		if (A[mid] == x)		//找到x，退出循环
			break;
		else if(A[mid] < x)		//比x小，到mid右半部分去找
			low = mid + 1;
		else
			high = mid - 1;		//比x大，到mid左半部分去找
	}
	//只能是以下两个if语句中的情况，要么找到了，要么没找到
	if (A[mid] == x && mid != n - 1) {	//如果是最后一个元素与x相等，则没有必要执行交换动作
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
* 功能：将存有n个整数的一维数组R中保存的序列循环左移p(0<p<n)位,即(X0,X1...Xp,Xp+1...Xn-1)变换为(Xp,Xp+1..Xn-1...X0,X1...Xp-1);
* 方法：可将该问题视为把数组ab转换成数组ba(a代表数组的前p个元素，b代表数组中余下的n-p个元素)。
* 时间复杂度的计算：三个Reverse函数的时间复杂度分别为：O(p/2),O((n-p)/2),O(n/2)，故该方法的时间复杂度为O(n),空间复杂度为O(1)。
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
* 功能：找两个等长升序序列A，B的中位数
* 方法：设A，B中位数分别为a,b。
******************************************************************/
ElemType Median_Search_SqList(ElemType A[], ElemType B[], int n) {
	int s1 = 0, d1 = n - 1, m1, s2 = 0, d2 = n - 1, m2;	//分别表示序列A,B的首位数、末位数和中位数
	while (s1 != d1 || s2 != d2) {
		m1 = (s1 + d1) / 2;
		m2 = (s2 + d2) / 2;
		if (A[m1] == B[m2])		//若a=b
			return A[m1];
		if (A[m1] < B[m2]) {	//若a<b，舍弃A中较小的一半，舍弃B中较大的一半，舍弃长度相等
			if ((s1 + d1) % 2 == 0) {	//若元素个数为奇数
				s1 = m1;
				d2 = m2;
			}
			else {
				s1 = m1 + 1;
				d2 = m2;
			}
		}
		else {					//若a>b，舍弃A中较大的一半，舍弃B中较小的一半，舍弃长度相等
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
* 功能：找出一位数组中存放n个元素的主元素。其中，主元素的个数m>n/2。
* 方法：若存在主元素，则两两配对消去后剩下的那个为主元素；再重新扫描，若m>n/2,则确定。
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
			else {				//更换主元素，重新计数
				temp = A[i];
				count = 1;
			}
		}
	}
	if (count > 0) {			//再次扫描统计确认是否为主元素
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
* 功能：找出含n个整数的数组中的最小正整数x。
* 方法：x的范围为[1,n+1],可用一个大小为n+2的数组B(下标为0的不用)来记录出
* 现的整数并置为1，最后扫描B，找到第一个为0的元素下标。
******************************************************************/
int FindMissMin_SqList(int A[], int n) {
	int i, * B;
	B = (int*)malloc(sizeof(int) * (n + 2));
	for (i = 1; i < n + 2; i++)
		B[i] = 0;			//初始化B为０

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
* 功能：找出正整数三元组的最小距离。
* 方法：先假设一个非常大的最小距离D，固定三个数中的最大数来寻找与该数最接近的数使得距离最小。
******************************************************************/
int abs_(int a) {			//计算绝对值
	return a < 0 ? -a : a;
}
bool xls_min(int a, int b, int c) {	//a是否为三个数中的最小值
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