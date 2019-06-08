#!/bin/bash
if [ $# -ne 2 ];
then
  echo "Introduzca dos argumentos. ./ejercicio4.sh fichero.txt numeroSegundos"
  exit 1
fi

if [ ! -f $1 ];
then
  echo "$1 no es un fichero"
  exit 1
fi

if [ ! $2 -gt 0 ];
then
  echo "Introduzca un numero de segundos mayor que 0"
  exit 1
fi

for x in $(cat $1)
do
  # respuesta=$(ping -c 1 -w $2 $x)
  ping -c 1 -w $2 $x | sed -r -n 's/([0-9]+) bytes from ([0-9]+\.[0-9]+\.[0-9]+\.[0-9]).+ time=([0-9]+\.*)/La IP \2 respondio en \3/p '
  # sed
done | sort -k6 -n
