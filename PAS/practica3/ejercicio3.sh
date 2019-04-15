#!/bin/bash
if [ $# -ne 3 -a $# -ne 1 ];
then
	echo "El uso del programa es $0 rutaDirectorio umbral1 umbral2"
	exit 1
fi
if [ ! -d $1 ];
then
  echo " $1 no es un directorio"
  exit 1
fi
if [ $# -eq 3 ];
then
  umbral1=$2
  umbral2=$3
else
  umbral1=10000
  umbral2=100000
fi
rutapequenos=pequenos
rutamedianos=medianos
rutagrandes=grandes
if [ -d $rutagrandes ];
then
	echo "Ya existe la carpeta grandes,borrandola..."
  rm -rf $rutagrandes
fi
if [ -d $rutamedianos ];
then
	echo "Ya existe la carpeta medianos,borrandola..."
  rm -rf $rutamedianos
fi
if [ -d $rutapequenos ];
then
	echo "Ya existe la carpeta pequenos,borrandola..."
  rm -rf $rutapequenos
fi
echo "Creando las carpetas pequenos, medianos y grandes..."
mkdir $rutagrandes $rutamedianos $rutapequenos
echo "Copiando los archivos..."
for x in $(find $1 -size "-$umbral1"c -type f)
do
  cp $x $rutapequenos
done
for x in $(find $1 -size "+$umbral1"c -type f -a -size "-$umbral2"c -type f)
do
  cp $x $rutamedianos
done
for x in $(find $1 -size "+$umbral2"c -type f)
do
  cp $x $rutagrandes
done
