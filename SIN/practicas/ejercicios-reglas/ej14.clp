(deftemplate sensor
	(slot id)
	(slot estado)
)
(deffacts sensores
	(sensor(id 1)(estado correcto))
	(sensor(id 2)(estado incorrecto))
	(sensor(id 3)(estado correcto))
	(sensor(id 4)(estado correcto))
	(sensor(id 5)(estado correcto))
	(sensor(id 6)(estado correcto))
	(sensor(id 7)(estado correcto))
	(sensor(id 8)(estado incorrecto))
	(sensor(id 9)(estado incorrecto))
	(sensor(id 10)(estado incorrecto))
)
(defrule r-3-incorrectos
	(exists(sensor(id ?id1)(estado incorrecto))
	(sensor(id ?id2)(estado incorrecto))
	(sensor(id ?id3)(estado incorrecto))
	(test(<> ?id1 ?id2 ?id3)))
=>
	(printout t "Hay 3 o mas sensores en estado incorrecto" crlf)
)