
针对单个字符处理

- 判断类
	- isalpha 字母
	- isdigit 数字
	- isxdigit 十六进制字符
	- isalnum 字母或数字
	- isupper 大写
	- islower 小写
	- isblank 空白：`' '` 和 `'\t'`
	- isspace 空白间隔：范围更大
	- isprint 打印：指的是能被打印的
	- ispunct 标点：非字母数字空白
	- iscntrl 控制：不可见的控制字符
	- isgraph 图形：isprint 减去一个空格
- 转换类
	- tolower
	- toupper
#### 参数

作用对象均为 int，但传入的值范围必须在 unsigned char 之内

#### 返回值

判断类函数如果判断为真，则返回非 0 值，若为假则返回 0

转换类函数返回单字符

#### 闲的

```c
static inline bool diy_isalpha(int c){
	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

static inline bool diy_isdigit(int c){
	return c >= '0' && c <= '9';
}

static inline bool diy_isxdigit(int c){
	return diy_isdigit(c) || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f');
}

static inline bool diy_isalnum(int c){
	return diy_isalpha(c) || diy_isdigit(c);
}

static inline bool diy_isupper(int c){
	return c >= 'A' && c <= 'Z';
}

static inline bool diy_islower(int c){
	return c >= 'a' && c <= 'z'; 
}

static inline bool diy_isblank(int c){
	return c == ' ' || c == '\t';
}

static inline bool diy_isspace(int c){
	return c == ' ' || (c >= 0x09 && c <= 0x0D);
}

static inline bool diy_isprint(int c){
	return c >= 0x20 && c <= 0x7E;
}

static inline bool diy_isgraph(int c){
	return c >= 0x21 && c <= 0x7E;
}

static inline bool diy_ispunct(int c) {
    return diy_isgraph(c) && !diy_isalnum(c);
}

static inline bool diy_iscntrl(int c) {
    // 控制字符：小于空格，或者 DEL(0x7F)
    return c < 0x20 || c == 0x7F;
}

static inline int diy_tolower(int c) {
    if (c >= 'A' && c <= 'Z') {
        return c | 0x20; // 异或也可以：c ^ 0x20
    }
    return c;
}

static inline int diy_toupper(int c) {
    if (c >= 'a' && c <= 'z') {
        return c & ~0x20; // 异或也可以：c ^ 0x20
    }
    return c;
}
```