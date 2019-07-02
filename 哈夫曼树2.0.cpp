// DataStructure HuffmanTree.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// Huffman树1.0 实现最小堆拼接形成链式树
// 2.0修改了pop的循环结束条件 不再依赖把权重定为一个很大的值

#include "pch.h"
#include <iostream>
using namespace std;

const static int max = 100;

template <typename T>
class bond
{
public:
	T data;
	int weight = 0;
	bond<T> *left = NULL;
	bond<T> *right = NULL;
};

template <typename T>
class huffman
{
public:
	int top = 0;
	bond<T> *root = NULL;
	bond<T> array[max];											//最小堆暂时存储haffman树的节点
	huffman() { array[0].weight = -1; }							//把最小堆的顶部节点的weight置为一个较小值
	void insert_heap(T da, int we);								//插入最小堆并保持最小堆的结构
	bond<T> * insert_haff(int we, bond<T> *ls, bond<T> *rs);	//插入一个节点保持最小堆结构
	int heap_sort();											//从top位置排序保持最小堆
	void swap(bond<T> *p1, bond<T> *p2);						//交换堆中两个元素
	int pop_heap();												//从最小堆中弹出一个节点返回weight权重
	void print_array();											//输出最小堆
	int huffmanazation();										//把数据结构变为haffman树
	void print_huffman(bond<T> *p);
};
template <typename T>
void huffman<T>::insert_heap(T da, int we)
{
	array[++top].data = da;
	array[top].weight = we;
	heap_sort();
}
template <typename T>
int huffman<T>::heap_sort()
{
	int i = top;
	for (; array[i].weight < array[i / 2].weight; i /= 2)
	{
		swap(&array[i], &array[i / 2]);
	}
	return i;
}
template <typename T>
void huffman<T>::swap(bond<T> *p1, bond<T> *p2)
{
	bond<T> *pl = p1->left;
	bond<T> *pr = p1->right;
	T da= p1->data; int we = p1->weight;
	p1->data = p2->data;
	p1->weight = p2->weight;
	p1->left = p2->left;
	p1->right = p2->right;
	p2->data = da; p2->weight = we;
	p2->left = pl; p2->right = pr;
}
template <typename T>
int huffman<T>::pop_heap()
{
	int we = array[1].weight;
	swap(&array[1], &array[top]);
	array[top].weight = 0;
	array[top].left = NULL;
	array[top].right = NULL;
	top--;
	int i = 1;
	int temp = 0;
	while (2 * i < top)
	{
		if (array[i].weight <= array[2 * i].weight
			&&array[i].weight <= array[2 * i + 1].weight)
			break;
		else
		{
			if (array[2 * i].weight < array[2 * i + 1].weight)
				temp = 2 * i;
			else temp = 2 * i + 1;
			swap(&array[i], &array[temp]);
			i = temp;
		}
	}
	return we;
}
template <typename T>
void huffman<T>::print_array()
{
	for (int i = 1; i <= top; i++)
		cout << &array[i] << '\t' << array[i].data
		<< '\t' << array[i].weight << endl;
}
template <typename T>
int huffman<T>::huffmanazation()
{
	for (int i = top - 1; i; i--)
	{
		bond<T> *ls = new bond<T>;
		bond<T> *rs = new bond<T>;
		ls->data = array[1].data;
		ls->left = array[1].left;
		ls->right = array[1].right;
		ls->weight = pop_heap();
		rs->data = array[1].data;
		rs->left = array[1].left;
		rs->right = array[1].right;
		rs->weight = pop_heap();
		root = insert_haff(ls->weight + rs->weight, ls, rs);
	}
	return top;
}
template <typename T>
bond<T> *huffman<T>::insert_haff(int we, bond<T> *ls, bond<T> *rs)
{
	array[++top].weight = we;
	array[top].left = ls;
	array[top].right = rs;
	return &array[heap_sort()];
}
template <typename T>
void huffman<T>::print_huffman(bond<T> *s)
{
	if (s)
	{
		if (s->left == NULL && s->right == NULL)
			cout << s << '\t' << s->weight << '\t' << s->data << endl;
		else
		cout << s << '\t' << s->weight << endl;
		print_huffman(s->left);
		print_huffman(s->right);
	}
}

int main()
{
	huffman<int> tr;
	for (int i = 1; i < 11; i++) tr.insert_heap(i, i);
	tr.print_array();
	cout << tr.pop_heap() << endl;
	cout << "tr.print_array();" << endl;
	tr.print_array();
	cout << "f************ck;" << endl;
	tr.huffmanazation();
	tr.print_huffman(tr.root);

	return 0;
}

