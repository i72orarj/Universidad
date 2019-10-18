(deftemplate paciente "Datos paciente"
	(slot nombre (type STRING)(default ?NONE) )
	(slot apellidos(type STRING)(default ?NONE))
	(slot dni (type SYMBOL)(default 12345678A))
	(slot seguro-medico(type SYMBOL)(default Ninguna))
)

(deffacts pacientes
	(paciente 
		(nombre "miguel")
		(apellidos "muñoz")
		(dni 11111111X)
		(seguro-medico Si)	
		)

)

(deftemplate visita "Datos visita medico"
	(slot fecha (type SYMBOL)(default ?NONE))
	(slot paciente (type STRING)(default "Desconocido"))
	(slot sintomas (type STRING)(default ?NONE))
	(slot pruebas (type STRING) (default "Ninguna"))
	(slot medicacion (type STRING)(default "Ninguna"))
)

(deffacts visitas
	(visita
		(fecha 27/02/2019)
		(paciente "Miguel Muñoz")
		(sintomas "Tose mucho y no para")
		(pruebas "Basicas")
		(medicacion "unos caramelos")
	)
)