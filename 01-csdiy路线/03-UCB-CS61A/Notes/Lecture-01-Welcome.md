
- Values 值
- Operators 运算符
- Expressions 表达式（包括值和运算符）
	- 字面量、名称、调用

表达式描述一个计算过程并产生一个值

所有的表达式都能写成调用表达式（Call Expression）
```python
max(1 + 1, 3)
(lambda x: x + 1)(2)
```

嵌套表达式：先求操作符，再**从左到右**求每一个操作数，将函数应用到这些值上，递归执行