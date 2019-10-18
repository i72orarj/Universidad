(defrule r-busca-5
	?h <- (vector $? 5 $?)
=>
	(printout t "He encontrado un 5 en: "?h crlf)
)

(deffacts vectores
	(vector 1 2 3 4 5 6 7)
	(vector -1 6 0)
	(vector 5)
)