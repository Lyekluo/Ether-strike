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

我们计划让这个类定义的对象

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