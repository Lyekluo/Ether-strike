
针对字符串处理

- NULL

- size_t

- 字符串检验
	- strlen 长度，不包括`\0`
	- strcmp 比较
	- strncmp 前 n 个比较
	- strchr 首次出现字符
	- strrchr 最后出现字符
	- strstr 首次出现字符串
	- strspn 开头连续可以在某字符串中找到字符的长度
	- strcspn 开头碰到某字符的长度
	- strtok 字符串分割
	- strpbrk 开头第一个可在某字符串中找到字符的位置
- 字符串操纵
	- strcpy 复制
	- strncpy 复制前 n 个
	- strcat 字符串拼接
	- strncat 追加字符串的前 n 个字符
- 字符数组操纵
	- memset 填充
	- memcmp 比较
	- memchr 查找字符
	- memcpy 复制（不支持重叠）
	- memmove 移动（支持重叠）

### strlen

```c
char str = "abc";
size_t len = strlen(str); // 3
```

### strcmp

```c
int res = strcmp("apple", "apricot"); // < 0
int res_n = strncmp("apple", "apricot", 2); // 0
```

### strchr / strrchr

```c
char str[] = "hello";
char *p1 = strchr(str, 'l');
char *p2 = strrchr(str, 'l');
```

### strstr

```c
char str[] = "hello world";
char *p = strstr(str, "world");
```

### strspn / strcspn

```c
size_t len1 strspn("123abc", "0123456789"); // 3
size_t len2 strcspn("hello", "l"); // 2
```

### strtok

```c
char str[] = "a,b";
char *token = strtok(str, ","); // "a\0b"
```

### strpbrk

```c
char str[] = "hello";
char *p = strpbrk(str, "xyzo"); // 返回'o'的地址
```