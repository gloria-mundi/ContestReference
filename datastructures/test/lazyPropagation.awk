
/Neutral element for combine/ {
	print "#ifndef SEGTREE_FIRST_NEG"
	print "# ifndef SEGTREE_MAX"
	print
	print "# else"
	tmp = $0
	sub(/0/, "numeric_limits<T>::min()", tmp)
	print tmp
	print "# endif"
	print "#else"
	sub(/0/, "numeric_limits<T>::max()")
	print
	print "#endif"
	next
}

/Modify this \+ E/ {
	print "#ifndef SEGTREE_FIRST_NEG"
	print "# ifndef SEGTREE_MAX"
	print
	print "# else"
	tmp = $0
	sub(/a \+ b/, "max(a, b)", tmp)
	print tmp
	print "# endif"
	print "#else"
	sub(/a \+ b/, "a < 0 ? a : min(a, b)")
	print
	print "#endif"
	next
}

/Unused value by updates/ {
	print "#ifndef SEGTREE_FIRST_NEG"
	print
	print "#else"
	sub(/0/, /numeric_limits<U>::max()/)
	print
	print "#endif"
	next
}

/And this \+ UF/ {
	print
	getline set_tree
	getline set_lazy
	print "#ifndef SEGTREE_MAX"
	print "# ifndef SEGTREE_FIRST_NEG"
	print set_tree
	print "# else"
	tmp = set_tree
	sub(/val \* k\[i\]/, "val", tmp)
	print tmp
	print "# endif"
	print set_lazy
	print "#else"
	sub(/= val \* k\[i\]/, "+= val", set_tree)
	sub(/= val/, "+= val", set_lazy)
	print set_tree
	print set_lazy
	print "#endif"
	next
}

/Optional/ { print "#ifdef SEGTREE_MAX" }
/^\};$/ { print "#endif" }

/SegTree\(const vector<T>& a\)/ {
	print "#ifndef SEGTREE_INIT_DEFAULT"
	print
	print "#else"
	getline
	sub(/\/\//, "")
	print
	print "#endif"
	getline
	print
	print "#ifndef SEGTREE_INIT_DEFAULT"
	getline
	print
	print "#endif"
	next
}

{ print }
