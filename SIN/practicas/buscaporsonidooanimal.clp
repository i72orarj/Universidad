(deffacts sonidos
	(sonido-animal gato miau)
	(sonido-animal perro guau)
	(sonido-animal gallo kikiriki)
	(sonido-animal pajaro piopio)
)

(defrule r-busca-sonido-o-animal
	(sonido-animal ?a ?s)
	(or (sonido ?s) (animal ?a))
=> 
	(printout t "El "?a" hace "?s crlf)
)