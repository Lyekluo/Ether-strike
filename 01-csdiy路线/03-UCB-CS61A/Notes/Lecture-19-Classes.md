# 类

```python
class Student:
    def __init__(self, name: str, in_mega: bool):
        self.name = name
        
        self.discussion_points = 0
        if in_mega:
            self.discussion_points = 10
        
        self.mt2_points = 0
        self.a_plus_points = 0

    def total_points(self):
        return self.discussion_points + self.mt2_points


def create_students(regular: list[str], mega: list[str]) -> dict[str, Student]:
    # 用字典推导式批量创建所有 regular 列表里的学生实例
    result = {name: Student(name, False) for name in regular}
    
    # 用 for 循环追加 mega 列表里的学生实例
    for name in mega:
        result[name] = Student(name, True)
        
    return result

# 测试
regular_list = ["Daniel", "Darren", "Peyton"]
mega_list = ["Terry", "Tejas"]

students_dict = create_students(regular_list, mega_list)

print("Daniel (regular) 的讨论课分数:", students_dict["Daniel"].discussion_points) 
# 0

print("Terry (mega) 的讨论课分数:", students_dict["Terry"].discussion_points)    
# 10

print("Darren 的总分 (discussion + mt2):", students_dict["Darren"].total_points()) 
# 0
```

上面那个创建学生实例可以不这么写，有如下几种解法

```python
result = {name: Student(name, name in mega) for name in regular + mega}
```

```python
result = (
	{name: Student(name, False) for name in regular} |
	{name: Student(name, True) for name in mega}
)
```

其中加入括号可以使表达式随便换行