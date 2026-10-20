
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
char str[] = "abc";
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
char *p1 = strchr(str, 'l'); // str + 2
char *p2 = strrchr(str, 'l'); // str + 3
```

### strstr

```c
char str[] = "hello World";
char *p = strstr(str, "World"); // str + 6
```

### strspn / strcspn

```c
size_t len1 = strspn("123abc", "0123456789"); // 3
size_t len2 = strcspn("hello", "l"); // 2
```

### strtok

```c
char str[] = "Hello,World,C";

char *p = strtok(str, ",");
printf("%s\n", p); // Hello

p = strtok(NULL, ",");
printf("%s\n", p); // World

p = strtok(NULL, ",");
printf("%s\n", p); // C

p = strtok(NULL, ",");
if (p == NULL) printf("%p\n", p); // (nil)
```

传 NULL 是为了告知从上次记下的位置开始扫

连续的分隔符会直接跳过，跑到下一个真正的片段，不会返回空字符串

结尾的分隔符会被忽略

### strpbrk

```c
char str[] = "hello";
char *p = strpbrk(str, "xyzo"); // 返回'o'的地址
```

在 str 中找到第一个命中 accept 里任意字符的位置

### strcpy / strncpy

```c
char dest1[11], dest2[11], dest3[11];
strcpy(dest1, "HelloWorld"); // HelloWorld

strncpy(dest2, "HelloWorld", 5); // Hello?????
dest2[5] = '\0'; // Hello

strncpy(dest3, "Hi", 5); // Hi \0\0\0

strncpy(dest2, "Ha", 2); // Hallo
```

strncpy 不会清空目标内存，它只覆盖被指定的部分

安全做法配合 memset 使用

### strcat / strncat

```c
char dest[20] = "Hello";
strcat(dest, "C"); // HelloC \0
strncat(dest, "World", 3); // HelloCWor \0
```

strncat 必须算出正确的 n，否则后续内存会被非法访问

```c
size_t remaining_space = sizeof(dest) - strlen(dest) - 1;
strncat(dest, src, remaining_space);
```

-1 留给 \0

### memset

```c
int arr[5];
memset(arr, 0, sizeof(arr)); // arr 的 20 个字节清 0
```

memset 中间数字只取最低 8 位

对于非 char 类型数组，memset 只能用于清 0 或 -1（每个元素的长度不为 1 字节，清的值不一定等于元素的值）

对于 char 类型数组，memset 可以传任意 0 - 255 之间的整数，或者是直接传字符，char 数组会按 char 类型的 1 个字节逐个填充

```c
char str[10];
memset(str, 'A', sizeof(str)); // AAAAAAAAAA
str[9] = '\0';
```

memset 物理意义上只是无脑覆盖，对于 char 类型数组不会负责生成合法字符串，因此需要手动补 \0。

**对于任意 str 和 mem 函数来说，如果输入执行长度，它们就只管执行长度，而不会附加其它的限制**，这在强大的前提下导致了某种程度上的危险性。

### memcmp

```c
int arr1[] = {1, 2};
int arr2[] = {1, 3};
int res = memcmp(arr1, arr2, sizeof(arr1));
```

从头开始，发现任意一个字节不一样，则立即停止比较，返回这个字节的差值（前减后）

不能用来比较实际数值大小，因为只是局部性质

最常用法是判断是否完全相等，若为 0 则相等

### memchr

```c
char s[] = "hello";
char *p = memchr(s, 'l', 5); // s + 2
```

返回最早结果

memchr 同样只是严格按长度办事，不会检查 \0 而停下

memchr 返回 void * 指针

没有 memrchr！

### memcpy

```c
int src[3] = {1, 2, 3};
int dest[3];
memcpy(dest, src, sizeof(src)); // 1 2 3
```

惊天大坑：

假设我原本想要把某个字符串往后挪两位

```c
char s[10] = "ABCDEF";
memcpy(s + 2, s, 4); // ABABAB
```

在 char 数组不重叠的时候不用考虑这个问题，但是如果数组重叠，那么它真的是按一个一个字节从前到后搬的（在搬到 `s[4]` 之前所来源的 `s[2]` 已被覆盖为 'A'，那它就只能搬 'A'）

解决方案为：

### memmove

```c
char s[10] = "ABCDEF";
memmove(s + 2, s, 4); // ABABCD
```

会自动判断是从前往后还是从后往前（整体挪动的话总有一个是可以的）