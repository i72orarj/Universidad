(defrule r-elimina-numero-uno
	?h <- (datos $?a ?x $?b)
	(test(= ?x 1))
=>
	(retract ?h)
	(assert(datos $?a $?b))
)