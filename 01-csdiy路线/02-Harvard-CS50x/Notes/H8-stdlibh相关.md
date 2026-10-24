
此标头是程序支持工具库的一部分，特别是，它提供用于程序终止、内存管理、字符串转换、随机数生成的函数。此标头还提供了一些算法。

**宏**

- NULL
- EXIT_SUCCESS
- EXIT_FAILURE
- RAND_MAX   至少为32767

**常用函数**

- 内存管理
	- malloc 分配未初始化内存
	- calloc 分配并自动清零内存
	- realloc 调整已分配内存的大小
	- free 释放内存
- 字符串转换
	- atoi 字符串转int
	- atof 字符串转double
	- strtol 字符串安全转long
	- strtod 字符串安全转double
- 随机数生成
	- rand 伪随机
	- srand 设置随机数种子
- 排序与搜索
	- qsort 快速排序
	- bsearch 二分查找
- 整数绝对值
	- abs
	- labs
	- llabs
- 程序控制
	- exit 立刻终止


### 内存管理

```c
#include <stdlib.h>

int *p = malloc(4 * sizeof(int));
if (p == NULL){
	// 检查分配失败后的操作
}

int *q = calloc(4, sizeof(int));

int *tmp = realloc(p, 8 * sizeof(int));
if (tmp != NULL){
	p = tmp;
}

free(p);
free(q);
p = NULL;
q = NULL;
```

malloc 和 calloc 参数的单位是字节，realloc 的参数是原内存首地址和新内存的字节数

calloc 会强制对所有内存清空，在往内存中写入数据的瞬间可能会带来额外性能开销，但是如果本身就需要全 0 内存则优先使用 calloc

realloc 会自动拷贝内容

### 字符串转换

```c
int a = atoi("123abc"); // 123
int b = atoi("abc"); // 0

char *end;
long val = strtol("123abc", &end, 10); // val = 123, end 指向 "abc"
```

atoi 在失败时返回 0，遇到溢出也是 0，读到 0 也是 0

strtol 的参数分别是 待转换字符串，停下的地址，转换到几进制的数：
- 没事可以写 10
- 有上限和下限：从 2 到 36 = 10 + 26
- 写的是 0：自动检测进制到16，8，10进制之一
- 若为 16，则会自动跳过前缀 0x 输出后面的内容
- 2 进制和 8 进制前缀无法被自动跳过

### 绝对值

```c
int a = abs(-5); // 5
long b = labs(-500L); // 500L
long long c = llabs(-500LL) // 500LL

int d = abs(-3.14); // 3 (更有可能是未定义行为，不要这么干！)
```

碰到不是整数的，向 0 截断再取绝对值

### 程序控制

```c
if (/* 发生致命错误 */){
	exit(EXIT_FAILURE); // 即 exit(1);
}
return 0;
```

### 随机数

```c
int r = rand(); // 0 到 RAND_MAX (通常为 32767) 之间的随机数
int x = rand() % 100; // [0, 99] 之间的随机数
int y = a + rand() % (b - a + 1); // [a, b] 之间的随机数
```

事实上严格来讲上面那一段是不严谨的，RAND_MAX 的值导致了0 到 67 的概率略大于 68 到 99，一种办法是直接丢掉重新尝试生成

在 MSVC 编译器下，RAND_MAX 的值为 32767

在 GCC 编译器下，RAND_MAX 的值为 2147483647

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 5; i++){
		int random_value = rand() % 100 + 1;
		printf("%d ", random_value);
	}
	printf("\n");
	return 0;
}
```

使用的时间戳以秒为单位

如果不调用 srand，那么每次运行程序的 rand 函数均使用默认种子 1，这意味着每次运行生成的随机数序列都一样

### 排序与查找

```c
int cmp(const void *a, const void *b){
	int x = *(const int *)a;
	int y = *(const int *)b;
	if (x < y){
		return -1;
	}
	if (x > y){
		return 1;
	}
	return 0;
}

int cmp2(const void *a, const void *b){
	int x = *(const int *)a;
	int y = *(const int *)b;
	return (x > y) - (x < y);
}

int cmp3(const void *a, const void *b) {
    return (*(const int *)a > *(const int *)b) - (*(const int *)a < *(const int *)b);
}

int arr[5] = {3, 1, 4, 1, 5};
qsort(arr, 5, sizeof(int), cmp);

int target = 4;
int *result = (int *)bsearch(&target, arr, 5, sizeof(int), cmp);
```

#### qsort

qsort 的参数为：数组名，元素个数，每个元素的类型大小，比较函数指针，其中比较函数的参数是两个指针

效果为对 arr 指向的数组以升序排序，直接对原数组操作得到该数组，返回值为 void

#### bsearch

bsearch 的参数为：目标值，数组名，元素个数，每个元素的类型大小，比较函数指针

使用时不要忘记转类型

返回值为目标值对应的地址，或者是 NULL

cmp 的返回值只要求 正负 0 的区别，使用 1 和 -1 相当直观

以上例子均为 int，那如果是别的类型？

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int id;
	int score;
} Student;

int compareStudent(const void *a, const void *b){
	const Student *stu_a = (const Student *)a;
	const Student *stu_b = (const Student *)b;
	if (stu_a->id < stu_b->id){
		return -1;
	}
	else if (stu_a->id > stu_b->id){
		return 1;
	}
	else{
		if (stu_a->score > stu_b->score){
			return -1;
		}
		else if (stu_a->score < stu_b->score){
			return 1;
		}
		return 0;
	}
}

int main(){
	Student students[4] = {
		{1002, 85},
		{1001, 90},
		{1003, 95},
		{1001, 80}
	};
	int n = 4;
	
	qsort(students, n, sizeof(Student), compareStudent);
	for (int i = 0; i < n; i++){
		printf("ID: %d, Score: %d\n", students[i].id, students[i].score);
	}
	
	Student target;
	target.id = 1002;
	target.score = 0;
	Student *found = (Student *)bsearch(&target, students, n, sizeof(Student), compareStudent);
	if (found != NULL){
		printf("ID: %d, Score: %d\n", found->id, found->score);
	}
	else{
		printf("NotFound\n");
	}
}
```

> [!WARNING] bsearch 遇到相同的 key 时应该返回哪一个
> - **未指定**

qsort 的时间复杂度是 $O(n\ log\ n)$

这个 bsearch 看起来很像手搓的二分查找，但是不常用的原因如下：

- 相同 key 查找不稳定，没有偏左或偏右的倾向
- 性能黑洞



**更深的等到 cpp 再看吧，后面感觉是被 C 语言束缚住了**