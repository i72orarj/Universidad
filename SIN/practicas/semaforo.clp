(defrule r-puedo-pasar
	(logical(semaforo verde))
=>
	(assert (puedo pasar))
)