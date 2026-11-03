# 效率

## Memorization 记忆化

fib 函数

```python
def fib(n):
    if n == 0:
        return 0
    elif n == 1:
        return 1
    else:
        return fib(n - 1) + fib(n - 2)
```

fib 递归会算死人的，每次都把同一个值重新算一遍

解决：

```python
def memo(f):
	cache = {}
	def memoized(n):
		if n not in cache:
			cache[n] = f(n)
		return cache[n]
	return memoized
	
@memo
def fib(n):
	if n == 0:
		return 0
	elif n == 1:
		return 1
	else:
		return fib(n - 1) + fib(n - 2) 
```

然后速度直接起飞

```python
>>> fib(1000)
43466557686937456435688527675040625802564660517371780402481729089536555417949051890403879840079255169295922593080322634775209689623239873322471161642996440906533187938298969649928516003704476137795166849228875
```

## 列表

```python
def using_list_comprehension(n):
	return [k * k for k in range(n)]
	
def using_append(n):
	s = []
	for k in range(n):
		s.append(k * k)
	return s
	
def using_assign(n):
	s = [0 for k in range(n)]
	for k in range(n):
		s[k] = k * k
	return s
	
def using_insert(n): ## 这个结果是逆序的
	s = []
	for k in range(n):
		s.insert(0 , k * k)
	return s
	
def using_add(n):
	s = []
	for k in range(n):
		s = s + [k * k]
	return s
```

- 列表推导式
- 尾插
- 按索引赋值
- 后移并前插
- 列表拼接

前三个是快的动作，因为它们每次操作不接触已有数据；后两个是慢的动作，引发了大量的数据位移和复制

## Powers 无限序列生成与截断

```python
def powers(b):
	 n = 0
	 while True:
		 yield pow(b, n)
		 n += 1
		 
def prefix(t, n):
	for i in range(n):
		yield next(t)
```

```python
>>> list(prefix(powers(2), 10))
[1, 2, 4, 8, 16, 32, 64, 128, 256, 512]
```

## 高阶生成器函数

```python
>>> from operator import add
>>> 
>>> def map_pairs(f, t):
...     previous = next(t)
...     for x in t:
...         yield f(previous, x)
...         previous = x
...
>>> list(map_pairs(add, iter([3, 4, 5, 6, 7])))
[7, 9, 11, 13]
>>> list(prefix(map_pairs(lambda x, y:(x, y), powers(2)), 5))
[(1, 2), (2, 4), (4, 8), (8, 16), (16, 32)]
```

其中循环 `for x in t` 即为不断调用 `next(t)` ，拿到里面的数据赋值给 x，直到 StopIteration

## 链表和树的生成器遍历

我们回忆链表和树的类定义

```python
from dataclasses import dataclass, field

type LinkedList[T] = Link[T] | tuple[()]

@dataclass
class Link[T]:
	first: T
	rest: LinkedList[T] = () # 默认为空
	
@dataclass
class Tree[T]:
	label: T
	branches : list[Tree[T]] = field(default_factory = list)
```

遍历生成器函数

```python
def items(s: LinkedList):
	while isinstance(s, Link):
		yield s.first
		s = s.rest
		
def labels(t: Tree):
	yield t.label
	for b in t.branches:
		yield from labels(b)
```

`yield from` 的定义是将后面的生成器函数遍历完的结果一个接一个全部传回

## 函数装饰器

```python
>>> def trace(fn):
...     def wrapped(x):
...         print('->', fn, '(', x, ')')
...         return fn(x)
...     return wrapped
...
>>> @trace
... def triple(x):
...     return 3 * x
...
>>> triple(12)
-> <function triple at 0x7082242756f0> ( 12 )
36
>>> run_docstring_examples(triple, globals(), True)
Finding tests in NoName
```

我们先定义了一个高阶函数 trace，它返回一个函数：在调用自己的参数之前，先用一条 print 语句把函数和参数打印出来

在 `@trace` 下，triple 最终绑定的不是 triple 函数本身，而是 `trace(triple)` 的返回值

如果前面没有 trace，等价写法即为在后面补上

```python
>>> triple = trace(triple)
```

装饰器符号 `@` 后面也可以跟一个调用表达式，求值得到一个函数