# 效率

这节没有新语法

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

