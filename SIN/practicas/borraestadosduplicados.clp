(deftemplate estado
	(slot id(type INTEGER)(range 0 10000000000))
	(slot s1(type INTEGER)(range 0 3))
	(slot s2(type INTEGER)(range 0 4))	
)

(deffacts datos
	(estado(id 1)(s1 2)(s2 1))
	(estado(id 2)(s1 3)(s2 2))
	(estado(id 3)(s1 2)(s2 1))
	(estado(id 4)(s1 2)(s2 4))
	(estado(id 5)(s1 2)(s2 1))
	(estado(id 6)(s1 2)(s2 4))
)


(defrule r-elimina-repetidos
	(estado(id ?n1)(s1 ?x)(s2 ?y))
	?h <- (estado(id ?n2)(s1 ?x)(s2 ?y))
	(test(neq ?n1 ?n2))
=>	
	(retract ?h)
	(printout t "Eliminando "?h2" que esta repetido" crlf)

)