#!/bin/bash

if [ $1 ];then
	gcc "$1".c -o "$1" -pthread
	./"$1"
else
	echo -e "\nDebe enviar el nombre del programa sin la extension como parametro.\n"
fi