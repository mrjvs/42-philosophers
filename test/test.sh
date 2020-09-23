#!/bin/bash

if [ -z $1 ]; then
	echo "oof"
elif [ "$1" == "1" ]; then
	cd ../philo_one
	make re
	cd ../test
	../philo_one/philo_one "$2" "$3" "$4" "$5" $6 | node ./test.js
elif [ "$1" == "2" ]; then
	cd ../philo_two
	make re
	cd ../test
	../philo_two/philo_two "$2" "$3" "$4" "$5" $6 | node ./test.js
elif [ "$1" == "3" ]; then
	cd ../philo_three
	make re
	cd ../test
	../philo_three/philo_three "$2" "$3" "$4" "$5" $6 | node ./test.js
fi
