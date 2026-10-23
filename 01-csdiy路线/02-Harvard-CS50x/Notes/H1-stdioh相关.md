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


### 格式化输出

```c
printf("ftext, %d", n); // 输出到屏幕
fprintf(fp, "ftext, %d", n); // 输出到文件指针 fp 指向的文件

char buf[20];
sprintf(buf, "%d", 123); // 输出到字符串 buf，无长度限制（请考虑缓冲区溢出）
snprintf(buf, sizeof(buf), "%d", 123); // 输出长度限制
```

### 格式化输入

```c
scanf("%d", &n); // 从键盘读入
fscanf(fp, "%d", &n); // 从文件读入

char str[] = "123 456";
int a, b;
sscanf(str, "%d %d", &a, &b); // 从字符串读取数据
```

### 单字符读写

```c
int c - getchar(); // 读入一个字符，遇到 EOF 则返回 -1
int d = fgetc(fp); // 从 fp 指向的文件读入一个字符
ungetc('A', stdin); // 把字符'A'塞回输入流的最前面
putchar('A'); // 像屏幕输出一个字符
fputc('A', fp); // 向文件输出一个字符
```

`getchar()` 常用于吃换行，`ungetc` 常用于撤回解析读入

### 字符串读写

```c
char s[100];
fgets(s, sizeof(s), stdin); // 从键盘读入一整行
fgets(s, sizeof(s), fp); // 从文件读入一整行
```

fgets 会包括换行符，如果需要纯字符串内容需要让 getchar 吃一下

### 二进制读写

```c
int arr[3] = {1, 2, 3};
fwrite(arr, sizeof(int), 3, fp); // 写入 3 个 int 类型的数据

int dest[3];
fread(dest, sizeof(int), 3, fp); // 从 fp 指向的文件读取 3 个 int 类型的数据
```

fread 和 fwrite 会返回 size_t 类型，表示成功读写的元素个数