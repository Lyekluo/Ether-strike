# 迭代器

一个容器可以提供一个迭代器，能够依次读取其中的元素

一般形式：

`iter(iterable)`

```python
>>> s = [3, 4, 5]
>>> t = iter(s)
>>> next(t)
3
>>> next(t)
4
>>> u = iter(s)
>>> next(u)
3
>>> next(t)
5
>>> w = u
>>> next(w)
4
>>> next(t)
Traceback (most recent call last):
  File "<python-input-31>", line 1, in <module>
    next(t)
    ~~~~^^^
StopIteration
```

我们可以用 `reversed` 函数生成反向迭代器

`reversed(iterable)`

```python
>>> t = reversed(s)
>>> next(t)
5
>>> next(t)
4
>>> next(t)
3
```

## 使用 map 函数建立迭代链路

一般形式：

`map(func, iterable)`

测试

```python
>>> def cube(k):
......  print("cubing", k)
   ...  return pow(k, 3)
   ...
>>> x = [cube(k) for k in range(1, 6)]
cubing 1
cubing 2
cubing 3
cubing 4
cubing 5
>>> x
[1, 8, 27, 64, 125]
>>> x = map(cube, range(1, 6))
>>> x
<map object at 0x7d82a0b2a1c0>
>>> x = list(x)
cubing 1
cubing 2
cubing 3
cubing 4
cubing 5
>>> x
[1, 8, 27, 64, 125]
>>> x = map(cube, range(1, 6))
>>> total = sum(x)
cubing 1
cubing 2
cubing 3
cubing 4
cubing 5
>>> total
225
>>> x = list(x)
>>> x
[]
```

## 其它函数

python 内置了一些其它返回惰性求值迭代器的函数：

已知的 `map(func, iterable)`，处理后对应的每一项返回 `func(x)`

`filter(func, iterable)`：func 是过滤函数，用于条件判断

`zip(first_iter, second_iter)`：拉链函数，将迭代器中的多个序列对应位置的元素打包成元组返回，碰到较短的序列耗尽就停止

后续可以作为多组数据进行处理

（不止能传入两个 iterable）

```python
>>> names = ['Alice', 'Bob', 'Charlie']
>>> scores = [90, 85, 95]
>>>
>>> z = zip(names, scores)
>>> z
<zip object at 0x7d82a0b2ba80>
>>> list(z)
[('Alice', 90), ('Bob', 85), ('Charlie', 95)]
>>>
>>> list(zip([1, 2, 3, 4], ["a", "b"]))
[(1, 'a'), (2, 'b')]
```

zip 函数另一个例子：矩阵转置

```python
>>> matrix = [[1, 2, 3], [4, 5, 6]]
>>> transposed = list(map(list, zip(*matrix)))
>>> transposed
[[1, 4], [2, 5], [3, 6]]
>>> transposed = list(map(list, zip(*transposed)))
>>> transposed
[[1, 2, 3], [4, 5, 6]]
```

其中的解包操作符 `*`：

对于某个可迭代对象中的所有元素，解包成各自独立的参数传给函数

## all and any

`all(s: iterable) -> bool`

当 iterable 中存在一值为假值时返回 False，否则返回 True

`any(s: iterable) -> bool`

当 iterable 中存在一值为真值时返回 True，否则返回 False

```python
>>> x = any(map(print, range(-3, 3)))
-3
-2
-1
0
1
2
>>> x
False
>>> x = all(map(print, range(-3, 3)))
-3
>>> x
False
```

两个函数都是拿到每一个值都立刻做测试