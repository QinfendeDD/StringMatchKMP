//�ַ���ƥ��BF�㷨��KMP�㷨 @kylin
#ifndef __STRING_MATCH_H__
#define __STRING_MATCH_H__

/**
* �ַ���ƥ��BF�㷨
* ʵ��1
* @param strSrc   Դ�ַ���
* @param strDest  ��ƥ��ģʽ�ַ���
* @param pos	  ���ҿ�ʼλ��
*
* @return ƥ��ɹ����ؿ�ʼ������ʧ�ܷ���-1
*/
int StringMatchBF(char*strSrc, char*strDest, int pos);

/**
* �ַ���ƥ��BF�㷨
* ʵ��2
* @param s			Դ�ַ���
* @param t			��ƥ��ģʽ�ַ���
* @param index		���ҿ�ʼλ��
*
* @return ƥ��ɹ����ؿ�ʼ������ʧ�ܷ���-1
*/
int index_bf(char *s, char *t, int index);


//BBC ABCDAB ABCAABCDABDE
//	  ABCDABD

/**
* ��ȡģʽ��next����
* ��ģʽ���Ƚ�iλ���ַ�ʱ��ƥ�䣬1-(i-1)���е�һ���ַ����ֵ�λ�� �洢��next[i]��
*-1��ʾ������
* @param pattern			ģʽ��
* @param next				next����
* @param n					�����С
*
* @warning no 
*/
void next_1(char pattern[], int next[], int n);

/**
* �ַ���ƥ��BF�㷨����next
* @param s			Դ�ַ���
* @param t			��ƥ��ģʽ�ַ���
* @param n			next����
* @param size		����ʹ��Ĵ�С
* @param index		���ҿ�ʼλ��
*
* @return ƥ��ɹ����ؿ�ʼ������ʧ�ܷ���-1
*/
int index_bf_1(char *s, char *t, int *n, int size, int index);

//ABCDABDABCD
/**
* ��ȡģʽ��next����
* ��ģʽ���Ƚ�iλ���ַ�ʱ��ƥ�䣬��1-(i-1)���е�һ���ַ����ֵ�λ�ÿ�ʼ��i-1�ַ���������ȵ��ַ��� �洢��next[i]��
* 0��ʾû��
* @param pattern			ģʽ��
* @param next				next����
* @param n					�����С
*
* @warning no
*/
void next_2(char pattern[], int next[], int n);

/**
* �ַ���ƥ��BF�㷨����next
* @param s			Դ�ַ���
* @param t			��ƥ��ģʽ�ַ���
* @param n			next����
* @param size		����ʹ��Ĵ�С
* @param index		���ҿ�ʼλ��
*
* @return ƥ��ɹ����ؿ�ʼ������ʧ�ܷ���-1
*/
int index_bf_2(char *s, char *t, int *n, int size, int index);

//AAAAAABBAAAABBAA
/**
* ��ȡģʽ��next����
* ��ģʽ���Ƚ�iλ���ַ�ʱ��ƥ�䣬��1-(i-1)���е�һ���ַ����ֵ�λ�ÿ�ʼ��i-1�ַ���������ȵ��ַ��� �洢��next[i]��
* 0��ʾû��
* @param pattern			ģʽ��
* @param next				next����
* @param n					�����С
*
* @warning no
*/
void next_3(char pattern[], int next[], int n);

#pragma region �����˲��ͷ���
//ǳ̸�ַ���ƥ���㷨��BF�㷨��KMP�㷨
//�ο���http://blog.csdn.net/jiajiayouba/article/details/9178789
/*
*KMP�㷨֮next�������
*next���鶨�壺��ģʽƥ�䴮Tʧ���ʱ��next�����Ӧ��Ԫ��֪��Ӧ����T�����ĸ�Ԫ�ؽ�����һ�ֵ�ƥ�䡣
*/
//char p[] =     "AACDAADABCD";
void get_next(char *t, int *next);

/*
���ַ���s�У����±�index��ʼ�����Ƿ����ַ���t.����У�����t��s�еĿ�ʼλ�ã����û�У�����-1��
(ʹ��KMP�㷨ʵ��)
ע���ַ�����s��t�У����ٱ����ַ������ȡ�
//ԭ���и��㷨next���鶨�����,int next[strlen(t)] �������޸�
*/
int index_kmp(char *s, char *t, int*next, int index);

#pragma endregion

//char p[] =     "AACDAADABCD";
void makeNext(const char P[], int next[], int size);
#endif




