(deffacts sonidos
	(sonido-animal gato miau)
	(sonido-animal perro guau)
	(sonido-animal gallo kikiriki)
	(sonido-animal pajaro piopio)
)

(defrule r-sonido-animal
	(sonido-animal ?animal ?sonido)
	=>
	(printout t "El " ?animal " hace " ?sonido crlf)
)