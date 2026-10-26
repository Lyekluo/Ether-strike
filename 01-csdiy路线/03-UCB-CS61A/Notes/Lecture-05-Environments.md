# 环境（作用域）

`func <name>(<formal parameters>) [parent=<label>]`

函数在被定义时还没被创建帧，到调用时创建

```python
# Wrong make_adder()

def make_adder(n):
	return adder
	
def adder(k):
	return n + k
	
add_three = make_adder(3)
print(add_three(4))
```

自己手写环境图逻辑：

第 3 行：定义了全局函数 make_adder
第 6 行：定义了全局函数 adder
第 9 行：调用 `make_adder(3)`，创建局部帧 f1，其中 n = 3
`make_adder`内部执行`return adder`，找不到，往上找到了，返回`adder`函数，然后被销毁了
`add_three` 现在指向`adder`对象
第 10 行：`print(add_three(4))`，创建局部帧 f2，其中 k = 4
`return n + k`的 n 找不到，往上找到全局帧也找不到，寄了

NameError: name 'n' is not defined