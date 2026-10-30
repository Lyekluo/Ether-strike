# 变异

又称为原地修改

## List Mutation

以下代码创建了一个新的列表

```python
s = [1, 2, 3]
t = list(s)
u = [x for x in s]
v = s + t
w = t[1:]
```

以下代码改变了原列表的值

```python
s.append(4) # 尾插
s[1] = 'hi' # 改变值
s.extend(t) # 把 t 加在 s 后面
s += t # 同上
s.remove(2) # 去掉第一个值为 2 的元素
s.pop() # 去掉最后一个元素
s.pop(1) # 去掉索引为 1 的元素
```

## 例题

### 例1 条件聚合路径

打印出树 t 中含有一个标签和大于等于 n 的路径

```python
def print_big(t, n):
	def helper(t, p):
		p = p + [t.label]
		if is_leaf(t):
			if sum(p) >= n:
				print(p)
		else:
			for b in t.branches:
				helper(b, p)
	helper(t, [])
```

直观上是自顶向下遍历的，以叶子作为终点来判定，路径在路上被以列表合并的方式记录

**不能使用变异方法！** 否则会导致 p 在不同的分支中被共享干扰（一直在同一内存下修改）

使用创建方法会在局部帧中给 p 赋值，不会污染上一级或全局

```python
>>> t = Tree(1, [Tree(2), Tree(3, [Tree(4), Tree(5)])])
>>> print_big(t, 6)
[1, 3, 4]
[1, 3, 5]
```

### 例2

返回树中，节点值大于所有祖先节点值的节点数量

```python
def bigs(t):
	n = [0]
	
	def f(a, x):
		if a.label > x:
			n[0] += 1
		for b in a.branches:
			f(b, max(a.label, x))
	
	f(t, t.label - 1)
	return n[0]
```

```python
>>> a = Tree(1, [Tree(4, [Tree(4), Tree(5)]), Tree(3, [Tree(0, [Tree(2)])])])
>>> print(bigs(a))
4
```

### 例3

```python
def chain(s):
    return [s[0], s[1:]]

silver = [2, chain([3, 4, 5])] # [2, [3, [4, 5]]]

gold = [silver[0], silver[1].pop()] # [2, [3]]

silver[0] = 1 # [1, [3]]

platinum = chain(chain([6, 7, 8])) # [6, [[7, 8]]]

print("silver:", silver)       # [1, [3]]
print("gold:", gold)           # [2, [4, 5]]
print("platinum:", platinum)   # [6, [[7, 8]]]
```