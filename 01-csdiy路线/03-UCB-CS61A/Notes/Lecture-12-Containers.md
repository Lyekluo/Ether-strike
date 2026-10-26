# 容器

一般指可以装其他对象的复合数据类型

- 序列
- 映射
- 集合

在环境图中表示时，容器里装的不是值本身，而是指向值的指针

## 盒指针图 Box-and-Pointer Notation

- 列表在内存中表现为一排带索引的相邻盒子
- 盒子要么装原始值，要么装指针，指针指向另一个复合对象，如另一个列表或函数
- 变量名不存数据，变量名只存指向盒子的指针

```python
nested_list = [[1, 2], [], [[3, False, None], [4, lambda: 5]]]
```

手搓练习
- 空列表用 `empty list` 表示
- lambda 算子用 `func λ() <line 8> [parent=Global]` 表示

## 聚合 Aggregation

**聚合的概念大约是将 一组多元素的集合 运算得到单个元素，针对算术、逻辑和字符串**

容器是聚合的原始数据

有一些内置函数可以将几个可迭代对象压缩成单一的值

- `sum(iterable, start)`

对可迭代对象中所有元素求和，再加上 start值（默认为 0），这个时候就完全可以不带 start 参数：`sum(iterable)`

不能用来拼字符串

- `max(iterable, key=func)`

用 key 变换，得到最大值的原元素被返回

- `all(iterable)` 

这个是个检测所有真值的函数，返回 True 当且仅当全为真值

```python
>>> words = ["CS", "61A", "is", "fun"]

>>> " ".join(words)
'CS 61A is fun'

>>> "".join(words)
'CS61Aisfun'
```

**例1** summation 的另一种写法

```python
def cube(k):
	return pow(k, 3)
	
def summation(n, term):
	"""Sum the first n terms of a sequence.
	
	>>> summation(5, cube)
	225
	"""
	total, k = 0, 1
	while k <= n:
		total, k = total + term(k), k + 1
	return total
	
def summation2(n, term):
	return sum([term(x) for x in range(1, n + 1)])
```

**例2** 停车方案

将车辆停车停在一排停车位，一辆摩托车占据一个停车位，一辆轿车占据两个相邻停车位。一个长为 n 的字符串能代表 n 个相邻停车位，用 % 表示一辆摩托车，<>表示一辆轿车，. 表示一个空位

补充 park 函数，输入一个 n 作为长度，使得其能返回所有该长度车辆的停放方式所代表的字符串组成的列表

解答如下：

```python
def park(n):
	"""Return the ways to park cars and motorcycles in n adjacent spots.
	>>> park(1)
	['%', '.']
	>>> park(2)
	['%%', '%.', '.%', '..', '<>']
	>>> len(park(4))
	29
	"""
	if n < 0:
		return []
	elif n == 0:
		return ['']
	else:
		return ['%' + s for s in park(n - 1)] + ['.' + s for s in park(n - 1)] + ['<>' + s for s in park(n - 2)]
```

思路：考虑开头的所有合法字符串种类，往下递归即可得到所有字符串的列表

**——递归的信仰之跃——**