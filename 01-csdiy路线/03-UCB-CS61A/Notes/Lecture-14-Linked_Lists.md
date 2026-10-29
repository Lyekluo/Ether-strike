# 链表

链表是包含值和指向剩余部分链表的结构

```python
type LinkedList[T] = Link[T] | tuple[()]

@dataclass
class Link[T]:
	first: T
	rest: LinkedList[T] = ()
```

空元组用来作为空链表

T 的值表示当前节点的值

效果如下：

```python
>>> Link(3, Link(4, Link(5)))
Link(first=3, rest=Link(first=4, rest=Link(first=5, rest=())))
```

或是步步前插

```python
>>> s = ()
>>> s = Link(5, s)
>>> s = Link(4, s)
>>> s = Link(3, s)
>>> s
Link(first=3, rest=Link(first=4, rest=Link(first=5, rest=())))
```

加入打印格式：

```python
from dataclasses import dataclass

type LinkedList[T] = Link[T] | tuple[()]

@dataclass
class Link[T]:
	"""A Link has a first value of type T and the rest of the linked list.
	"""
	
	first: T
	rest: LinkedList[T] = ()
	
	def __str__(self):
		return format_link(self)

def format_link(s: Link):
	"""Return a Link s formatted as items within parentheses.
	"""
	
	string = '(' + str(s.first)
	remaining = s.rest
	while isinstance(remaining, Link):
		string += ' ' + str(remaining.first)
		remaining = remaining.rest
	
	assert remaining == (), f'{s!r} is not a LinkedList'
	return string + ')'
```

效果

```python
>>> s = Link(3, Link(4, Link(5)))
>>> print(s)
(3 4 5)
>>> s.first
3
>>> s.rest.first
4
>>> s.rest.rest.first
5
>>> s.rest.rest.rest
()
>>> s.rest.rest
Link(first=5, rest=())
>>> print(s.rest.rest)
(5)
```