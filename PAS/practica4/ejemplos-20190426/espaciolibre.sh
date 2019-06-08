#!/bin/bash

df | sed -r -n '2,$s/([^ ]+)[ ]+([^ ]+)[ ]+([^ ]+)[ ]+([^ ]+)[ ]+([^ ]+)[ ]+([^ ]+)/El fichero de bloques \1 montado en \6, tiene usados \3 bloques de un total de \2 (porcentaje \5)./gp'
