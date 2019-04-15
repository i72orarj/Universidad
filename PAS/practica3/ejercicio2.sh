#!/bin/bash

if [ $# -ne 2 -a $# -ne 1 ];
then
	echo "El uso del programa es $0 rutaDirectorio numeroBytes"
	exit 1
fi
if [ $# -eq 1 ];
then
	tam=0
elif [ $# -eq 2 ];
then
	if [ $2 -ge 0 ];
	then
		tam=$2
	else
		echo "El numero de bytes es negativo"
		exit 1
	fi
fi
if [ ! -d $1 ];
then
  echo " $1 no es un directorio"
  exit 1
fi
echo "Nombre LongitudUsuario FechaModificacion FechaAcceso Tamano Bloques Permisos Ejecutable"
for x in $(find $1 -size "+$tam"c -type f -o -size "$tam"c -type f)
do
	if [ -x $x ];
	then
		ejecutable=1
	else
		ejecutable=0
	fi
	let longitud=$(stat -c %U $x | wc -m)-1
	#echo ""
  echo "$(basename $x);$longitud;$(stat -c %y $x);$(stat -c %X $x);$(stat -c %s $x);$(stat -c %b $x);$(stat -c %A $x);$ejecutable;"
done | sort -n -t";" -k 5

# stat -c "%n;$caracteres;%y;%x;%s;%b;%A;$ejec" $x >> $fichero



#en el punto 3 no es fecha de creacion sino de modificacion
