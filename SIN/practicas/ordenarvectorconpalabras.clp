(deffacts vectores
	(vector vA 6 5 sin 4 3 1)
	(vector vB 3 -1 4 2 bug 0.1)
	(vector vC -23)
)

(defrule r-ordena
	?h <-(vector ?nombre $?a ?x $?b ?y $?c)
	(test(numberp ?x))
	(test(numberp ?y))
	(test(> ?x ?y))
=>
	(retract ?h)
	(assert(vector ?nombre $?a ?y ?x $?b $?c))	
)
