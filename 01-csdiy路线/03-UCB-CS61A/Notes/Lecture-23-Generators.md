# 生成器

调用一个包含 yield 的函数，生成一个迭代器，在迭代过程中函数不会被立即执行完，而是步步执行，期间函数帧仍然存在，并被冻结，该函数是一个生成器函数

```python
>>> def plus_minus(x):
...     yield x
...     yield -x
...
>>> t = plus_minus(3)
>>> t
<generator object plus_minus at 0x7b88720e53c0>
>>> next(t)
3
>>> next(t)
-3
>>> next(t)
Traceback (most recent call last):
  File "<python-input-5>", line 1, in <module>
    next(t)
    ~~~~^^^
StopIteration
```

局部帧被冻结的证明：

```python
>>> def counter():
...     count = 0
...     while count < 2:
...         count += 1
...         yield count
...
>>> c = counter()
>>> next(c)
1
>>> next(c)
2
```

如果被销毁，则局部变量 count 每次都是 1，而事实上结果是 2，说明局部变量 count 保留了上一次的运算结果，所在帧没有被销毁

生成器函数里面也可以写 return 返回