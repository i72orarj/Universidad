#!/bin/bash
if [ $# -ne 1 ];
then
  echo "Debe introducir un fichero. $0 fichero.txt"
  exit 1
fi
if [ ! -f $1 ];
then
  echo "$1 no es un fichero"
  exit 1
fi
ruta="/home/$USER"
echo "===="
echo "Listado de archivos ocultos del directorio $ruta"

for x in $(ls -a $ruta | grep '^\.')
do
  nCaracteres=$(basename $x | wc -m)
  echo "$x $nCaracteres"
done | sort -k2 -n | grep -o -E '^\..* '
echo "===="
echo "El fichero a procesar es $1"
fichero="$(basename $1).sinLineasVacias.txt"
echo "El fichero sin lineas vacias se ha guardado en $fichero"
if [ ! -e $fichero ];
then
  touch $fichero
fi
grep -v -E '^ *$' $1 >>$fichero
echo "===="
# ps xu #procesos
# ps xu | sed -n -r '2,$s/^(.+) ([0-9]+) (.+) ([0-9]+:+[0-9]+) (.+) (.+) $/PID: "\2" Hora: "\3" Ejecutable: "\5"/p '
ps -ux | sed -rn '2,$s/(^[A-Za-z0-9]*)\ *([0-9]*)\ *([0-9\.]*)\ *([0-9\.]*\ *[0-9]*\ *[0-9]*)\ *([A-Za-z0-9\?\/]*)\ *([A-Za-z.]*)\ *([0-9A-Za-z\:]*)\ *([0-9\:]*)\ *([A-Za-z\/\-\(\)]*).*/PID: "\2" Hora: "\7" Ejecutable: "\9"/p'
# ps -ux | sed -rn '2,$s/(^[A-Za-z0-9]*)\ *([0-9]*)\ *([0-9\.]*)\ *([0-9\.]*\ *[0-9]*\ *[0-9]*)\ *([A-Za-z0-9\?\/]*)\ *([A-Za-z.]*)\ *([0-9A-Za-z\:]*)\ *([0-9\:]*)\ *([A-Za-z\/\-\(\)]*).*/"\1" "\2" "\3" "\4" "\5" "\6" "\7" "\8" "\9"/p'
echo "===="
