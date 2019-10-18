(deffacts sonidos
	(sonido-animal gato miau)
	(sonido-animal perro guau)
	(sonido-animal gallo kikiriki)
	(sonido-animal pajaro piopio)
)

(defrule r-busca-por-sonido
	(sonido ?s)
	(sonido-animal ?a ?s)
=>
	(printout t "El " ?a " hace " ?s crlf)
)