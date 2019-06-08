#!/bin/bash

if [ $# -ne 1 ];
then
  echo "Debe introducir un fichero. ./ejercicio2.sh fichero.txt"
  exit 1
fi
if [ ! -f $1 ];
then
  echo "$1 no es un fichero"
  exit 1
fi

# sed -e '/^$/d' -r -e '/=+/d' -r -e 's/\([0-9]+\)/|-> Fecha de estreno: \1/' -r -e 's/Dirigida por ([a-zA-Z]+)$/|-> Director: \1/' -r -e 's/Reparto:(.+)/|-> Reparto: \1/'  -r -e 's/^[0-9]+hr\ [0-9]+(min)/|-> Duracion: \1/' -r -e '/^ +.+/d' -r -e 's/(^[^(|)].*)/Título: \1/'$1
# sed '/=+/d' $1

# sed -e '/^$/d' | sed -r -e '/=+/d' | sed -r -e 's/(\(.*\/.*\/.*\)) (.+)/|-> Fecha de estreno: \1/' | sed -r -e 's/Dirigida por (.+)$/|-> Director: \1/' | sed -r -e 's/Reparto: (.+)/|-> Reparto: \1/'| sed -r -e 's/([[:digit:]]hr [[:digit:]]*min)/|-> Duración: \1/' | sed -r -e '/^ +.+/d' | sed -r -e 's/(^[^(|)].*)/Título: \1/' $1

sed -rn -e 's/(^[^\ (Dirigido)(Reparto)()0-9=])/\nTitulo: \1/p' -e 's/^(\([0-9].{8,9}\))|/|-> Fecha de estreno: \1/p' -e 's/^(Dirigida por )(.*)/|-> Director: \2/p' -e 's/^(Reparto:)(.*)/|-> Reparto: \2/p' -e 's/(^[0-9])/|-> Duracion \1/p' $1
