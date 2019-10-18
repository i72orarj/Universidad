(defglobal
	?*x* = 3
	?*y* = 0
)

(deffatcts datos
	(dato 34)
	(dato 32)
	(dato 9)
)

(defrule r-comprueba
	(dato ?p)
	(test(= ?p (* 3 ?*x*)))
=>
	(printout t "La variable global vale: " ?*x* crlf)
	(printout t "El dato encontrado vale: " ?p crlf)
	
)