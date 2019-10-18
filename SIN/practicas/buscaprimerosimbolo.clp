(deffacts vectores
	(vector 1 2 3 4 5 6 7)
	(vector rojo 6 0)
	(vector "falkj faji")
)

(defrule r-busca-primero-simbolo
	?h <-(vector ?x&:(symbolp ?x) $?)
=>
	(printout t "En el hecho "?h " lo primero es un symbol" crlf)


)