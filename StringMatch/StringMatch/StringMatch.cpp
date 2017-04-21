#include "stdafx.h"

#pragma region ʵ�ִ���

int StringMatchBF(char*strSrc, char*strDest, int pos)
{
	if (strSrc == NULL || strDest == NULL)
	{
		return -1;
	}

	if (strSrc + pos == NULL || *(strSrc + pos) == '\0')
	{
		return -1;
	}

	strSrc = strSrc + pos;

	char* tSrc = strSrc;
	char* tDest = strDest;

	int j = pos;

	while (*strSrc != '\0')
	{
		while (*tSrc == *tDest)
		{
			tDest++;
			tSrc++;
			if (*tDest == '\0')
			{
				return j;
			}
		}

		strSrc++;
		tSrc = strSrc;
		tDest = strDest;
		j++;
	}
	return -1;
}

int index_bf(char *s, char *t, int index)
{
	int i = index;
	int j = 0;
	while (s[i] != '\0')
	{
		while (*(t + j) != '\0' && *(s + i + j) != '\0')
		{
			if (*(t + j) != *(s + i + j))
				break;
			j++;
		}
		if (*(t + j) == '\0')
		{
			return i;
		}
		i++;
		j = 0;
	}
	return -1;
}

//BBC ABCDAB ABCAABCDABDE
//	  ABCDABD

void next_1(char pattern[], int next[], int n)
{
	int i = 0; //���ַ�λ��
	int j = 1; //ƥ��ʧ�ܵ�λ��

	next[0] = -1;
	next[1] = -1;

	j = 2;
	for (; j < n;j++)
	{
		next[j] = -1;
		for (int k = 1; k < j;k++)
		{
			if (pattern[i] == pattern[k])
			{
				next[j] = k;
				break;
			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		printf("%3c", pattern[i]);
	}
	printf("\n");
	for (int i = 0; i < n;i++)
	{
		printf("%3d", next[i]);
	}
	printf("\n");
}

int index_bf_1(char *s, char *t, int* n, int size, int index)
{
	int i = index;
	int j = 0;
	next_1(t, n, size);

	while (s[i] != '\0')
	{
		while (*(t + j) != '\0' && *(s + i + j) != '\0')
		{
			if (*(t + j) != *(s + i + j))
				break;
			j++;
		}
		if (*(t + j) == '\0')
		{
			return i;
		}
		
		if (n[j] == -1)
		{
			i++;
		}
		else
		{
			i += n[j];
		}

		//i++;
		j = 0;
	}
	return -1;
}

//ABCDABDABCD
//AACDAADABCD
//AACDAADABCD
void next_2(char pattern[], int next[], int n)
{
	int i = 0; //���ַ�
	int j = 1; //ƥ��ʧ�ܵ�λ��

	next[0] = 0;
	next[1] = 0;

	j = 2;
	for (; j < n; j++)
	{
		int num = 0;
		for (int k = 1; k < j; k++)
		{
			if (pattern[i] == pattern[k])
			{
				i++;
				num++;
			}
			else
			{
				num = 0;
				i = 0;

				if (pattern[i] == pattern[k])
				{
					i++;
					num++;
				}
			}
		}
		next[j] = num;
		i = 0;
	}

	for (int i = 0; i < n; i++)
	{
		printf("%3c", pattern[i]);
	}
	printf("\n");
	for (int i = 0; i < n; i++)
	{
		printf("%3d", next[i]);
	}
	printf("\n");
}

//AAAAAABBAAAABBAA
//AACDAADABCD
void next_3(char pattern[], int next[], int n)
{
	int i = 0; //���ַ�
	int j = 1; //ƥ��ʧ�ܵ�λ��

	next[0] = 0;
	next[1] = 0;

	j = 2;
	for (; j < n; j++)
	{
		int num = 0;
		i = next[j - 1];
		for (int k = 1+next[j-1]; k < j; k++)
		{
			if (pattern[i] == pattern[k])
			{
				i++;
				num++;
			}
			else
			{
				num = 0;
				i = 0;

				if (pattern[i] == pattern[k])
				{
					i++;
					num++;
				}
			}
		}

		next[j] = num;
		//i = 0;
	}

	for (int i = 0; i < n; i++)
	{
		printf("%3c", pattern[i]);
	}
	printf("\n");
	for (int i = 0; i < n; i++)
	{
		printf("%3d", next[i]);
	}
	printf("\n");
}


//char s[] = "BBC ABCDAB ABCAABCDABDE";
//char p[] =     "ABCDABDABCD";
int index_bf_2(char *s, char *t, int *n, int size, int index)
{
	int i = index;
	int j = 0;
	next_2(t, n, size);

	while (s[i] != '\0')
	{
		while (*(t + j) != '\0' && *(s + i + j) != '\0')
		{
			if (*(t + j) != *(s + i + j))
				break;
			j++;
		}

		if (*(t + j) == '\0')
		{
			return i;
		}

		if (n[j] == 0)
		{
			i += j==0?1:j;
			j = 0;
		}
		else
		{
			i += j - n[j];
			j = n[j];
		}

		//i++;
		//j = 0;
	}
	return -1;
}


/*
KMP�㷨֮next�������
next���鶨�壺��ģʽƥ�䴮Tʧ���ʱ��next�����Ӧ��Ԫ��֪��Ӧ����T�����ĸ�Ԫ�ؽ�����һ�ֵ�ƥ�䡣
*/
//char p[] =     "AACDAADABCD";
void get_next(char *t, int *next)
{
	int i = 0; //Prefix ǰ׺  
	int j = 1; //Postfix ��׺  
	next[0] = 0; //�Զ���ģ�0��1����0��ʼƥ��  
	next[1] = 0;

	while (t[j] != '\0')
	{
		if (t[i] == t[j]) //��ǰ���ַ�ƥ�䣬����ǰ�ƽ�  
		{
			i++;
			j++;
			next[j] = i;
			continue;
		}
		else
		{
			i = next[i]; //ǰ���ַ���ƥ�䣬����ݡ�ע�⣬��ʱ��i��j��ƥ�䣬��ˣ�����next���鶨�壬Ҫ���ݵ�next[i]��ֵ��  
		}
		if (0 == i) //�����ݵ����ַ�ʱ���������д���  
		{
			if (t[i] == t[j])
			{
				next[++j] = ++i;
			}
			else
				next[++j] = i;
		}
	}

	i = 0;
	while (t[i] != '\0')
	{
		printf("%3c", t[i]);
		i++;
	}
	printf("\n");

	i = 0;
	while (t[i] != '\0')
	{
		printf("%3d", next[i]);
		i++;
	}
	printf("\n");
}

/*
���ַ���s�У����±�index��ʼ�����Ƿ����ַ���t.����У�����t��s�еĿ�ʼλ�ã����û�У�����-1��
(ʹ��KMP�㷨ʵ��)
ע���ַ�����s��t�У����ٱ����ַ������ȡ�
*/
int index_kmp(char *s, char *t, int*next, int index)
{
	//int next[strlen(t)]; ԭ���и�д������
	get_next(t, next);
	int i = index, j = 0;
	while (s[i] != '\0' && t[j] != '\0')
	{
		if (s[i] == t[j])
		{
			i++;
			j++;
			continue;
		}
		else
		{
			j = next[j]; //��ģʽƥ�������У���ȡҪ���ݵ��Ľ��  
		}
		if (0 == j) //���������һ���ַ�  
		{
			if (s[i] == t[j])
			{
				i++;
				j++;
			}
			else
			{
				i++;
			}
		}
	}
	if (t[j] == '\0') //��ʾ�ַ���t�У������ַ���ƥ�����  
	{
		return i - strlen(t); //��Ϊi��ƥ����s��t�ַ����Ľ�β����ΪҪ���ص���s��t�Ŀ�ʼ�±꣬��i-strlen(t).  
	}
	else
	{
		return -1;
	}
}


//char p[] =     "AACDAADABCD";
void makeNext(const char P[], int next[], int size)
{
	int q, k;//q:ģ���ַ����±ꣻk:���ǰ��׺����
	int m = strlen(P);//ģ���ַ�������
	next[0] = 0;//ģ���ַ����ĵ�һ���ַ������ǰ��׺����Ϊ0
	for (q = 1, k = 0; q < m; ++q)//forѭ�����ӵڶ����ַ���ʼ�����μ���ÿһ���ַ���Ӧ��nextֵ
	{
		while (k > 0 && P[q] != P[k])//�ݹ�����P[0]������P[q]��������ͬ��ǰ��׺����k
			k = next[k - 1];          //�����û��ϵ������ķ��������whileѭ�������δ���ľ������ڣ�ȷʵ�������  
		if (P[q] == P[k])//�����ȣ���ô�����ͬǰ��׺���ȼ�1
		{
			k++;
		}
		next[q] = k;
	}

	for (int i = 0; i < size; ++i)
	{
		printf("%3c", P[i]);
	}
	printf("\n");
	for (int i = 0; i < size; ++i)
	{
		printf("%3d", next[i]);
	}
	printf("\n");
}


#pragma endregion

int _tmain(int argc, _TCHAR* argv[])
{
	char s[] = "BBC ABCDAB ABCAABCDABDAECDABCDABDABCDAACDAADABCD";
	//char p[] = "ABCDABDABCD";
	char p[] = "AACDAADABCD";
	char p2[] = "ABDABABD";
	int n[11] = {};

	int index = -1;
	index = index_bf(s, p, 0);
	printf("index_bf result:%d\n", index);

	index = index_bf_1(s, p, n, 11, 0);
	printf("index_bf_1 result:%d\n", index);

	index = index_bf_2(s, p, n, 11, 0);
	printf("index_bf_2 result:%d\n", index);

	index = index_kmp(s, p,n, 0);
	printf("index_kmp result:%d\n", index);

	next_2(p, n, 11);
	next_3(p, n, 11);
	get_next(p, n);
	makeNext(p, n, 11);


	getchar();
	return 0;
}

//		������
//		index_bf result : 37
//		A  A  C  D  A  A  D  A  B  C  D
//		- 1 - 1  1  1  1  1  1  1  1  1  1
//		index_bf_1 result : 37
//		A  A  C  D  A  A  D  A  B  C  D
//		0  0  1  0  0  1  2  0  1  0  0
//		index_bf_2 result : 37
//		A  A  C  D  A  A  D  A  B  C  D
//		0  0  1  0  0  1  2  0  1  0  0
//		index_kmp result : 37
//		A  A  C  D  A  A  D  A  B  C  D
//		0  0  1  0  0  1  2  0  1  0  0
//		A  A  C  D  A  A  D  A  B  C  D
//		0  0  1  0  0  1  2  0  1  0  0
//		A  A  C  D  A  A  D  A  B  C  D
//		0  0  1  0  0  1  2  0  1  0  0
//		A  A  C  D  A  A  D  A  B  C  D
//		0  1  0  0  1  2  0  1  0  0  0


