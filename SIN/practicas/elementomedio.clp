(deffacts vectores
	(vector v1 1 3 5)
	(vector v2 1 3 5 2)
	(vector v3 1 3 5 7 2 3)
	(vector v4 1 3 3 4 1 5 2)
	(vector v5 1 3 5 9)
	(vector v6 1 2 8 10)
)

(defrule r-medio
	(vector ?nombre $?a ?x $?b)
	(test(eq (length $?a) (length $?b)))
=>
	(printout t "El valor del elemento medio del vector "?nombre" es "?x crlf)
)
(defrule r-medio-media
	(vector ?nombre $?a ?x ?y $?b)
	(test(eq (length $?a) (length $?b)))
=>
	(printout t "La media de los valores del medio del vector "?nombre" es "(/ (+ ?x ?y) 2) crlf)
)