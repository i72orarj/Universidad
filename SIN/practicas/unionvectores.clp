(deffacts sets
	(set1 1 3 5)
	(set2 3 7 8)
	(union)
)

(defrule r-union
	(or(set1 $? ?x $?)
		(set2 $? ?x $?))
	(not(union $? ?x $?))
	?h <- (union $?valores)
=>
	(retract ?h)
	(assert(union $?valores ?x))
)
