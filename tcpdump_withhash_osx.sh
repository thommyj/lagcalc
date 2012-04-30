#!/bin/bash
tcpdump -e -n -i $1 |  awk 'BEGIN {FS=" "}{sub(/:/,"",$18);printf "%s %21s > %s %21s L2:%d L3/L4:%d\n",$2,$16,substr($4,0,17),$18,system("./calclagslave " $2 " " substr($4,0,17)  " " 2 " " 1),system("./calclagslave_l3 " $16 " " $18 " " 2 " " 1) }'
