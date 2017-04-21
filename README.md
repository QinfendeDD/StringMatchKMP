字符串匹配算法理解（从BF算法到KMP算法）
===========
* 暴风(Brute Force)算法是普通的模式匹配算法，BF算法的思想就是将目标串S的第一个字符与模式串T的第一个字符进行匹配，若相等，则继续比较S的第二个字符和 T的第二个字符；若不相等，则比较S的第二个字符和T的第一个字符，依次比较下去，直到得出最后的匹配结果。BF算法是一种蛮力算法
* KMP算法是一种改进的字符串匹配算法，由D.E.Knuth，J.H.Morris和V.R.Pratt同时发现，因此人们称它为克努特——莫里斯——普拉特操作（简称KMP算法）。KMP算法的关键是利用匹配失败后的信息，尽量减少模式串与主串的匹配次数以达到快速匹配的目的。具体实现就是实现一个next()函数，函数本身包含了模式串的局部匹配信息。时间复杂度O(m+n)。
****** 

KMP算法是对BF算法进行改进的一种算法，但是如果直接去看KMP算法的话会很难理解（至少我看了几遍没看懂:smile:），我尝试着从BF算法优化过程去理解KMP算法，就会轻松很多。让我们一起开始吧。

* 先看看BF算法的匹配过程，目标串S["**BBCDABCDAACDAAAABCDAADE**"],模式串T["**ABCDAAD**"]


![][bf]

* BF算法代码
```cpp
int index_bf(char *s, char *t)
{
	int i = 0;
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
```

在图中，第5次匹配时一直匹配到字符'D'才失败，前面6个字符匹配成功，进行第6次匹配时，从目标串S加1字符与模式串T第1个字符重头进行匹配，这样效率太低了。
我们知道一次正确的匹配肯定是在目标串S中以模式串T首字符'A'开始的（如第5次和第9次匹配），因此*如果我们在每次匹配的过程中能够在目标串S中找到下一个模式串T首字符'A'位置的话，就可以直接从当前比较位置跳到下一个'A'位置进行继续匹配（如图中第5次匹配可以直接跳到第9次匹配），那么就可以省去很多不必要的匹配了。* 我们以此思路来进行第一次优化，我们观察第5次匹配过程，在'D'字符匹配失败时，前面匹配过的串"ABCDAA"，在目标串和模式串中是一样的，我们可以通过模式串T中第2个'A'的位置，来计算出目标串第2个'A'的位置，这样我们就可以直接跳到第9次比较了。

### BF算法第一次优化
在一次匹配中，目标串S从i位置与模式串T0（0为开始位置）位置开始重头匹配，在T的j位置失败，如果我们能知道在j位置失败时，T中已经匹配的串中下一个首字符出现的位置话，就可以直接跳到下一次首字符位置继续匹配啦。现在对模式串T设计一个数组 **int next[]**,数组长度与模式串T长度一致，数组j下标处存储着模式串T的0到j-1子串第2次出现首字母位置（第一次就是首字母0处）。上图第5次匹配，在模式串T j=6 处失败，模式串T 0到j-1=6的子串（"ABCDAA"）中第2次出现'A'的位置为4，子串中没有再次出现首字符表示-1。

模式串T和next数组

 0 |1 |2 |3 |4 |5 |6 |
:----: | :----:|:----:|:----:|:----:|:----:|:----:|
A  | B |C |D |A |A |D |
-1  | -1 |-1 |-1 |-1 |4 |4 |

* next数组算法
```cpp
void next_1(char pattern[], int next[], int n)
{
	int i = 0; //首字符位置
	int j = 1; //匹配失败的位置

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
}
```
* 利用该next数组对BF算法进行第1次优化
```cpp
int index_bf_1(char *s, char *t, int* n, int size)
{
	int i = 0;
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
```
_在一次匹配失败的时候，可以通过next数组对目标串跳过一些比较,下图_

![][bf1]

### BF算法第二次优化
经过第一次优化后，我们从原来的第5次匹配跳到第9次匹配，我们发现第10次匹配也是在第5次匹配的子串中进行，能不能从第5次直接跳到第10次匹配呢？


--------------------------------
[bf]:/StringMatch/img/BF.png "BF算法图示"
[bf1]:/StringMatch/img/BF_1.png "BF算法图示"

