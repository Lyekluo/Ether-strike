# 树形递归

- 斐波那契数列
- 分割数方法数

函数在递归时调用自己不止一次，此时它的函数定义解法在可读性已经远胜于任何的迭代方案

> [!NOTE] **快速回忆分割数方案的计算：**
> - 我们用不超过 m 的正整数分割 n 的方法数
> 	- 用不超过 m 的正整数分割 n - m 的方法数
> 	- 用不超过 m - 1 的正整数分割 n 的方法数
> - 基准情况
> 	- 0 被分割的方法数为 1（触底标记）
> 	- 小于 0 的数被分割的方法数为 0
> 	- 用 0 或小于 0 的数分割的方法数为 0
> - 本质：判断分割方案是否包含 m

**警惕重复计算带来的性能缺陷**

后续会存在记忆化或者是`@lru_cache`的解决方案：将算过的结果存在字典中，下次使用直接查表，斐波那契时间复杂度降为线性

```python
from functools import lru_cache

@lru_cache(maxsize=None) 
def fib(n):
    if n <= 2: return 1
    return fib(n-1) + fib(n-2)

print(fib(100))
```

**每条路径是否都有 return？**

**例1** 最长求和子列

```python
def longest(s: list[int], n: int) -> list[int] | None:
	"""Return the longest sublist of s that sums to n, or None if none exists
	"""
	if len(s) == 0:
		if n == 0:
			return []
		else:
			return None
	minus_first = longest(s[1:], n - s[0])
	without_first = longest(s[1:], n)
	if isinstance(minus_first, list):
		with_first = [s[0]] + minus_first
		if isinstance(without_first, list):
			return max(with_first, without_first, key = len)
		else:
			return with_first
	else:
		return without_first
```

我们将潜在的最长求和子列分为有 **第 0 个元素** 和 **没有第 0 个元素** 的两种最长求和子列，取其中长度最大者

当列表长为 0 时，下一层子列已经不存在，无法分配元素，只能展开求和的 n 是否为 0 的分类讨论。
- 若为 0 则说明 n 刚好被分配完，方案存在，返回空列表 `[]` 
- 若不为 0 ，则说明 n 被错误分配，方案不存在，返回 `None`

而要得到次级的子链，要使次级进行相同的递归操作，如此继续下去将遍历数列中的所有元素

接下来我们只需要相信下一层递归已经返回正确结果，将其逐级向上合并即得