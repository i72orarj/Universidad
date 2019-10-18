(deffacts vectores
	(vector vA 1 2 3 4)
	(vector vB 7 5 1 3)
	(vector vC 0 8 4 5 3)
)

(defrule r-ordenar-vector
	?h <-(vector ?n $?a ?x ?y $?b)
	(test(> ?x ?y))	
=>	
	(retract ?h)
	(assert(vector ?n $?a ?y ?x $?b))
)