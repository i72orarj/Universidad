(deftemplate emergencia
	(slot tipo)
	(slot ubicacion)
)

(deftemplate equipo-bomberos
	(slot nombre)
	(slot ubicacion)
)

(deffacts datos
	(emergencia(tipo fuego)(ubicacion "Vial-42"))
	(equipo-bomberos (nombre "AXZ")(ubicacion "Vial-42"))
	(emergencia(tipo fuego)(ubicacion "Los Pedroches"))
	(emergencia (tipo gato-en-arbol)(ubicacion "Los Pedroches"))
)

(defrule r-fuegos-controlados
	(emergencia(tipo fuego)(ubicacion ?n)); el forall se activa aunque no hay tipo fuego, con esto anulas eso
	(forall (emergencia(tipo fuego)(ubicacion ?n))
		(equipo-bomberos(nombre ?x)(ubicacion ?n))
	)
=>
	(printout t "Todos los fuegos estan controlados" crlf)
)