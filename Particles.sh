#!/bin/bash

#$1 ecm

MAINPATH=~/Trabalhos/Therminator2/amazon
INPUT=$MAINPATH/$1gev
COUNTER=0

while [ $COUNTER -lt 100 ]; do
    
    cd $MAINPATH
    cp Particles.h $INPUT
    cd $INPUT
    if [ $COUNTER -lt 10 ]; then
        NAME=event00$COUNTER.root
    else
        NAME=event0$COUNTER.root
    fi
    
    cat Particles.h | sed "s/FILENAME/$NAME/g" >> temp && mv temp Particles.h

    echo ".L Particles.C
    Particles t
    t.Loop();
    .q
    " | root -l
    
    echo $COUNTER
    let COUNTER=COUNTER+1

done