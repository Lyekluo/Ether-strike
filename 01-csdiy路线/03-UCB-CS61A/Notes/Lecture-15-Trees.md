# 树

## 树的概述

**递归式描述**

一棵**树**有一个**根**标签和一系列**分支**，每个分支都是一棵树，没有分支的一棵树叫**叶子**

**关联式描述**

- 树的每个位置称作**节点**
- 每个节点都有一个**标签**，可以为任意值
- 每个节点可以是某个节点的父/子节点
- 最高的节点叫做根节点

## 对于树的行为设计

- 获取树根的标签：`t.label`
- 获取树的分支列表：`t.branches`
- 获取树的某个分支：`t.branches[i]`
- 判断树是否为叶子：`is_leaf(t)`
- 把树作为一个值：`return t`、`f(t)`、`[t]`、`s = t` 等等

## Code

```python
from dataclasses import dataclass, field

@dataclass
class Tree[T]:
	label: T
	branches : list[Tree[T]] = field(default_factory = list)
	
def is_leaf(t: Tree) -> bool:
	return not t.branches
```

### 例1 数叶子

```python
def count_leaves(t):
	if is_leaf(t):
		return 1
	else:
		branch_counts = [count_leaves(b) for b in t.branches]
		return sum(branch_counts)
```

### 例2 取最大标签值

```python
def largest_label(t):
	if is_leaf(t):
		return t.label
	else:
		return max([largest_label(b) for b in t.branches] + [t.label])
```

### 例3 取最大和路径

```python
def largest_path_sum:
	if is_leaf(t):
		return t.label
	else:
		return t.label + max([largest_path_sum(b) for b in branches])
```

### 例4

打印所有大于根标签的枝叶标签值

```python
def above_root(t):
	def process(u):
		if u.label > t.label:
			print(u.label)
		for b in u.branches:
			process(b)
	process(t)
```

四个例子分别指向

- 聚合
- 极值
- 路径
- 条件遍历