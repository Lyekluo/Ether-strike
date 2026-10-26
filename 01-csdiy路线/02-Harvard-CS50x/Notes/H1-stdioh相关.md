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

注意到单字符输出都把内容放在最前

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

### 文件操作

#### 打开与关闭

```c
FILE *file_ptr = fopen("data.txt", "r");
if (file_ptr == NULL){
	fprintf(stderr, "fopen failed, errno: %d\n", errno);
	return 1;
}
```

fopen 完全可以用来创建文件

不检查会 RE

```c
// FILE *freopen(const char *filename, const char *mode, FILE *stream);

if (freopen("input.txt", "r", stdin) == NULL){
	fprintf(stderr, "redirect stdin failed\n");
	return 1;
}

if (freopen("output.txt", "w", stdout) == NULL){
	fprintf(stderr, "redirect stdout failed\n");
	return 1;
}
```

freopen：尝试关闭 stream 原本指向的流，根据 filename 和 mode 打开新文件，作为新的流与 stream 绑定，绑定成功返回 stream 指针，失败返回 NULL

mode 有 r w a b 等模式，C11 有独占创建模式 wx wbx

**这个 stdin 被覆盖掉之后改回来太麻烦了，而且不一定有这个权限，所以我估计正常人类应该不会干这种事**

```c
int close_status = fclose(file_ptr);
if (close_status == EOF){
	fprintf(stderr, "fclose failed\n");
}
```

记得关

#### 缓冲控制

```c
printf("Processing data...");
fflush(stdout);
```

printf 使用行缓冲，没有遇到 `\n` 不会立刻输出到终端

没有 `fflush(stdin)` ！

```c
// void setbuf(FILE *stream, char *buffer);
setbuf(file_ptr, NULL); // 禁用缓冲

// int setvbuf(FILE *stream, char *buffer, int mode, size_t size);
char my_buffer[4096];
setvbuf(file_ptr, my_buffer, _IOFBF, sizeof(my_buffer));
```

mode 中的缓冲模式分别有 \_IOFBF（全缓冲），\_IOLBF（行缓冲），\_IONBF（无缓冲）

#### 定位

```c
int seek_status = fseek(file_ptr, 0, SEEK_END);
if (seek_status != 0){
	fprintf(stderr, "fseek failed\n");
}

long current_offset = ftell(file_ptr);
if (current_offset = EOF){
	fprintf(stderr, "ftell failed\n");
}

rewind(file_ptr);

fpos_t current_pos;
if (fgetpos(file_ptr, &current_pos) == EOF){
	fprintf(stderr, "fgetpos failed\n");
}

if (fsetpos(file_ptr, &current_pos) == EOF){
	fprintf(stderr, "fsetpos failed\n");
}
```

越界后 fseek 在下一次读取报错

fpos_t 所能存储的位置数有更少的溢出可能

#### 状态查询

```c
char ch;
while ((ch = fgetc(file_ptr)) != EOF){
	// 处理
}
if (feof(file_ptr)){
	printf("reached end of file\n");
}
if (ferror(file_ptr)){
	fprintf(stderr, "IO error occurred\n");
}
```

feof 返回一个 int，如果到了末尾，就返回非 0 值（作为真），否则就返回 0

如果循环结束了，可以判断一下是正常到文件尾还是出错了

```c
clearerr(file_ptr);
```

把 FILE * 的 feof 和 ferror 标志清 0，使文件流恢复正常工作

**清零的意思是让 feof 忘掉到了末尾的记忆，不然动不了**

```c
perror("open failed\n");
```

perror 永远打印到 stderr 里

#### 文件管理

```c
if (remove("temp_data.txt") != 0){
	perror("remove failed"); // remove failed: No such file or directory
}

if (rename("oldname.txt", "newname.txt") != 0){
	perror("rename failed"); // rename failed: No such file or directory
}

FILE *tmp_fp = tmpfile();
if (tmp_fp != NULL){
	fputs("temporary cache", tmp_fp);
	fclose(tmp_fp);
}
```

tmpfile 用完会自动删除