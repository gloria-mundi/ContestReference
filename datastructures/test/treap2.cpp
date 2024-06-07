#include "../treap2.cpp"

void test(int n) {
	Treap treap;
	vector<ll> dumb;
	for (int i = 0; i < n; i++) {
		assert(treap.getSize(treap.root) == ssize(dumb));
		int j = util::randint(ssize(dumb) + 1);
		ll x = util::randint();
		treap.insert(j, x);
		dumb.insert(begin(dumb) + j, x);
	}
	for (int i = 0; i < 5*n; i++) {
		assert(treap.getSize(treap.root) == ssize(dumb));
		{
			int j = util::randint(ssize(dumb));
			treap.remove(j);
			dumb.erase(begin(dumb) + j);
		}
		{
			int j = util::randint(ssize(dumb) + 1);
			ll x = util::randint();
			treap.insert(j, x);
			dumb.insert(begin(dumb) + j, x);
		}
	}
	for (int i = 0; i < n; i++) {
		assert(treap.getSize(treap.root) == ssize(dumb));
		int j = util::randint(ssize(dumb));
		treap.remove(j);
		dumb.erase(begin(dumb) + j);
	}
	assert(treap.root < 0);
	assert(empty(dumb));
}

int main() {
	test(1000);
	test(1);
	test(0);
}
