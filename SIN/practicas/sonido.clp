(defrule r-gallo " Sonido del gallo"
	(sonido kikiriki)
	=>
	(printout t "Se trata de un gallo"crlf)
)
(defrule r-perro " Sonido del perro"
	(sonido guau)
	=>
	(printout t "Se trata de un perro"crlf)
)
(defrule r-gato " Sonido del gato"
	(sonido miau)
	=>
	(printout t "Se trata de un gato"crlf)
)
(defrule r-pato " Sonido del pato"
	(sonido cuacua)
	=>
	(printout t "Se trata de un pato"crlf)
)
(defrule r-vaca " Sonido de la vaca"
	(sonido muuu)
	=>
	(printout t "Se trata de una vaca"crlf)
)
(defrule r-oveja " Sonido de la oveja"
	(sonido beee)
	=>
	(printout t "Se trata de un oveja"crlf)
)
