
# 题解

```c
#include <stdio.h>
int main(){
    int a,b;
    scanf("%d%d", &a, &b);
    printf("%d\n", a + b);
    return 0;
}
```

## 想说的话

你知道我要干什么。

### 高精度比较、加法、减法、乘法、开根（向下取整）

```c
#include <stdio.h>
#include <string.h>

typedef struct{
	int d[1001];
	int len;
} bigint;

bigint read_bigint(){
	bigint x = {{0}, 0};
	char s[1005];
	scanf("%s", s);
	int start = 0;
	while (s[start] == '0' && s[start + 1] != '\0')	start++;
	x.len = strlen(s + start);
	for (int i = x.len - 1; i >= 0; i--){
		x.d[i] = s[start + x.len - 1 - i] - '0';
	}
	return x;
}

void print_bigint(bigint x){
	for (int i = x.len - 1; i >= 0; i--){
		printf("%d", x.d[i]);
	}
	printf("\n");
}

int cmp(bigint a, bigint b){
	if (a.len != b.len){
		return a.len > b.len ? 1 : -1;
	}
	for (int i = a.len - 1; i >= 0; i--){
		if (a.d[i] != b.d[i]){
			return a.d[i] > b.d[i] ? 1 : -1;
		}
	}
	return 0;
}

bigint add(bigint a, bigint b){
	bigint c = {{0}, 0};
	int carry = 0;
	int max_len = a.len > b.len ? a.len : b.len;
	for (int i = 0; i < max_len || carry; i++){
		int sum = carry + (i < a.len ? a.d[i] : 0) + (i < b.len ? b.d[i] : 0);
		c.d[c.len++] = sum % 10;
		carry = sum / 10;
	}
	return c;
}

bigint sub(bigint a, bigint b){
	bigint c = {{0}, a.len};
	int borrow = 0;
	for (int i = 0; i < a.len; i++){
		int cur = a.d[i] - borrow;
		if (i < b.len){
			cur -= b.d[i];
		}
		if (cur < 0){
			cur += 10;
			borrow = 1;
		}
		else{
			borrow = 0;
		}
		c.d[i] = cur;
	}
	while (c.len > 1 && c.d[c.len - 1] == 0){
		c.len--;
	}
	return c;
}

bigint mul(bigint a, bigint b){
	bigint c = {{0}, a.len + b.len};
	for (int i = 0; i < a.len; i++){
		for (int j = 0; j < b.len; j++){
			c.d[i + j] += a.d[i] * b.d[j];
		}
	}
	for (int i = 0; i < c.len; i++){
		if (c.d[i] >= 10){
			c.d[i + 1] += c.d[i] / 10;
			c.d[i] %= 10;
		}
	}
	if (c.d[c.len] != 0){
		c.len++;
	}
	while (c.len > 1 && c.d[c.len - 1] == 0){
		c.len--;
	}
	return c;
}

bigint div2(bigint a){
	bigint c = {{0}, a.len};
	int rem = 0;
	for (int i = a.len - 1; i >= 0; i--){
		int cur = rem * 10 + a.d[i];
		c.d[i] = cur / 2;
		rem = cur % 2;
	}
	while (c.len > 1 && c.d[c.len - 1] == 0){
		c.len--;
	}
	return c;
}

bigint add1(bigint a){
	bigint c = a;
	c.d[0]++;
	int i = 0;
	while (c.d[i] >= 10){
		c.d[i] -= 10;
		i++;
		if (i >= c.len){
			c.len++;
		}
		c.d[i]++;
	}
	return c;
}

bigint sub1(bigint a){
	bigint c = a;
	c.d[0]--;
	int i = 0;
	while (i < c.len && c.d[i] < 0){
		c.d[i] += 10;
		c.d[i + 1]--;
		i++;
	}
	while (c.len > 1 && c.d[c.len - 1] == 0){
		c.len--;
	}
	return c;
}

bigint sqrt_bigint(bigint a){
	if (a.len == 1 && (a.d[0] == 0 || a.d[0] == 1)){
		return a;
	}
	bigint lo = {{1}, 1};
	bigint hi = {{0}, (a.len + 1) / 2 + 1};
	hi.d[hi.len - 1] = 1;
	bigint ans = lo;
	while (cmp(lo, hi) <= 0){
		bigint mid = div2(add(lo, hi));
		bigint sq = mul(mid, mid);
		int c = cmp(sq, a);
		if (c == 0){
			return mid;
		}
		else if (c < 0){
			ans = mid;
			lo = add1(mid);
		}
		else{
			hi = sub1(mid);
		}
	}
	return ans;
}
```

我拿上面的东西跑去写了P2293，TLE好几次给我急坏了，小查了一下才发现有压行的手法

```c
#include <stdio.h>
#include <string.h>
#define BASE 1000000000LL

typedef struct{
	long long d[250];
	int len;
} bigint;

bigint read_bigint(){
	bigint x = {{0}, 0};
	char s[1005];
	scanf("%s", s);
	int len = strlen(s);
	for (int i = len - 1; i >= 0; i -= 9){
		int l = i > 8 ? i - 8 : 0;
		long long pt = 0;
		for (int j = l; j <= i; j++){
			pt = pt * 10 + (s[j] - '0');
		}
		x.d[x.len++] = pt;
	}
	return x;
}

void print_bigint(bigint x){
	printf("%lld", x.d[x.len - 1]);
	for (int i = x.len - 2; i >= 0; i--){
		printf("%09lld", x.d[i]);
	}
	printf("\n");
}

int cmp(bigint a, bigint b){
	if (a.len != b.len){
		return a.len > b.len ? 1 : -1;
	}
	for (int i = a.len - 1; i >= 0; i--){
		if (a.d[i] != b.d[i]){
			return a.d[i] > b.d[i] ? 1 : -1;
		}
	}
	return 0;
}

bigint add(bigint a, bigint b){
	bigint c = {{0}, 0};
	long long carry = 0;
	int max_len = a.len > b.len ? a.len : b.len;
	for (int i = 0; i < max_len || carry; i++){
		long long sum = carry + (i < a.len ? a.d[i] : 0) + (i < b.len ? b.d[i] : 0);
		c.d[c.len++] = sum % BASE;
		carry = sum / BASE;
	}
	return c;
}

bigint sub(bigint a, bigint b){
	bigint c = {{0}, a.len};
	long long borrow = 0;
	for (int i = 0; i < a.len; i++){
		long long cur = a.d[i] - borrow;
		if (i < b.len){
			cur -= b.d[i];
		}
		if (cur < 0){
			cur += BASE;
			borrow = 1;
		}
		else{
			borrow = 0;
		}
		c.d[i] = cur;
	}
	while (c.len > 1 && c.d[c.len - 1] == 0){
		c.len--;
	}
	return c;
}

bigint mul(bigint a, bigint b){
	bigint c = {{0}, a.len + b.len};
	for (int i = 0; i < a.len; i++){
		for (int j = 0; j < b.len; j++){
			c.d[i + j] += a.d[i] * b.d[j];
			c.d[i + j + 1] += c.d[i + j] / BASE;
			c.d[i + j] %= BASE;
		}
	}
	if (c.d[c.len - 1] >= BASE){
		c.d[c.len] += c.d[c.len - 1] / BASE;
		c.d[c.len - 1] %= BASE;
	}
	if (c.d[c.len] != 0){
		c.len++;
	}
	while (c.len > 1 && c.d[c.len - 1] == 0){
		c.len--;
	}
	return c;
}

bigint div2(bigint a){
	bigint c = {{0}, a.len};
	long long rem = 0;
	for (int i = a.len - 1; i >= 0; i--){
		long long cur = rem * BASE + a.d[i];
		c.d[i] = cur / 2;
		rem = cur % 2;
	}
	while (c.len > 1 && c.d[c.len - 1] == 0){
		c.len--;
	}
	return c;
}

bigint add1(bigint a){
	bigint c = a;
	c.d[0]++;
	int i = 0;
	while (c.d[i] >= BASE){
		c.d[i] -= BASE;
		i++;
		if (i >= c.len){
			c.len++;
		}
		c.d[i]++;
	}
	return c;
}

bigint sub1(bigint a){
	bigint c = a;
	c.d[0]--;
	int i = 0;
	while (i < c.len && c.d[i] < 0){
		c.d[i] += BASE;
		c.d[i + 1]--;
		i++;
	}
	while (c.len > 1 && c.d[c.len - 1] == 0){
		c.len--;
	}
	return c;
}

bigint sqrt_bigint(bigint a){
	if (a.len == 1 && (a.d[0] == 0 || a.d[0] == 1)){
		return a;
	}
	bigint lo = {{1}, 1};
	bigint hi = {{0}, (a.len + 1) / 2 + 1};
	hi.d[hi.len - 1] = 1;
	bigint ans = lo;
	while (cmp(lo, hi) <= 0){
		bigint mid = div2(add(lo, hi));
		bigint sq = mul(mid, mid);
		int c = cmp(sq, a);
		if (c == 0){
			return mid;
		}
		else if (c < 0){
			ans = mid;
			lo = add1(mid);
		}
		else{
			hi = sub1(mid);
		}
	}
	return ans;
}
```

优化后可 AC 一小部分高精度计算