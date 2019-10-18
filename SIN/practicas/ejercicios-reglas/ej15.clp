(deftemplate planta
	(slot tolerancia-frio)
	(slot tolerancia-sombra)
	(slot tolerancia-climaseco)
)
(deftemplate caractetisticas-deseadas
	(slot tolerancia-frio)
	(slot tolerancia-sombra)
	(slot tolerancia-climaseco)
)

(deffacts plantas
	(planta(tolerancia-frio 0)(tolerancia-sombra 100)(tolerancia-climaseco 50))
	(planta(tolerancia-frio 10)(tolerancia-sombra 90)(tolerancia-climaseco 100))
	(planta(tolerancia-frio 20)(tolerancia-sombra 80)(tolerancia-climaseco 50))
	(planta(tolerancia-frio 30)(tolerancia-sombra 70)(tolerancia-climaseco 100))
	(planta(tolerancia-frio 40)(tolerancia-sombra 60)(tolerancia-climaseco 50))
	(planta(tolerancia-frio 50)(tolerancia-sombra 50)(tolerancia-climaseco 100))
	(planta(tolerancia-frio 60)(tolerancia-sombra 40)(tolerancia-climaseco 50))
	(planta(tolerancia-frio 70)(tolerancia-sombra 30)(tolerancia-climaseco 100))
)



(defrule r-buscar-plantas 
	?h <- (planta (tolerancia-frio ?tf)(tolerancia-sombra ?ts)(tolerancia-climaseco ?tc))
	(caractetisticas-deseadas(tolerancia-frio ?tf)(tolerancia-sombra ?ts)(tolerancia-climaseco ?tc))
=>
	(printout t "Se ha encontrado la planta "?h crlf)
	
)