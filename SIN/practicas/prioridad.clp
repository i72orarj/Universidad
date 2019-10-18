(defrule primera
	(declare(salience 10))
	=>
	(printout t "Me ejecuto la primera" crlf)
)

(defrule segunda

=>
(printout t "Me ejecuto la segunda" crlf)
)