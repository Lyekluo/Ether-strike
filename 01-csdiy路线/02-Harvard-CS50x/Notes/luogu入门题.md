
接下来的代码均使用 C 语言

## 基础语法和输入输出

### B2002 Hello,World! 题解：

```c
#include <stdio.h>
int main(){
	printf("Hello,World!");
} 
```

头文件 `#include <stdio.h>`

程序主函数 `int main(){}`

### H1 <stdio.h> 相关

C语言的标准输入输出库，全称为 Standard Input/Output Header，提供了（不全，只放了感觉像认识的）：

- 函数
	- 格式化输出
		- printf（前往stdout）
		- fprintf（任意 FILE \*）
		- sprintf snprintf（字符串，是否限制长度）
	- 格式化输入
		- scanf（来自stdin）
		- fscanf（任意 FILE \*）
		- sscanf（字符串）
	- 单字符读写
		- getchar（来自stdin）
		- fgetc（任意）
		- ungetc（塞回输入流，成为下一次读取的第一个字符）
		- putchar
		- fputc
	- 字符串读写
		- fgets（读一行，会读完'\n'）
	- 二进制读写
		- fread
		- fwrite
	- 文件操作
		- 打开与关闭
			- fopen
			- freopen（重定向流到指定文件）
			- fclose（记得关）
		- 缓冲控制
			- fflush（刷新）
			- setbuf
			- setvbuf（精细控制）
		- 文件定位（光标）
			- fseek
			- ftell
			- rewind
			- fgetpos（存入 fpos_t）
			- fsetpos（用 fpos_t 恢复）
		- 状态查询
			- feof（判断）
			- ferror（判断）
			- clearerr
			- perror
		- 文件管理
			- remove
			- rename
			- tmpfile
			- tmpnam
- 类型
	- FILE（文件流对象）
	- fpos_t（文件位置）
	- size_t（无符号整数类型，用于表示大小）
- 宏
	- 标准流（FILE \*）
		- stdin
		- stdout
		- stderr
	- 常量
		- NULL（0或 (void*)0，空指针）
		- EOF -1
		- etc.
	- 文件定位起点
		- SEEK\_SET
		- SEEK\_CUR
		- SEEK\_END
	- 缓冲模式
		- \_IOFBF
		- \_IOLBF
		- \_IONBF


### H2 跨行读取的问题

scanf 的大多数格式符如 %d / %s 等均有一个特性：**自动跳过前导空白字符（即空格`' '`、制表符`'\t'`、换行符`'\n'`）**，那么 scanf 可以跨空格和跨行吃数据，而 **%c** 不能，此时需要

```c
scanf(" %c", &c);
```

来跳过所有前导空白

**为什么？在数字和字符串的层面上，空格应当作为分隔而非内容，而对于单个字符来说，空格是有意义的**

如果此时需要从 %d 类切换到 %c 或者 fgets 的时候，需要手动处理 stdin 缓冲区里残留的换行符，例如：

```c
int n;
char c;
scanf("%d", &n);
getchar();
scanf("%c", &c);
```

```c
scanf("%d", &n);
getchar();
fgets(s, sizeof(s), stdin);
```

`getchar();` 起到的作用只是吸收，然后丢弃

或者使用**循环吸收**所有空白

```c
while (getchar() != '\n');
```

如果吸收的不是换行符就下一个（此时换行符已经被吸收）。这种感觉有点像先执行再判定是否成功

fgets 不跳过任何字符，直到吃到一个换行符停止，所以每次 fgets 一行数据之后，都要用：

```c
s[strcspn(s, "\n")] = '\0';
```

来手动去掉换行符。手动去掉之后，再用于输出时就得惦记着手动加换行符

注：fgets 和 getchar 只需要头文件`<stdio.h>`，strcspn 需要`<string.h>`

### H3 变量动作的问题

先有常见变量类型的整理：

#### 基本类型

|         类型         | 大小  |          数值范围          |   占位符格式   |
| :----------------: | :-: | :--------------------: | :-------: |
|        char        |  1  |        -128 127        | %c / %hhd |
|    signed char     |  1  |        -128 127        |   %hhd    |
|   unsigned char    |  1  |         0 255          |   %hhu    |
|       short        |  2  |      -32768 32767      |    %hd    |
|   unsigned short   |  2  |        0 65535         |    %hu    |
|        int         |  4  | -2147483648 2147483647 |    %d     |
|    unsigned int    |  4  |      0 4294967295      |    %u     |
|     long long      |  8  |    - 2^63 2^63 - 1     |   %lld    |
| unsigned long long |  8  |       0 2^64 - 1       |   %llu    |
|       float        |  4  |        十进制6位有效         |    %f     |
|       double       |  8  |        十进制15位有效        |    %lf    |
|    long double     | 12  |        十进制18位有效        |    %Lf    |
|  char * / char[]   |  8  |                        |    %s     |
|       void *       |  8  |                        |    %p     |
|      十六进制 int      |  4  |                        | %#x / %#X |
|      八进制 int       |  4  |                        |    %#o    |
|       size_t       |  8  |                        |    %zu    |

布尔类型（C23前需要加入 stdbool.h）

```c
#include <stdbool.h>
bool flag1 = true;
bool flag2 = false;
```

其底层类型为\_Bool，大小为1。**任何非0的值给bool类型赋值时，都会变成1。**

#### 派生类型

**函数**

```c
int add(int, int);
int add(int a, int b);
int add(int a, int b){
	return a + b;
}

int (*fp)(int, int) = add; // 声明 fp 函数指针，初始化指向函数add
```

>[!HINT] **函数指针**
> - 函数指针的唯一用途是**调用**
> - **函数名 add 在赋值、初始化、传参的表达式中会退化为指向该函数的指针**
> 	- 本质：函数名 add 是函数对应代码段起始地址的符号
> 	- 函数应该将自己的值赋给函数指针 \*fp，而不是赋给某个函数（函数本身没有内存空间）
> 	- sizeof(add) 是未定义行为，函数名也不能进行指针算术
> 	- 带来的特性：函数名随便 \* 和 & 不影响调用（有什么用？）

**指针**

```c
int *p;
char *s;
void *v; // 无类型指针，可以指向任意类型
int **pp;
int (*fp)(int, int);
int *arr[10]; // 指针数组：包含10个 int 指针的数组，[]优先级大于*
int (*arr)[10]; // 数组指针：指向一个包含10个 int 的指针，()优先级更大

int a = 10;
int *p1 = &a;
int *p2 = NULL;
int *p3 = malloc(sizeof(int));
*p1 = 20;
```

- 指针算术：`p[3] == *(p + 3)`，1的步长为指针指向元素类型

**结构体**

```c
typedef struct point{
	int x;
	int y;
};

point p = {1, 2};
p.x = 1;
p.y = 2;

point *q = &p;
q->x = 1;
q->y = 2;
```

- 可以嵌套结构体，也可以包含自身的指针（参考链表和树）
- 访问的时候用 .（其中的变量）或 ->（指针指向的结构体其中的变量）

**数组**

```c
int a[10];
int b[10][10];
char s[100];

int arr[] = {1, 2, 3, 4, 5}; // 自动推断长度
int arr[5] = {1, 2, 3, 4, 5}; // 自己写长度，自己填完
int part[5] = {1, 2}; // 部分初始化，剩余补0
int arr[10] = {[3] = 7, [2] = 9, [5] = 9}; // 跳位置部分初始化
char s1[] = "hello";
char s2[10] = "hello";
```

>[!HINT] **数组**
>- 数组的下标从 0 开始，到 n - 1 结束
>- **数组名 a 的本质是数组首元素的地址的符号，在赋值、传参、运算表达式中会退化为指向数组首元素的指针（如 int \*），除非对数组名寻址，或进行 sizeof 运算**
>	- 数组名是非左值，不能被赋值
>	- 数组名可以进行指针算术：`a[3] == *(a + 3)`，事实上该代码对于任意一个指针均成立
>	- `&a`的类型是 int (\*)[10] 数组指针，如果只写一维数组或者不用数组传参都用不到
>- **二维数组 b 退化后是 int (\*)[10]，不是 int \*\*！**
>- 数组的结构体包装方法可以便利于整体赋值、传参返回，详情见如下代码块：

```c
typedef struct ArrayWrapper{
	int arr[5];
};

ArrayWrapper a = {{1, 2, 3, 4, 5}}
ArrayWrapper b = a;
a.arr[0] = 100;
```

**例1 A+B Problem**

可以多次调用的高精度加法函数

```c
#include <stdio.h>
#include <string.h>

typedef struct{
	int d[1001];
	int len;
} bigint;

bigint read_bigint(){
	bigint x;
	char s[1001];
	scanf("%s", s);
	x.len = strlen(s);
	for (int i = 0; i < x.len; i++){
		x.d[i] = s[x.len - 1 - i] - '0';
	}
	return x;
}

bigint add(bigint a, bigint b){
	bigint c = {{0}, 0};
	int carry = 0;
	int max_len = a.len > b.len ? a.len : b.len;
	for (int i = 0; i < max_len || carry; i++){
		int sum = carry + (i < a.len ? a.d[i] : 0) + (i < b.len ? b.d[i] : 0);
		c.d[c.len++] = sum % 10;
		carry = sum / 10;
	}
	return c;
}

void print_bigint(bigint x){
	for (int i = x.len - 1; i >= 0; i--){
		printf("%d", x.d[i]);
	}
	printf("\n");
}

int main(){
	int n;
	scanf("%d", &n);
	bigint sum = {{0}, 0};
	for (int i = 0; i < n; i++){
		bigint x = read_bigint();
		sum = add(sum, x);
	}
	print_bigint(sum);
	return 0;
}
```

**联合体**

```c
union data{
	float f;
	int i;
	char c;
};
```

- 所有成员共享同一块内存，大小等于最大成员，同一时间只能对一个成员有效

**\*枚举常量**

```c
enum color {RED, GREEN, BLUE};
printf("%d %d %d\n", RED, GREEN, BLUE); // 输出 0 1 2
enum color c = RED;
enum color d;
d = GREEN;

enum color {ONE = 1, TWO, THREE};
printf("%d %d %d\n", ONE, TWO, THREE); // 输出 1 2 3

enum {RED, GREEN, BLUE}; // 此时变为全局变量，并有初始值
enum {MAX_SIZE = 100, MIN_SIZE = 1}; // 可以用于代替 #define 的工作
int a[MAX_SIZE];
```

- 本质上是int，用 %d 输出

#### 类型限定符

const 表示变量为只读，不能被修改，定义时即初始化

```c
const int a = 10;
const int *p; // p 指向的内容是只读的，但是 p 本身可以再赋值
int * const q = &a; // q 本身是只读的，但是 q 指向的内容可以再赋值
const int * const r = &a; // r 和 a 均为只读
```

理解：const 右侧最接近的内容将被设置为只读

#### 存储类

|     存储类      | 作用域  | 生命周期  | 存储位置  | 默认初始值 |
| :----------: | :--: | :---: | :---: | :---: |
|    `auto`    | 当前函数 | 函数执行期 |   栈   |  垃圾值  |
|  `register`  | 当前函数 | 函数执行期 |  寄存器  |  垃圾值  |
| `static`（局部） | 当前函数 |  程序   |  静态区  |   0   |
| `static`（全局） | 当前文件 |  程序   |  静态区  |   0   |
|   `extern`   | 跨文件  |  程序   | 全局数据区 |   0   |

#### typedef

```c
typedef struct{
	char *name;
	char *number;
} person;
```

#### 变量的动作

- 声明
- 定义
- 初始化
- 赋值

声明：告诉编译器存在一个变量/函数，它的名字和类型是什么，不一定分配内存

```c
extern int a;
int add(int, int);
```

定义：按这个类型分配一块内存

```c
int a;
int a = 67; // 定义 + 初始化
```

一个变量只能定义一次，却可以声明多次，在多 .c 或是 .h 文件中使用

```c
// 在 file1.c 中
int global = 100;

// 在 file2.c 中
extern int global;
```

### H4 变量类型转换 和 字面量后缀

#### 隐式转换

```c
int a = 10;
double b = a;
int c = 3.14; // 截断成3
int d = -3.14; // 截断成-3
```

>[!HINT] 截断
> 向零取整

#### 类型等级

```
char = short < int < long long < float < double < long double
```

如果出现任何一次 unsigned ，整个算术表达式就是 unsigned 运算

>[!NOTE] 整型提升
> - C标准强制规定：任何比 int 小的整数类型运算时会被提升为 int

#### 显式转换

```c
double x = (double)3 / 2;
int y = (int)3.14;
```

#### 字面量后缀

> [!WARNING] 惊天大坑
> ```c
> int a = 100000;
> int b = 100000;
> long long c = a * b; // 溢出
> long long d = 100000LL * 100000; // 小写字体不对的时候看不清
> float m = 3.14159265358979; // double 转 float 会丢精度
> float n = 3.14159265358979f;
> ```

