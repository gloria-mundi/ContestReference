#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template<typename T>
T _lg_check(T n) {
	assert(n > 0);
	return __lg(n);
}

#define __lg _lg_check

namespace util {

mt19937 rd(0);

int randint(int l, int r) {
	assert(l <= r);
	return uniform_int_distribution<int>(l, r)(rd);
}

int randint(int x) {
	assert(x > 0);
	return randint(0, x-1);
}

int randint() {
	return randint(-1'000'000, +1'000'000);
}

}
