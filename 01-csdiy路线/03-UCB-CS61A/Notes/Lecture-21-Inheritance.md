# 继承

## 类属性游标

```python
class Place:
	last = None
	
	def __init__(self, n):
		self.name = n
		self.then = Place.last
		Place.last = self
		
	def print_history(self):
		print(self.name)
		if self.then is not None:
			self.then.print_history()
```

类属性中含有一个全局游标 last，每次按该类创建新实例时，类属性 place.last 会指向被最新创建的实例

而对象属性中含有 then，用于记录上一个节点，在被创建时指向 place.last，然后再将自己作为 place.last

```python
>>> places = [Place(x * 2) for x in range(10)]
>>> print(Place.last.name)
18
>>> places[2].print_history()
4
2
0
```

## Friend 类双向引用

A 和 B 是朋友，那么 A 记录 B，B 记录 A

```python
class Friend:
	def __init__(self, name: str):
		self.name = name
		self.just_talked = None
		self.talked_to = 0 ## 别人对他讲话多少次，不是双向
	
	def talk(self, other):
		self.just_talked = other
		other.just_talked = self
		other.talked_to += 1
		
	def is_bestie(self, other):
		return self.just_talked == other and other.just_talked == self
		
	def has_bestie(self):
		return self.just_talked and self.is_bestie(self.just_talked)
```

测试实录

```python
>>> a = Friend("Alice")
>>> b = Friend("Bob")
>>> c = Friend("Charlie")
>>>
>>> a.talked_to
0
>>> a.just_talked
>>> a.name
'Alice'
>>> a.talk(b)
>>> a.talked_to
0
>>> b.talked_to
1
>>> b.just_talked
<__main__.Friend object at 0x7d82a0b041a0>
>>> b.just_talked.name
'Alice'
>>> a.has_bestie()
True
>>> b.has_bestie
<bound method Friend.has_bestie of <__main__.Friend object at 0x7d82a2402d50>>
>>> b.has_bestie()
True
>>> c.talk(b)
>>> a.has_bestie
<bound method Friend.has_bestie of <__main__.Friend object at 0x7d82a0b041a0>>
>>> a.has_bestie()
False
>>> b.has_bestie()
True
>>> c.is_bestie(b)
True
>>> b.is_bestie(c)
True
```