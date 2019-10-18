(deffacts vectores
	(vector v1 9 4 4 9)
	(vector v2 1 2 3 4 5)
	(vector v3 2 5 1 5 2)
)

(defrule r-comprueba-asimetria
	(vector ?nombre ?x $?a ?y)
	(test(<> ?x ?y))
=>
	(printout t "El vector " ?nombre " no es simetrico" crlf)

)

(defrule r-comprueba-extremos
	?h <- (vector ?nombre ?x $?a ?y)
	(test(= ?x ?y))
=>
	(retract ?h)
	(assert(vector ?nombre $?a))
)

(defrule r-comprueba-simetria ;mejor la segunda opcion
	(vector ?nombre $?a)
	(or(test(eq (length $?a) 0))
		(test(eq (length $?a) 1)))

=>
	(printout t "El vector " ?nombre " es simetrico" crlf)

)
;la siguiente es la del profesor
(defrule r-comprueba-simetria
	(or(vector ?nombre ?)
		(vector ?nombre ))
=>
	(printout t "El vector " ?nombre " es simetrico" crlf)

)
