### Princeton Algorithms Assignment 1 - in C

#### The goal of this repo is purely to recreate the first assignment in Princeton's Algorithms Part 1 [class](https://www.coursera.org/learn/algorithms-part1)
#### The course teaches in Java, but this is being used as a way to teach myself C along the way and understand differences in a language with less abstractions and no GC.

##### Assignment 1 - Percolation (DONE)

##### How to run (On Linux)
```
cd percolation

# Place where the executable will be stored
mkdir bin

# Build the executable
make build

# Run Monte-Carlo simulation with grid size = 200 and # Trials = 100
make run SIZE=200 TRIALS=100

# Sanity testing for grid with size 2
make test
```

