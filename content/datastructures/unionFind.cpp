struct UnionFind {
	vector<int> unions; // unions[i] = parent or unions[i] = -size

	UnionFind(int n): unions(n, -1) {}

	int find(int a) {
		return unions[a] < 0 ? a : unions[a] = find(unions[a]);
	}

	bool link(int a, int b) {
		if ((a = find(a)) == (b = find(b))) return false;
		if (unions[b] > unions[a]) swap(a, b);
		unions[b] += unions[a];
		unions[a] = b;
		return true;
	}

	int size(int a) {
		return -unions[find(a)];
	}

	int add() {
		unions.push_back(-1);
		return ssize(unions) - 1;
	}
};
