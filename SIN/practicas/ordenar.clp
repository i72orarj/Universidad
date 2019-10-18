;imprimir ordenados

(deffacts numeros
	(dato 6)
	(dato 1.3)
	(dato 2)
	(dato -1)
	(dato 5)
	(dato 3)
)


(defrule r-ordena-numeros
	?h <- (dato ?x)
	(not(dato ?y&:(< ?y ?x)))
=>
	(retract ?h)
	(printout t ?x crlf)
)
