#!/bin/bash

# "binaryname" ""
build () {
    echo "Compiling $1"
    rm -rf "../$1"
    cp -r ./code "../$1"

    COM=THREAD
    LOCK=SEM

    # remove unneccesary header files
    if [ $2 == "process_sem" ]; then
        rm "../$1/philosophers_shared_sem.h"
        rm "../$1/philosophers_shared_mutex.h"
        COM=PROCESS
    elif [ $2 == "shared_sem" ]; then
        rm "../$1/philosophers_process_sem.h"
        rm "../$1/philosophers_shared_mutex.h"
    elif [ $2 == "shared_mutex" ]; then
        rm "../$1/philosophers_process_sem.h"
        rm "../$1/philosophers_shared_sem.h"
        LOCK=MUTEX
    fi

    if [ $LOCK == "SEM" ]; then
        rm "../$1/philosopher/lock-mutex.c"
        mv "../$1/philosopher/lock-sem.c" "../$1/philosopher/lock.c"

        rm "../$1/philosopher/forks-mutex.c"
        mv "../$1/philosopher/forks-sem.c" "../$1/philosopher/forks.c"
    elif [ $LOCK == "MUTEX" ]; then
        rm "../$1/philosopher/lock-sem.c"
        mv "../$1/philosopher/lock-mutex.c" "../$1/philosopher/lock.c"
        
        rm "../$1/philosopher/forks-sem.c"
        mv "../$1/philosopher/forks-mutex.c" "../$1/philosopher/forks.c"
    fi

    if [ $COM == "THREAD" ]; then
        rm "../$1/philosopher/communication-process.c"
        mv "../$1/philosopher/communication-thread.c" "../$1/philosopher/communication.c"

        rm "../$1/philosopher/starter-process.c"
        mv "../$1/philosopher/starter-thread.c" "../$1/philosopher/starter.c"
    elif [ $COM == "PROCESS" ]; then
        rm "../$1/philosopher/communication-thread.c"
        mv "../$1/philosopher/communication-process.c" "../$1/philosopher/communication.c"

        rm "../$1/philosopher/starter-thread.c"
        mv "../$1/philosopher/starter-process.c" "../$1/philosopher/starter.c"
    fi

    # set variables
    sed -i -e "s=HEADERHERE=philosophers_$2.h=g" "../$1/philosophers.h"
    sed -i -e "s=NAMEHERE=$1=g" "../$1/Makefile"

    echo "Finished compiling $1"
}

build "philo_five" "process_sem"
