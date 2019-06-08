#!/bin/bash
while read x;
do
  echo "$x" | sed -r -n -e 's/model name.*: ([a-zA-Z0-9.]+)/Modelo del procesador: \1/p' -e 's/cpu MHz.*: ([0-9]+\.[0-9]+)/Megahercios: \1/p' -e 's/cache size.*: ([0-9]+)/Tamano de cache: \1 /p' -e 's/cpu cores.*: ([0-9]+)/Numero maximo de hilos en ejecucion: \1/p' -e 's/vendor_id.*: ([a-zA-Z]+)/ID vendedor: \1/p'
done < /proc/cpuinfo
echo "Puntos de montaje:"
cat /proc/mounts | sed -rn 's/^[a-z]*\ *([a-z/]*)\ *([a-z]*)\ *[a-z]*,[a-z]*,([a-z]*),[a-z]*.*/Punto de montaje: \1,\t Dispositivo: \3, \tTipo de dispositivo: \2/p' | sort -r
echo "Particiones y numero de bloques: "
cat /proc/partitions | sed -r -n -e '3,$s/.+ ([0-9]+) ([a-zA-Z0-9]+)/-> Particion: \2, Numero de bloques: \1/p' | sort -k2 -r
