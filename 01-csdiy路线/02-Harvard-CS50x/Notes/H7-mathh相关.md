
**宏**

- INFINITY 正无穷大
- NAN 非数 Not a Number

**函数**

- 绝对值
	- fabs 浮点绝对值
- 取整
	- ceil 向上取整
	- floor 向下取整
	- trunc 向零取整
	- round 四舍五入远离 0
	- lround 四舍五入返回 long
	- llround 四舍五入返回 long long
- 取余数
	- fmod 浮点数取模
	- remainder 舍入余数
- 幂
	- pow 浮点幂
	- sqrt 平方根
	- cbrt 立方根
	- hypot 斜边
- 指对
	- exp
	- exp2
	- log
	- log2 
	- log10
- ？
	- fma 先乘后加
	- fmax
	- fmin
- 三角函数
	- sin
	- cos
	- tan
	- asin
	- acos
	- atan
	- atan2 旋转角
	- sinh
	- cosh
	- tanh
- 检查
	- isnan 是否非数
	- isinf 是否无穷大
	- isfinite 是否有限

### 宏与特殊状态

```c
#include <math.h>

double a = 1.0 / 0.0; // INFINITY
double b = 0.0 / 0.0; // NAN
```

NAN 不能用于做相等判断，`NAN != NAN`

### fabs

```c
double res = fabs(-3.14); // 3.14
```

fabs 专用于 C 语言即可

### ceil / floor / trunc / round

```c
double c = ceil(3.14); // 4.0
double c2 = ceil(-3.14); // -3.0
double f = floor(3.14); // 3.0
double f2 = floor(-3.14); // -4.0
double t = trunc(3.14); // 3.0
double t2 = trunc(-3.14); // -3.0
double r = round(3.5); // 4.0
double r2 = round(-3.5); // -4.0

long l = lround(3.5); // 4L
long long ll = llround(3.5); // 4LL
```

ceil 的分数形式 $\lceil\frac{a}{b}\rceil$ 推荐写成 `(a + b - 1) / b`

### fmod / remainder

```c
double m1 = fmod(5.5, 2.0); // 1.5
double m2 = remainder(5.5, 2.0); // -0.5
```

fmod 的结果符号与被除数相同，remainder 取的是到最近倍数距离

浮点整除判断：

```c
const double EPS = 1e-9;
if (fabs(fmod(a, b)) < EPS);
```

### pow / sqrt / cbrt / hypot

```c
double p = pow(2.0, 3.0); // 8.0
double s = sqrt(16.0); // 4.0
double c = cbrt(27.0); // 3.0
double h = hypot(3.0, 4.0); // 5.0
```

**禁止使用 pow 计算整数幂，请手写快速幂**

### exp / exp2 / log / log2 / log10

```c
double e = exp(1.0); // 2.718282
double l = log(e); // 1.0
double l2 = log2(8.0); // 3.0
double l10 = log10(100.0); // 2.0
```

剩下没有的用换底公式，高一知识

$log_{a}(b) = \frac{ln b}{ln a}$

### fma / fmax / fmin

```c
double res = fma(2.0, 3.0, 4.0); // 10.0
double max = fmax(3.14, 2.71); // 3.14
double min = fmin(3.14, 2.71); // 2.71
```

fma 的公式是 a * b + c，精度相较于直接表达式更高

### 三角

```c
double rad = 30.0 * (3.1415926535 / 180.0);
double s = sin(rad); // 0.5
double a = atan2(1.0, 1.0); // 0.785398
```

三角函数中的角度都是弧度

atan2 函数的物理意义是 向量的方向相对于x轴正半轴转过的角度，范围是 $-\pi$ 到 $\pi$

**适用于极角计算和极角排序**

### isnan / isinf / isfinite

```c
double a = 0.0 / 0.0;
if (isnan(a)){
	printf("NaN\n");
}

double b = 1.0 / 0.0;
if (isinf(b)){
	printf("inf\n");
}

double c = 3.14;
if (isfinite(c)){
	printf("num\n");
}
```

```text
NaN
inf
num
```
