# 序列

满足以下 5 个条件的数据类型

1. 每个元素有明确位置
2. 可用位置读取一个元素
3. 可读取一段
4. 可获取长度
5. 可被迭代遍历

**四种原生序列：**

1. 列表（List）：`[1, 2, 3]`
2. 元组（Tuple）：`(1, 2, 3)`
3. 字符串（String）：`"Lyekluo"`
4. 范围（Range）：`range(1, 10)`

## Demo

```python
def demo1():
    >>> x = 6
    >>> digits = [1, 8, 0, 8]
    >>> digits
    [1, 8, 0, 8]
    >>> digits[2] # Get one element out of the list. List indices start at 0!
    0
    >>> def get_index():
    ...   return 1
    ...
    >>> digits[get_index()]
    8
    >>> def get_list(n):
    ...   return [n, n + 1, n + 2]
    ...
    >>> get_list(3)
    [3, 4, 5]
    >>> get_list(3)[get_index()]
    4
    >>> 1 in digits
    True
    >>> 2 in digits
    False
    >>> [1, 8] in digits
    False
    >>> other_digits = [1, 2, [1, 8]]
    >>> [1, 8] in other_digits
    True
    >>> digits + other_digits
    [1, 8, 0, 8, 1, 2, [1, 8]]
    >>> len(digits)
    4
    >>> type(digits)
    <class 'list'>
    >>> digits2: list[int] = [1, 4, 5]
    return

def demo2():
    >>> digits = [1, 8, 0, 8]
    >>> i = 0
    >>> while i < len(digits):
    ...   print(digits[i])
    ...   i += 1
    ...
    1
    8
    0
    8
    >>> for d in digits:
    ...   print(d)
    ...
    1
    8
    0
    8
    return

def range_demo():
    >>> range(3)
    range(0, 3)
    >>> for x in range(3):
    ...   print(x)
    ...
    0
    1
    2
    >>> digits = [1, 0, 1, 8]
    >>> for i in range(len(digits)):
    ...   print(digits[i])
    ...
    1
    0
    1
    8
    >>> [100 * d for d in digits]
    [100, 0, 100, 800]
    >>> [100 * d for d in digits if d < 5]
    [100, 0, 100]
    return
```

### 列表

列表是可变序列，可以求长度，可以用 for 遍历

单个元素正向索引从 0 开始（从第一个到最后一个），负向索引从 -1 开始（倒数第几个）（？没见过 挺新奇的）

多个元素索引：

```python
>>> s = [0, 1, 2, 3, 4]

>>> s[1:]
[1, 2, 3, 4]

>>> s[:3]
[0, 1, 2]

>>> s[1:4]
[1, 2, 3]

>>> s[::2]
[0, 2, 4]

>>> s[::-1]
[4, 3, 2, 1, 0]

>>> s[-2::-1]
[3, 2, 1, 0]
```

多元素索引在越界时不会报错

多元素索引会产生新对象，容易导致性能问题

`in`操作符判断单个元素是否被包括在序列内，而序列的子序列不被包括在序列内：不能使用`[1, 2] in [1, 2, 3]`返回 True

列表可以直接用 + 进行前后拼接

`digits: list[int] = [1, 4, 5]`提示静态类型（只是写给自己和IDE看，IDE 可以据此推荐对象方法）

### 范围

`list(range(-2, 2)) == [-2, -1, 0, 1]`
`list(range(4)) == [0, 1, 2, 3]`

### 列表推导式

有点像集合描述法

#### 1 对单个元素做变形：**$\{f(x)\ |\ x∈S\}$**

`[<expression> for <name> in <iterable>]`

```python
>>> [x * 2 for x in [1, 2, 3]]
[2, 4, 6]

>>> [s.upper() for s in ["a", "b"]]
['A', 'B']
```

#### 2 带过滤器：$\{f(x)\ |\ x∈S\ 且\ P(x)\}$

`[<expression> for <name> in <iterable> if <condition>]`

```python
>>> [x * 2 for x in [1, 2, 3, 4] if x % 2 == 0]
[4, 8]
```

#### 3 笛卡尔积

`[<expression> for <name1> in <iterable1> for <name2> in <iterable2>]`

```python
>>> [x + y for x in [1, 2] for y in [10, 20]]
[11, 21, 12, 22]
```

等价于嵌套循环，后面的是里层循环

#### Promote 函数

```python
def promoted(s, f):
	return [e for e in s if f(e)] + [e for e in s if not f(e)]
```