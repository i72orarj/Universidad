(deffacts datos
	(dato 1)
	(dato 9)
	(dato 7)
	(dato 3)	
	(vector)
)


(defrule r-rellena
	?h1 <-(dato ?x)
	?h2 <- (vector $?a)
=>
	(retract ?h1)
	(retract ?h2)
	(assert(vector $?a ?x))
)

(defrule r-ordena-vector
	?h <- (vector $?a ?x ?y $?b)
	(test(> ?x ?y))
=>
	(retract ?h)
	(assert(vector $?a ?y ?x $?b))	
)

(defrule r-vector-ordenado
	(vector $?a)
	(exists
		(and	
			(vector $?a ?x ?y $?b)
			(test(< ?x ?y))
		)
	)
=>
	(assert(vector ordenado))
)

(defrule r-imprime-vector
	(vector $?a)
	(vector ordenado)
=>
	(printout t "El vector ya esta ordenado: "$?a crlf)










)