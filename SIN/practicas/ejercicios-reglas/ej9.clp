(deffacts datos
	(dato 1)
	(dato 2)
	(dato 3)
	(dato 4)
	(dato 5)
	(todos-los-datos)
)

(defrule r-todos
	?h1 <- (dato ?x)
	?h2 <- (todos-los-datos $?a)
=>
	(retract ?h1)
	(retract ?h2)
	(assert(todos-los-datos $?a ?x))
)

