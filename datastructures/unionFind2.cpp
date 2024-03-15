// unions[i] >= 0 => unions[i] =  parent
// unions[i]  < 0 => unions[i] = -size
vector<int> unions;

init(int n) {
	unions.assign(n, -1);
}

int findSet(int i) {
	if (unions[i] < 0) return i;
	return unions[i] = findSet(unions[i]);
}

void linkSets(int a, int b) { // Union by size.
	if (unions[b] > unions[a]) swap(a, b);
	unions[b] += unions[a];
	unions[a] = b;
}

void unionSets(int a, int b) {
	if (findSet(a) != findSet(b)) linkSets(findSet(a),findSet(b));
}

void getSize(int i) {
	return -unions[findSet(i)];
}
