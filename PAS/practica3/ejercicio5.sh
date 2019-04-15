#!/bin/bash
if [ $# -ne 1 ];
then
	echo "El uso del programa es $0 rutaDirectorio"
	exit 1
fi
if [ ! -d $1 ];
then
  echo "$1 no es un directorio"
  exit 1
fi
date=$(date +%s) #devuelve los segundos desde 1970
for x in $(find ~/Copia/ -type f)
do
  modif=$(stat $x -c %X) #segundos desde 1970 hasta la ultima modificacion
  time=$(($date-$modif))
  if [ $time -gt 200 ] #borra los .tar.gz que lleven creados mas de 2oo segundos
  then
    rm -r $x
    echo "Borrando $x de $time segundos..."
  fi
done
tar -czf ~/Copia/copia-$(stat -c %U $0)-$date.tar.gz $*
echo "La copia de seguridad se ha creado correctamente"
