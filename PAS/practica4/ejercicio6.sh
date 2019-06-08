#!/bin/bash
if [ $# -ne 1 ];
then
  echo "Debe introducir una cadena que sea shell de sistema. ./ejercicio1.sh cadena"
  exit 1
fi

# cambiar variable de entorno
odfIFS=$IFS
IFS=':'
while read -a fila; #-a guarda lo que lee en un vector
do
  if [ ${fila[6]} == $1 ];
  then
    # grupo=$(sed -n -r 's/([a-zA-Z]+):.*:{fila[3]}:/\1/p' /etc/group )
    while read -a fila2;
    do
      if [ ${fila2[2]} == ${fila[3]} ];
      then
        grupo=${fila2[0]}
      fi
    done < /etc/group
    logueado=$(who | grep -c ${fila[0]})
    echo "============"
    echo "Logname: ${fila[0]}"
    echo "-> UID: ${fila[2]} "
    echo "-> GID: ${fila[3]} "
    echo "-> Grupo: $grupo "
    echo "-> gecos: ${fila[4]} "
    echo "-> Home: ${fila[5]} "
    echo "-> Shell por defecto: ${fila[6]} "
    echo "-> Logeado: $logueado"
  fi
done < /etc/passwd
IFS=$oldifs
