; Sistema de ayuda a la decisión para: Comprar un vehículo.

;Dadas las características de un vehículo que el usuario desea comprar (como por ejemplo: plazas, puertas, CV, precio, etc.),
;indicar al usuario cual (o cuales) serían los vehículos disponibles que mejor se ajustan a lo que busca.
;El número mínimo de características a considerar debe ser 5, y el número de vehículos diferentes debe ser de 25.

;preguntar al principio por rango de precio, tipo y combustible

(deftemplate coche
	(slot tipo (type SYMBOL))  	;deportivo,familiar,turismo,suv
	(slot tipo_punt(type SYMBOL)(default no))
	(slot marca (type SYMBOL))  	;bmw,audi,mercedes,ford,skoda,peugeot,renault
	(slot marca_punt(type SYMBOL)(default no))
	(slot modelo(type STRING))
	(slot precio (type NUMBER)) 	;mayor que 0
	(slot precio_punt(type SYMBOL)(default no))
	(slot puertas (type INTEGER)(allowed-integers 2 3 4 5)); solo es posible 2 3 4 o 5
	(slot plazas (type INTEGER)(allowed-integers 2 5 7))  ; 2 5 7
	(slot caballos (type INTEGER))     ;mayor que 0
	(slot combustible (type SYMBOL)) ;gasolina,diesel,hibrido
	(slot combustible_punt(type SYMBOL)(default no))
	(slot puntuacion (type INTEGER))
)

(deffacts coches
	(coche (tipo deportivo)(marca BMW)(modelo "i8 Coupe")(precio 145000)(puertas 3)(plazas 2)(caballos 374)(combustible hibrido)(puntuacion 0))
	(coche (tipo turismo)(marca BMW)(modelo "Serie 1")(precio 27000)(puertas 5)(plazas 5)(caballos 109)(combustible gasolina)(puntuacion 0))
	(coche (tipo familiar)(marca BMW)(modelo "Serie 2 Grand Tourer")(precio 26000)(puertas 5)(plazas 7)(caballos 116)(combustible diesel)(puntuacion 0))
	(coche (tipo familiar)(marca BMW)(modelo "Serie 2 Grand Tourer")(precio 24000)(puertas 5)(plazas 7)(caballos 140)(combustible gasolina)(puntuacion 0))
	(coche (tipo suv)(marca BMW)(modelo "x1")(precio 30000)(puertas 5)(plazas 5)(caballos 140)(combustible gasolina)(puntuacion 0))
	(coche (tipo suv)(marca Audi)(modelo "x1")(precio 30000)(puertas 5)(plazas 5)(caballos 140)(combustible gasolina)(puntuacion 0))
	(coche (tipo turismo)(marca Audi)(modelo "A7")(precio 51500)(puertas 5)(plazas 5)(caballos 204)(combustible diesel)(puntuacion 0))
	(coche (tipo deportivo)(marca Audi)(modelo "TT")(precio 33500)(puertas 2)(plazas 2)(caballos 245)(combustible gasolina)(puntuacion 0))
	(coche (tipo suv)(marca Mercedes)(modelo "GLE")(precio 60000)(puertas 5)(plazas 5)(caballos 245)(combustible diesel)(puntuacion 0))
	(coche (tipo familiar)(marca Mercedes)(modelo "GLS")(precio 88000)(puertas 5)(plazas 5)(caballos 333)(combustible gasolina)(puntuacion 0))
	(coche (tipo turismo)(marca Mercedes)(modelo "Clase A")(precio 30000)(puertas 5)(plazas 5)(caballos 150)(combustible diesel)(puntuacion 0))
	(coche (tipo turismo)(marca Mercedes)(modelo "Clase C")(precio 50000)(puertas 5)(plazas 5)(caballos 190)(combustible hibrido)(puntuacion 0))
	(coche (tipo deportivo)(marca Mercedes)(modelo "AMG GT Coupe")(precio 191800)(puertas 3)(plazas 2)(caballos 557)(combustible gasolina)(puntuacion 0))
	(coche (tipo deportivo)(marca Mercedes)(modelo "AMG GT Roadster")(precio 150000)(puertas 3)(plazas 2)(caballos 476)(combustible gasolina)(puntuacion 0))
	(coche (tipo deportivo)(marca Ford)(modelo "Mustang")(precio 41500)(puertas 3)(plazas 2)(caballos 290)(combustible gasolina)(puntuacion 0))
	(coche (tipo turismo)(marca Ford)(modelo "Fiesta")(precio 8300)(puertas 3)(plazas 5)(caballos 70)(combustible gasolina)(puntuacion 0))
	(coche (tipo turismo)(marca Ford)(modelo "Fiesta")(precio 13800)(puertas 5)(plazas 5)(caballos 85)(combustible diesel)(puntuacion 0))
	(coche (tipo suv)(marca Ford)(modelo "Kuga")(precio 19300)(puertas 5)(plazas 5)(caballos 120)(combustible diesel)(puntuacion 0))
	(coche (tipo familiar)(marca Ford)(modelo "Mondeo")(precio 32400)(puertas 5)(plazas 5)(caballos 150)(combustible diesel)(puntuacion 0))
	(coche (tipo familiar)(marca Ford)(modelo "Nuevo Mondeo")(precio 36800)(puertas 5)(plazas 5)(caballos 135)(combustible hibrido)(puntuacion 0))
	(coche (tipo turismo)(marca Ford)(modelo "KA+")(precio 7700)(puertas 5)(plazas 5)(caballos 70)(combustible gasolina)(puntuacion 0))
	(coche (tipo turismo)(marca Skoda)(modelo "Fabia")(precio 8500)(puertas 5)(plazas 5)(caballos 75)(combustible gasolina)(puntuacion 0))
	(coche (tipo turismo)(marca Skoda)(modelo "Fabia")(precio 10000)(puertas 5)(plazas 5)(caballos 95)(combustible gasolina)(puntuacion 0))
	(coche (tipo familiar)(marca Skoda)(modelo "Kodiaq")(precio 21000)(puertas 5)(plazas 5)(caballos 150)(combustible gasolina)(puntuacion 0))
	(coche (tipo suv)(marca Skoda)(modelo "Karoq")(precio 17600)(puertas 5)(plazas 5)(caballos 115)(combustible gasolina)(puntuacion 0))
	(coche (tipo suv)(marca Skoda)(modelo "Karoq")(precio 24000)(puertas 5)(plazas 5)(caballos 150)(combustible diesel)(puntuacion 0))
	(coche (tipo suv)(marca Peugeot)(modelo "5008")(precio 21700)(puertas 5)(plazas 5)(caballos 130)(combustible gasolina)(puntuacion 0))
	(coche (tipo suv)(marca Peugeot)(modelo "2008")(precio 14700)(puertas 5)(plazas 5)(caballos 100)(combustible diesel)(puntuacion 0))
	(coche (tipo familiar)(marca Peugeot)(modelo "Traveller")(precio 21700)(puertas 4)(plazas 7)(caballos 120)(combustible diesel)(puntuacion 0))
	(coche (tipo turismo)(marca Peugeot)(modelo "208")(precio 9200)(puertas 5)(plazas 5)(caballos 82)(combustible hibrido)(puntuacion 0))
	(coche (tipo turismo)(marca Renault)(modelo "Zoe")(precio 21200)(puertas 5)(plazas 5)(caballos 109)(combustible hibrido)(puntuacion 0))
	(coche (tipo familiar)(marca Renault)(modelo "Kangoo")(precio 11500)(puertas 3)(plazas 5)(caballos 90)(combustible hibrido)(puntuacion 0))
	(coche (tipo suv)(marca Renault)(modelo "Captur")(precio 11500)(puertas 5)(plazas 5)(caballos 90)(combustible gasolina)(puntuacion 0))
	(coche (tipo turismo)(marca Renault)(modelo "Megane")(precio 13100)(puertas 5)(plazas 5)(caballos 100)(combustible gasolina)(puntuacion 0))
	(inicio)
	(valor_marca 100)
	(valor_combustible 125)
	(valor_tipo 125)
	(valor_precio 150)
	;sigue con los demas
)

(defrule r-inicio
	(inicio)
=>
	(printout t "Bienvenido al concesionario CarmenaMotor" crlf)
  (printout t "En CarmenaMotor comparamos coches a partir de lo que el cliente solicite, pudiendo optar por el tipo de coche, combustible, marca y un rango de precio" crlf)
  (printout t "¿Estas listo? Empezemos" crlf)
	(assert (parametro si))
)

(defrule r-introducir_parametro
	(parametro si)
=>
	(printout t "¿Que parametro desea introducir?" crlf)
	(assert (introducir (read)))
)


(defrule r-marca
	?h <- (introducir marca)
	(parametro si)
=>
	(retract ?h)
	(printout t "Introduzca la marca. Disponemos de las marcas: Audi, BMW, Mercedes, Ford, Skoda, Peugeot y Renault" crlf)
	(assert (marca (read)))
)

(defrule r-puntua_marca
	?h <- (coche (tipo ?tipo)(tipo_punt ?tipo_punt)(marca ?marca)(marca_punt ?marca_punt)(modelo ?modelo)(precio ?precio)(precio_punt ?precio_punt)(puertas ?puertas)(plazas ?plazas)(caballos ?caballos)(combustible ?combustible)(combustible_punt ?combustible_punt)(puntuacion ?puntuacion))
	(marca ?m)
	(valor_marca ?valor_marca)
	(test(eq ?m ?marca))
	(test(eq ?marca_punt no))
=>
	;(assert (coche (tipo ?tipo)(marca ?marca)(modelo ?modelo)(precio ?precio)(puertas ?puertas)(plazas ?plazas)(caballos ?caballos)(combustible ?combustible)(puntuacion (+ ?puntuacion ?valor_marca))))
	(modify ?h (puntuacion (+ ?puntuacion ?valor_marca))(marca_punt si))
)

(defrule r-adios_marca
	(declare(salience -1))
	?h <- (marca ?m)
=>
	(retract ?h)
)

(defrule r-tipo
	?h <- (introducir tipo)
	(parametro si)
=>
	(retract ?h)
	(printout t "Introduzca el tipo de vehiculo. A su eleccion tiene: turismo, familiar, suv y deportivo" crlf)
	(assert (tipo (read)))
)

(defrule r-puntua_tipo
	?h <- (coche (tipo ?tipo)(tipo_punt ?tipo_punt)(marca ?marca)(marca_punt ?marca_punt)(modelo ?modelo)(precio ?precio)(precio_punt ?precio_punt)(puertas ?puertas)(plazas ?plazas)(caballos ?caballos)(combustible ?combustible)(combustible_punt ?combustible_punt)(puntuacion ?puntuacion))
	(tipo ?t)
	(valor_tipo ?valor_tipo)
	(test(eq ?t ?tipo))
	(test(eq ?tipo_punt no))
=>
	;(assert (coche (tipo ?tipo)(marca ?marca)(modelo ?modelo)(precio ?precio)(puertas ?puertas)(plazas ?plazas)(caballos ?caballos)(combustible ?combustible)(puntuacion (+ ?puntuacion ?valor_marca))))
	(modify ?h (puntuacion (+ ?puntuacion ?valor_tipo))(tipo_punt si))
)
(defrule r-adios_tipo
	(declare(salience -1))
	?h <- (tipo ?t)
=>
	(retract ?h)
)

(defrule r-combustible
	?h <- (introducir combustible)
	(parametro si)
=>
	(retract ?h)
	(printout t "Introduzca el combustible. Poseemos coches gasolina, diesel y tambien hibridos" crlf)
	(assert (combustible (read)))
)

(defrule r-puntua_combustible
	?h <- (coche (tipo ?tipo)(tipo_punt ?tipo_punt)(marca ?marca)(marca_punt ?marca_punt)(modelo ?modelo)(precio ?precio)(precio_punt ?precio_punt)(puertas ?puertas)(plazas ?plazas)(caballos ?caballos)(combustible ?combustible)(combustible_punt ?combustible_punt)(puntuacion ?puntuacion))
	(combustible ?c)
	(valor_combustible ?valor_combustible)
	(test(eq ?c ?combustible))
	(test(eq ?combustible_punt no))
=>
	;(assert (coche (tipo ?tipo)(marca ?marca)(modelo ?modelo)(precio ?precio)(puertas ?puertas)(plazas ?plazas)(caballos ?caballos)(combustible ?combustible)(puntuacion (+ ?puntuacion ?valor_marca))))
	(modify ?h (puntuacion (+ ?puntuacion ?valor_combustible))(combustible_punt si))
)
(defrule r-adios_combustible
	(declare(salience -1))
	?h <- (combustible ?c)
=>
	(retract ?h)
)

(defrule r-precio
	?h <- (introducir precio)
	(parametro si)
=>
	(retract ?h)
	(printout t "Introduzca el precio maximo" crlf)
	(assert (precio_max (read)))
	(printout t "Introduzca el precio minimo" crlf)
	(assert (precio_min (read)))
)

(defrule r-puntua_precio
	?h <- (coche (tipo ?tipo)(tipo_punt ?tipo_punt)(marca ?marca)(marca_punt ?marca_punt)(modelo ?modelo)(precio ?precio)(precio_punt ?precio_punt)(puertas ?puertas)(plazas ?plazas)(caballos ?caballos)(combustible ?combustible)(combustible_punt ?combustible_punt)(puntuacion ?puntuacion))
	(precio_max ?pmax)
	(precio_min ?pmin)
	(valor_precio ?valor_precio)
	(test(>= ?pmax ?precio))
	(test(<= ?pmin ?precio))
	(test(eq ?precio_punt no))
=>
	;(assert (coche (tipo ?tipo)(marca ?marca)(modelo ?modelo)(precio ?precio)(puertas ?puertas)(plazas ?plazas)(caballos ?caballos)(combustible ?combustible)(puntuacion (+ ?puntuacion ?valor_marca))))
	(modify ?h (puntuacion (+ ?puntuacion ?valor_precio))(precio_punt si))
)
(defrule r-adios_precio
	(declare(salience -1))
	?h1 <- (precio_max ?pmax)
	?h2 <- (precio_min ?pmin)

=>
	(retract ?h1)
	(retract ?h2)
)


(defrule r-seguir_introduciendo
	(declare(salience -2))
	?h <- (parametro si)
=>
	(retract ?h)
	(printout t "¿Desea introducir mas parametros? [si/no] " )
	(assert(parametro (read)))
)

(defrule r-no_mas_parametros
	(parametro no)
=>
	(printout t "Se han encontrado los siguientes coches con los datos proporcionados" crlf)
	(assert(imprimir_compatibles))
	(assert(despedida))
)

(defrule r-imprime_compatibles
	(imprimir_compatibles)
	(coche (tipo ?tipo)(tipo_punt ?tipo_punt)(marca ?marca)(marca_punt ?marca_punt)(modelo ?modelo)(precio ?precio)(precio_punt ?precio_punt)(puertas ?puertas)(plazas ?plazas)(caballos ?caballos)(combustible ?combustible)(combustible_punt ?combustible_punt)(puntuacion ?puntuacion))
	(not (coche (tipo ?)(tipo_punt ?)(marca ?)(marca_punt ?)(modelo ?)(precio ?)(precio_punt ?)(puertas ?)(plazas ?)(caballos ?)(combustible ?)(combustible_punt ?)(puntuacion ?puntuacion2 &: (> ?puntuacion2 ?puntuacion))))
	;(test(> ?puntuacion ?puntuacion2))
=>
	(printout t ?marca " " ?modelo " de " ?precio " euros, consta de " ?puertas " puertas y " ?plazas " plazas y tiene un motor " ?combustible " de " ?caballos " caballos" crlf)
)

(defrule r-despedida
	(declare(salience -2))
  (despedida)
=>
  (printout t "Muchas gracias por confiar en CarmenaMotor. nos vemos pronto " crlf)
)
