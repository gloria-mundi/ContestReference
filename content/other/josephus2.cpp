ll rotateLeft(ll n) { // Der letzte Überlebende, 0-basiert.
	int bits = __lg(n);
	n ^= 1ll << bits;
	return n << 1;
}
