(deffacts sonidos-animales
	(sonido kikiriki)
	(sonido guau)
	(sonido miau)
)

(defrule r-sonido-gallo
	(sonido kikiriki)
=>
	(printout t "Se trata de un gallo" crlf)
)

(defrule r-sonido-perro
	(sonido guau)
=>
	(printout t "Se trata de un perro" crlf)
)

(defrule r-sonido-gato
	(sonido miau)
=>
	(printout t "Se trata de un gato" crlf)
)