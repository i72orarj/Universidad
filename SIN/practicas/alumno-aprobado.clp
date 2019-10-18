(defrule todos-limpios
	(forall (estudiante ?n)
			(lengua ?n)
			(matematicas ?n)
			(historia ?n)
	)
	=>
	(printout t "Todos limpios" crlf)
)
	
(deffacts estudiantes
	(estudiante herminio)
	(lengua herminio)
	(matematicas herminio)
	(historia herminio)
)