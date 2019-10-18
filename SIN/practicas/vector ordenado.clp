(deffacts vectores
	(vector v1 2 2 3 8 9)
	(vector v2 1 3 2 8 7)
	(vector v3 1 2 2 8 8 5)
)


(defrule r-imprime-no-ordenado
	(vector ?n $?)
	(exists
		(and	
			(vector ?n $? ?x ?y $?)
			(test(> ?x ?y))
		)
	)
=>
	(printout t "El vector " ?n " no esta ordenado" crlf )
)