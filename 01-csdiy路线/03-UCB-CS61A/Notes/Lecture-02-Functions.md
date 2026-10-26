# 函数

## 赋值语句 Assignment Statements

1. 对右侧表达式求值
2. 将右值赋给左值

**”左值“：**
- 名字
- 对象属性
- 下标
- 元组解包
- 星号解包

“右值”是表达式

任何左值单独出现时输出它本身的值

>[!WARNING] 函数的名字
> 函数的名字不一定指向最初的函数

## 环境图 Environment Diagrams

**帧**
- 负责维持名字和值的绑定
- 不允许重复的名字
- 全局帧和局部帧

**全局帧** 包括内置的所有名字，例如`min, pow`等等

**环境** 是帧的一条链，以全局帧结尾

**名字的查找** 从当前环境链的第一帧开始，找不到就沿链向外

用户定义的函数：
```python
from operator import mul
def square(x):
	return mul(x, x)
square(-2)
```

调用用户定义的函数
1. 创建新帧，并搭建配套的新环境链
2. 将实参绑定到形参
3. 执行函数主体，求值

## Print

`print(x)`的内容是 print 的副作用，返回值是 None（由于是 None 导致不显示），打印内容在返回值之前

**：非纯函数**

## \*小表达式问题 Small Expressions

```python
def f(x):
    return x + 1
def g(x):
    return 2 * x - 1
def h(x, y):
    return int(str(x) + str(y))
```

```python
class Number:
    def __init__(self, value):
        self.value = value
    def __str__(self):
        return str(self.value)
    def calls(self):
        return 0
    def chars(self):
        return 1

class Call:
    """A call expression."""
    def __init__(self, f, operands):
        self.f = f
        self.operands = operands
        self.value = f(*[e.value for e in operands])
    def __str__(self):
        return f'{self.f.__name__}({",".join(map(str, self.operands))})'
    def calls(self):
        return 1 + sum(o.calls() for o in self.operands)
    def chars(self):
        return 3 + sum(o.chars() for o in self.operands) + (len(self.operands) - 1)

def smalls(n):
    if n == 0:
        yield Number(5)
    else:
        for operand in smalls(n-1):
            yield Call(f, [operand])
            yield Call(g, [operand])
        for k in range(n):
            for first in smalls(k):
                for second in smalls(n-k-1):
                    if first.value > 0 and second.value > 0:
                        yield Call(h, [first, second])

def print_smallest():
    result = []
    for i in range(10):
        result.extend([e for e in smalls(i) if e.value == 2026])
    for e in result:
        assert eval(str(e)) == e.value
        print(e, '->', e.value, 'has', e.calls(), 'calls and', e.chars(), 'characters.')
```

理解后面补