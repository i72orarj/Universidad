(defrule r-insertar
	?p<-(pila $?valores)
	?v<-(push ?x)
=>
	(retract ?p)
	(retract ?v)
	(assert(pila ?x $?valores))
	(printout t "Valor insertado: "?x crlf)
)

(defrule r-extraer
	?p<-(pila ?x $?valores)
	?v<-(pop)
=>
	(retract ?p)
	(retract ?v)
	(assert(pila $?valores))
	(printout t "Valor eliminado: "?x crlf)
)

(defrule r-iniciar-pila
	(not(pila $?valores))
=>
	(assert(pila))
)