(deftemplate datos
	(slot val1 (type NUMBER))
	(slot val2 (type NUMBER))
)

(deffacts varios-datos
	(datos(val1 1)(val2 0))
	(datos(val1 5)(val2 5))
	(datos(val1 3)(val2 10))
	(datos(val1 2.5)(val2 8.1))
)

(defrule segundo-es-mayor
	(datos (val1 ?v1) (val2 ?v2))
	(test(> ?v2 ?v1))
=>
	(printout t ?v2 " es mayor que "?v1 crlf)

)
