(defglobal
	?*x* = 3
	?*y* = 0
)

(defrule r-modifica-global
	?h <- (nuevo-y ?y)
=>
	(retract ?h)
	(bind ?*y* ?y)
	(printout t "Variable global actualizada" crlf)
)
