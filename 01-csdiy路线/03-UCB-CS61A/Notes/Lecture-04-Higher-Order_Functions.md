# 高阶函数

最初定义函数时，是将运算模式提取出来，不再依赖具体数字
定义高阶函数时，是将计算方法提取出来，不再依赖具体函数

- 一个代码块只干一件事
- 模块化，打包成可复用的函数、类、文件等等
- 抽象屏障

迭代改进算法：

```python
def approx_eq(x, y, tolerance):
	return abs(x - y) < tolerance
	
def golden_update(guess):
	return 1 / guess + 1
	
def square_close_to_successor(guess):
	return approx_eq(guess * guess, guess + 1)

def improve(update, close, guess = 1):
	while not close(guess):
		guess = update(guess)
	return guess
	
phi = improve(golden_update, square_close_to_successor)
```

## 测试

**断言式 Assertion**

```python
>>> from math import sqrt
>>> phi = 1/2 + sqrt(5) / 2
>>> def improve_test():
		approx_phi = improve(golden_update, square_close_to_successor)
		assert approx_eq(phi, approx_phi), "phi differs from its approximation"
>>> improve_test()
```

assert 语句包含一个布尔表达式，后面跟一行引号括起来的文本（单引号双引号均可，前后一致）

如果 assert 的表达式为真值，执行 assert 语句没有任何效果，否则显示预设文本

**文档测试 Doctest**

```python
def fib(n):
    """返回第 n 个斐波那契数"""
    if n == 1 or n == 2:
        return 1
    return fib(n-1) + fib(n-2)

def fib_test():
    """这是一个专门用来测试 fib 的普通函数"""
    assert fib(2) == 1, '第2个斐波那契数应该是 1'
    assert fib(3) == 1, '第3个斐波那契数应该是 1'
    assert fib(50) == 7778742049, '在第50个斐波那契数发生 Error'
    print("fib_test 全部通过！")

def sum_naturals(n):
    """返回前 n 个自然数的和。

    >>> sum_naturals(10)
    55
    >>> sum_naturals(100)
    5050
    """
    total, k = 0, 1
    while k <= n:
        total, k = total + k, k + 1
    return total
```

绿色部分是文档字符串，第一行可写说明，随后任意一个 `>>>` 开头的代码行将被执行，并把下一行作为预期结果

验证方法：

1. 不进入 REPL

```bash
python3 -m doctest hw.py
```

最记住

2. 导入文件后测试

```bash
python3 -i demo.py
```

```python
>>> assert fib(8) == 13, "第八个斐波那契数是13"
>>> assert fib(8) == 999, "我故意写错预期结果"
AssertionError：我故意写错预期结果
```

直接调用

```python
fib_test()
fib_test 全部通过！
```

单个函数的测试

```python
>>> from doctest import run_docstring_examples
>>> run_docstring_examples(sum_naturals, globals(), True)
```