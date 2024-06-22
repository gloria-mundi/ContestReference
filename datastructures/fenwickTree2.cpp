vector<ll> add, mul;

void update(int l, int r, ll val) {
	for (int tl = l + 1; tl < ssize(add); tl += tl & -tl)
		add[tl] += val, mul[tl] -= val * l;
	for (int tr = r + 1; tr < ssize(add); tr += tr & -tr)
		add[tr] -= val, mul[tr] += val * r;
}

void init(vector<ll> &v) {
	mul.assign(size(v) + 1, 0);
	add.assign(size(v) + 1, 0);
	for(int i = 0; i < ssize(v); i++) update(i, i + 1, v[i]);
}

ll prefix_sum(int i) {
	ll res = 0;
	for (int ti = i; ti > 0; ti &= ti-1)
		res += add[ti] * i + mul[ti];
	return res;
}
