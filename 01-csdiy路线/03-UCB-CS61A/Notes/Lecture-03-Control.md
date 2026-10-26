# 控制流

## 控制流

语句不是表达式，没有值

控制语句根据逻辑比较的结果，控制程序的执行流程

可能被称为 if-statements

- **布尔逻辑**
	- 比较运算符
		- `<` `>` `!=` 等等
	- 逻辑运算符
		- and or not
	- 真值测试，被视作为 False 的
		- False
		- None
		- 0
		- 0.0
		- ""
		- []
		- {}

### **条件分支和循环**

```python
if <expression>:
    <suite>
elif <expression>:
    <suite>
else:
    <suite>
```

遇到第一个真值执行，跳过条件语句后续子句

```python
while <expression>:
	<suite>
```

每次对头值表达式求值，若为真，则执行语句

应当有终止状态（每次执行完应当改变某个变量）

### 短路

`<left> and <right>`

对左式求值，若为假则立即返回左式的值，否则返回右式的值

`<left> or <right>`

对左式求值，若为真则立即返回左式的值，否则返回右式的值

`not <expression>`

字面意思

**举例：**

```python
>>> 3 and 4
4
>>> 0 and 4
0
>>> 3 or 4
3
>>> 0 or 4
4
```

**应用：**

```python
name = input("Enter name: ") or "Anonymous"
port = config.get("port") or 8080

valid_name = user and user.name

created = create_file() and write_data() and send_notification()

result = is_valid and "Success" or "Failure"
```

1. 默认设置：当用户没有输入昵称时，快速进行默认输入
2. 默认设置：当字典取值为空时，快速给出默认值
3. 安全读取：如果 user 不存在，则在 user 处直接截断，不求值 user.name 而免除崩溃（否则有 AttributeError）
4. 程序的链式执行：一个做完后成功（返回真值）就做下一个
5. 模拟三元运算符（此时 and 和 or 中间的字面量必须为真值）