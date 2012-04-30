#!/bin/bash
tcpdump -enl -i $1 tcp or udp | awk -W interactive 'BEGIN {FS=" "}{sub(/:/,"",$12);printf "%s %21s > %s %21s L2:%d L3/L4:%d\n",$2,$10,substr($4,0,18),$12,system("./calclagslave " $2 " " substr($4,0,18)  " " 2 " " 1),system("./calclagslave_l3 " $10 " " $12 " " 2 " " 1) }'
