# 对象

## 字典

字典是一种映射类型，包含若干从 Keys 映射到 Values 的键值对，在内存中通过哈希表实现

## 字典推导式

`{<key exp>: <value exp> for <name> in <iterable> if <filter exp>}`

```python
def multiples(s, factors):
	
	"""Create a dictionary where each factor is a key and each value is the elements of s that are multiples of the key.
	
	>>> multiples([3, 4, 5, 6, 7, 8], [2, 3])
	{2: [4, 6, 8], 3: [3, 6]}
	>>> multiples([1, 2, 3, 4, 5], [2, 5, 8])
	{2: [2, 4], 5: [5], 8: []}
	"""
	
	return {d: [x for x in s if x % d == 0] for d in factors}
```

嵌套的遍历

## 面向对象编程

面向对象编程（Object-oriented Programming, OOP）是一种组织程序的方法，在数据的使用实现之间建立了抽象屏障（abstraction barrier），对象存在无法从全局访问的局部状态，与对象的行为捆绑在一起，形成独立的代理实体与外界接口交互

## 对象

对象是带有属性和方法的数据值

对象的**属性**（atrribute）是与对象关联的名称-值对，可以通过点表达式访问。**实例属性**（instance attributes）是只属于某个特定对象的属性

对对象进行操作、执行与对象相关的计算的函数，称为**方法**。方法对于某个特定的对象调用，方法的返回值和副作用可能取决于对象的属性，也可能改变对象的属性

## 类

对象具有类型，其模板称为类。常用的对象都有内置类，也可以创建新的用户自定义类。类定义规定该类的对象共享哪些属性和方法：

```python
class <name>:
	<suite>
```

执行 class 语句时，创建一个新类，并在当前环境的第一个帧绑定 `<name>` ，然后执行语句

class 语句的 `<suite>` 里包含 def 语句，为类的对象定义新方法，函数 `__init__` 是这个类的构造函数（constructor）

**例1 基础的银行账户**

我们计划让这个类所定义的对象 Account

- 有两个属性：持有者、余额

```python
class Account:
	def __init__(self, account_holder):
		self.balance = 0
		self.holder = account_holder
```

其中 `__init__` 有两个形式参数，第一个是 `self`，即为对象的名字；第二个是 `account_holder`，绑定时传入一个参数（持有者）用来作为其内容

具体使用：

```python
>>> a = Account('Kirk')
>>> a.balance
0
>>> a.holder
'Kirk'
```

同一类的不同对象是相互独立的

```python
>>> b = Account('Spock')
>>> b.balance = 200
>>> [acc.balance for acc in (a, b)]
[0, 200]
>>> c = a
>>> c is a
True
```

**例2 带有多种操作的银行账户

我们计划让这个类定义的对象 Account

- 有两个属性：持有者、余额
- 有两个方法：存款和取款

```python
class Account:

	def __init__(self, account_holder):
		self.balance = 0
		self.holder = account_holder
		
	def deposit(self, amount):
		self.balance = self.balance + amount
		return self.balance
		
	def withdraw(self, amount):
		if amount > self.balance:
			return 'Insufficient funds'
		self.balance = self.balance - amount
		return self.balance
```

```python
>>> spock_account = Account('Spock')
>>> spock_account.deposit(100)
100
>>> spock_account.withdraw(90)
10
>>> spock_account.withdraw(90)
'Insufficient funds'
>>> spock_account.holder
'Spock'
```

可以用内置函数确认并查找对象的属性和行为

```python
>>> hasattr(spock_account, 'deposit')
True
>>> getattr(spock_account, 'balance')
10
```

**例3 类属性的共享**

我们计划让这个类定义的对象 Account

- 有一个类属性：interest（利率）
- 有两个对象属性：balance（余额）、holder（持有人）

```python
class Account:
	interest = 0.02
	def __init__(self, account_holder):
		self.balance = 0
		self.holder = account_holder
```

```python
>>> spock_account = Account('Spock')
>>> kirk_account = Account('Kirk')
>>> spock_account.interest
0.02
>>> kirk_account.interest
0.02
```

类属性可以修改，改动之后会改变该类所有实例的这一属性值

```python
Account.interest = 0.04
>>> spock_account.interest
0.04
>>> kirk_account.interest
0.04
```

如果针对某个账户实例的 `interest` 属性赋值，就会新建一个与已有类属性同名的实例属性，并在访问时被返回，对其他实例没有影响

后续再修改类属性后，被修改的实例属性不受影响

实例属性的被修改性质可以被恢复

```python
>>> kirk_account.interest = 0.08
>>> kirk_account.interest
0.08
>>> spock_acccount.interest
0.04

>>> Account.interest = 0.05
>>> spock_account.interest
0.05
>>> kirk_account.interest
0.08

>>> del kirk_account.interest
>>> kirk_account.interest
0.05
```

## @dataclass

`@dataclass` 是原生 class 的一个模板生成器

我们计划让这个类的对象 Line

- 具有两个对象属性：slope（斜率）、intercept（截距）

下面第一段代码块效果等价于第二段

```python
class Line:
	def __init__(self, slope, intercept):
		self.slope = slope
		self.intercept = intercept
```

引入 `@dataclass` 写法

```python
from dataclasses import dataclass

@dataclass
class Line:
	slope: float
	intercept: float
	def __str__(self):
		return format_line(self)
		
def format_line(c: Line):
	return f'y = {c.slope}x + {c.intercept}'
```

```python
>>> c = Line(3, 4)
>>> c.slope
3
>>> c.intercept
4
>>> c
Line(slope=3, intercept=4)
>>> type(c) == Line
True
>>> print(c)
y = 3x + 4
```

`__str__` 决定了打印 Line 所输出的格式化字符串，`__repr__` 决定了求值 Line 所输出的还原对象的表达式

dataclass 会自带 `__eq__` 来判断两个对象中的数据是否相等的方法

## 继承

一个账户类 Account

```python
class Account:
    
    interest = 0.02
    
    def __init__(self, account_holder):
        self.balance = 0
        self.holder = account_holder
    
    def deposit(self, amount):
        self.balance = self.balance + amount
        return self.balance
    
    def withdraw(self, amount):
        if amount > self.balance:
            return 'Insufficient funds'
        self.balance = self.balance - amount
        return self.balance
```

我们计划实现一个活期账户 CheckingAccount：每次取款额外收取 1 美元的手续费，利率也更低

CheckingAccount 是 Account 的专门化，我们称 CheckingAccount 是 Account 的**子类（subclass）**，Account 是 CheckingAccount 的**基类（base class）**

子类继承基类的属性，但可以重写某些属性和方法。因此，在**继承**时，我们只写出子类和基类不一样的地方，剩下未写明的部分，会自动按基类的行为来

指定继承的方式，是把一个或多个求值为基类的表达式放进类名后的括号里

```python
class CheckingAccount(Account):
	
	withdraw_charge = 1
	interest = 0.01
	
	def withdraw(self, amount):
		return Account.withdraw(self, amount + self.withdraw_charge)
```

新定义了 手续费，修改了 利率 和 取款方法

这种重新定义的内容会引发名字的查找问题。此时，我们可以知道，点表达式查找的顺序如下：

1. 如果该名字是实例中的名字，就返回该实例中名字的值
2. 如果没有，则查找这个对象所属类中的名字，返回该类的名字
3. 如果没有，则查找这个类的基类中的名字，返回该基类名字的值

## 多重继承

子类可以从多个基类继承属性

```python
class SavingsAccount(Account):
	deposit_charge = 2
	def deposit(self, amount):
		return Account.deposit(self, amount - self.deposit_charge)
		
class AsSeenOnTVAccount(CheckingAccount, SavingsAccount):
	def __init__(self, account_holder):
		self.holder = account_holder
		self.balance = 1
```

```python
>>> such_a_deal = AsSeenOnTVAccount("John")
>>> such_a_deal.balance
1
>>> such_a_deal.deposit(20)
19
>>> such_a_deal.withdraw(5)
13
```

**C3 线性化算法**保证了一个原则：在方法解析顺序的链条中，任何一个父类只会出现一次，子类永远排在父类的前面

## 从零搭建的对象系统

如果放弃点表达式，我们可以用函数和字典实现同样的内容

### 前置内容

`callable()` 函数用于查询参数能否被调用（是函数、方法、类等等）

`*args` 将 args 这个元组拆开，将其中的元素一个个拿出来，平铺成位置参数传入

```python
def add_three(a, b, c):
    return a + b + c

add_three(1, 2, 3)

my_tuple = (1, 2, 3)
add_three(*my_tuple)
```

### 绑定器

首先要创建一个绑定工具

```python
def bind_method(value, instance):
	if callable(value):
		# 如果 value 是一个函数，我们返回一个新函数 method
		def method(*args):
			# 把 instance 当作 self 参数，连带传回
			return value(instance, *args)
		return method
	else:
		return value
```

### 实例的结构

我们使用绑定器制造一个实例，实例的本质是一个字典

```python
def make_instance(cls):
    # 实例自己的状态存在这个字典里
    attributes = {} 
    
    def get_value(name):
        if name in attributes:
            return attributes[name]
        else:
            # 去类里找
            value = cls['get'](name)
            # 如果是函数，需要绑定 self
            return bind_method(value, instance)
            
    def set_value(name, value):
        attributes[name] = value
        
    # 实例就是一个包含了 get 和 set 的字典
    instance = {'get': get_value, 'set': set_value}
    return instance
```

attributes 不用单独传回，它被 get_value 和 set_value 两个函数都包括在内

### 类生成器

```python
def make_class(attributes, base_class=None):
	
	def get_value(name):
		if name in attributes:
			return attributes[name]
		elif base_class is not None:
			return base_class['get'](name)
	
	def set_value(name, value):
		attributes[name] = value
	
	def new(*args):
		return init_instance(cls, *args)
	
	cls = {'get': get_value, 'set': set_value, 'new': new}
	return cls
```

### 实例的初始化器

```python
def init_instance(cls, *args):
	instance = make_instance(cls)
	init = cls['get']('__init__')
	if init:
		init(instance, *args)
	return instance
```

### 业务

```python
def make_account_class():
	def __init__(self, holder):
		self['set']('holder', holder)
		self['set']('balance', 0)
	def deposit(self, amount):
		self['set']('balance', self['get']('balance') + amount)
	return make_class({'__init__': __init__, 'deposit': deposit})
```