#!/bin/bash
echo "El numero de archivos en la carpeta actual es $(find . -maxdepth 1 -type f | wc -l )" #busca en la carpeta actual sin entrar en subacarpetas
echo "$(who | awk '{print $1}' | sort | uniq)" #imprime nombre
echo -n "Que caracter quieres cortar? " #con -n no hace salto de linea
read -t5 -n1 c #t indica segundos de espera y n el numero de caracteres a introducir
if [ -z $c ]; #comprueba si la longitud de c es 0
then
  c='a'
  echo ""
  echo "Se tomara el valor por defecto 'a'"
fi
echo ""
contador=0
for x in $(find $x)
do
  let contador+=$(echo "$(basename $x)" | grep -o $c | wc -l)
done
echo "El caracter $c aparece $contador veces en nombres de ficheros o directorios contenidos en la carpeta actual"

# awk es como un filtro ficheros columnas
# wc -l fich.txt | awk '{print $1}'
