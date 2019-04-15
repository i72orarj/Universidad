#!/bin/bash
function listararchivos()
{
    echo "<ul>" >> $fichero
    for x in $(find $1) #-maxdepth 1)
    do
      if [ -f $x ];
      then #saber si es directorio o archivo
        echo "<li><strong>$x</strong></li>" >> $fichero #si es un archivo, si es directorio no poner strong
      else
        echo "<li>$x</li>" >> $fichero
      fi
    done
    echo "</ul>" >> $fichero
}
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
fichero="$(basename $1).html"
if [ ! -e $fichero ];
then
  touch $fichero #crea el .html si no existe
fi
echo "<html>" > $fichero
echo "<head>" >> $fichero
echo "<title><h3>LISTADO DE DIRECTORIOS DE $1</h3></title>" >> $fichero
echo "</head>" >> $fichero
echo "<body>" >> $fichero
listararchivos $1
echo "</body>" >> $fichero
echo "</html>" >> $fichero

#hacer con funciones aunque no lo ponga en el pdf
