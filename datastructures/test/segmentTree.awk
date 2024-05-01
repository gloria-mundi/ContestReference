
/Neutral element for combine/ {
	print "#ifndef SEGTREE_MUL"
	print "# ifndef SEGTREE_FIRST_NEG"
	print
	print "# else"
	tmp = $0
	sub(/0/, "numeric_limits<ll>::max()", tmp)
	print tmp
	print "# endif"
	print "#else"
	sub(/0/, "1")
	print
	print "#endif"
	next
}

/modify this \+ neutral/ {
	print "#ifndef SEGTREE_MUL"
	print "# ifndef SEGTREE_FIRST_NEG"
	print
	print "# else"
	tmp = $0
	sub(/a \+ b/, "a < 0 ? a : min(a, b)", tmp)
	print tmp
	print "# endif"
	print "#else"
	sub(/a \+ b/, "a*b % MOD")
	print
	print "#endif"
	next
}

/SegTree\(vector<T>& a\)/ {
	print "#ifndef SEGTREE_INIT_DEFAULT"
	print
	getline
	print
	print "#else"
	getline
	sub(/\/\//, "")
	print
	getline
	sub(/\/\//, "")
	print
	print "#endif"
	next
}

/remove for range update/ {
	print "#ifndef SEGTREE_RANGE_UPDATE"
	print
	getline
	print
	getline
	print "\t\t}"
	print "#endif"
	print "\t}"
	next
}

/void update/ {
	print "#ifndef SEGTREE_RANGE_UPDATE"
}

/OR: range update/ {
	print "#else"
}

/^\};$/ {
	print "#endif"
}

{ print }
