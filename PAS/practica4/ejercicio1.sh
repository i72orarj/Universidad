#!/bin/bash
if [ $# -ne 1 ];
then
  echo "Debe introducir un fichero. ./ejercicio1.sh fichero.txt"
  exit 1
fi
if [ ! -f $1 ];
then
  echo "$1 no es un fichero"
  exit 1
fi
echo "**************************************************************"
echo "1.- Duracion de las peliculas"
grep -E '^[0-9]+.+\ [0-9]+(min)' $1
echo "**************************************************************"
echo "2.- Lineas que contienen el pais de la pelicula"
grep -E '.+-.+-' $1
echo "**************************************************************"
echo "3.- Solo los paises de las peliculas"
grep -Eo '\-.+\-' $1
echo "**************************************************************"
echo "4.1.- Numero de peliculas del 2016"
grep -Ec '.*(2016).*' $1
echo "4.2.- Numero de peliculas del 2017"
grep -Ec '.*(2017).*' $1
echo "**************************************************************"
echo "5.- Eliminar lineas vacias"
grep -v '^$' $1
echo "**************************************************************"
echo "6.- Lineas que empiezan por 'E'"
grep -E '^.{0,2}E.*' $1
echo "**************************************************************"
echo "7.- Lineas que contienen d, l, t con una vocal y la misma letra"
grep -E '(d[aeiou]d)|(l[aeiou]l)|(t[aeiou]t)' $1
echo "**************************************************************"
echo "8.- Lineas con 8 vocales o mas"
grep -E '((.*a.*)|(.*A.*)){8,}' $1
echo "**************************************************************"
echo "9.- Lineas que acaban con tres puntos y no empiezan por espacio"
grep -E '^R.*(\.\.\.)$' $1
echo "**************************************************************"
echo "10.- Mostrar entre comillas las vocales con tildes"
sed -r -e 's!([áéíóúÁÉÍÓÚ])!"\1"!g' $1
