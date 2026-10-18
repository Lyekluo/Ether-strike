
## Lambda 表达式

对 Lambda 表达式求值得到一个函数

```python
def summation(n, term):
	total, k = 0, 1
	while k <= n:
		total, k = total + term(k), k + 1
	return total
	
summation(5, lambda x: pow(1/2, x))
```

该函数的形参是 x

Lambda 表达式在被调用时，会和函数一样创造新的帧

## Function Currying 函数柯里化

将接收多个参数的函数 拆解成 每次只接受一个参数的函数

```python
def curry(f):
    def g(x):
        def h(y):
            return f(x, y)
        return h
    return g
```

此时有`pow(2, 3)`等价于`curry(pow)(2)(3)`

**例1**  将列表 `[1, 2, 3]` 里的每个数都加上 10，可以写：

```python
from operator import add
add_ten = curry(add)(10)
list(map(add_ten, [1, 2, 3]))
```

此处为什么要柯里化？

1. 列表是可变对象，若数据不可变则无法操作，应当生成新的数据
2. 对原有数据的保留是有益处的

## Zero-argument Function 零参数函数

1. 用于纯副作用函数
2. 延迟执行：某件事情应当交给别人决定什么时候做

函数赋给别的名字时 带不带括号，应当看要的是**函数本身**还是**函数算出的结果**

```python
import time
now = time.time   # now 变成了一个内置函数
now = time.time()   # 获取当前时间戳
```