#!/bin/bash 

function msg(){
    echo -n -e "\033[0;31m"
    echo $*
    echo -n -e "\033[0m"
}

function cmd(){
    echo -n -e "\033[0;32m"
    echo $*
    echo -n -e "\033[0m"
    $*
}

msg "compilation de example en objet"
cmd gcc -g -O0 -Wall -I. -c example.c

msg "compilation de hash en objet"
cmd gcc  -g -O0 -Wall -I. -c hash.c -o hash_std.o
msg "compilation de hash en objet repositionnable"
cmd gcc  -g -O0 -Wall -I. -fPIC -c hash.c -o hash_pic.o

msg "creation de la bibliotheque statique"
cmd ar rcs libhash.a hash_std.o
msg "utilisation de la bibliotheque statique"
cmd gcc example.o libhash.a -o example_static
msg "symboles dans le binaire statique:"
cmd nm ./example_static


msg "creation de la bibliotheque dynamique" 
cmd gcc -shared -o libhash.so hash_pic.o
msg "utilisation de la bibliotheque dynamique"
cmd gcc example.o -lhash -L. -o example_dynamique 

msg "ldd sur l'executable avec bibliotheque dynamique"
LD_LIBRARY_PATH=. ldd ./example_dynamique
msg "symboles dans le binaire dynamique:"
cmd nm ./example_dynamique

