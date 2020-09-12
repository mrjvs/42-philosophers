# finally!! I can use threads
last C project yay, no more norm after this!!!!

I tried making fork taking and threads/processes as pluggable as possible.
That way I can easily make all three programs from the subject without changing too much.

## usage
```SH
# build
make

# run examples, all numbers in milliseconds
# ./phil <phil_count> <time_to_die> <time_to_eat> <time_to_sleep> [phil_eat_count]
./phil 2 6000 3000 2000
./phil 2 6000 3000 2000 4
```

## TODO
 - [ ] argv parsing
 - [ ] Fork taking
 - [X] Give every philosopher a starvation checker thread*
 - [X] Remove printf statement in logger.c
 - [X] Dynamic sleep settings
 - [ ] Make all three programs (code generation)**

\* Starvation checker thread sets the death state and prints if starved

\*\* A script that copies all sources into export folder with file choices

## Before turnin
 - [ ] Add error flags
 - [ ] Check norm
 - [ ] Check subject
 - [ ] Check leaks
 - [ ] Remove debug symbols
