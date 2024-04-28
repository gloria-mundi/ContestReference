#include "../sparseTableDisjoint.cpp"

void test(int n) {
	vector<ll> values(n);
	for (ll &x: values) x = util::randint();
	DisjointST st;
	st.init(values);
	for (int i = 0; i < n; i++) {
		int l = util::randint(n);
		int r = util::randint(n);
		if (l > r) swap(l, r);
		r++;
		assert(
			st.query(l, r)
			==
			accumulate(values.begin()+l, values.begin()+r, 0ll)
		);
	}
}

int main() {
	test(1000);
	test(1);
}
