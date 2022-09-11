# Genetic_Algorithm
Generic algorithm is population based search and optimization technique which works 
based on the mechanism of natural genetics and Darwin’s principal of natural selection.
Initial solution can be any number of set. In population based search number of 
solutions are searched at a time. In a GA solutions are represented in a coded form like 
chromosomes, similarly in GA solutions consists of number of genes called as string which 
can consist of real or binary number. In this scope, we used binary coded GA, the string 
here only consist of 0 and 1. The length of string depends on the accuracy of desired solution.

The problem given is a minimization problem, so GA works only with maximization so the problem was converted 
from minimization to maximization. First we created initial solution set using random numbers.
The solution strings were taken to the mating pool using binary tournament selection, the crossover
performed is single-point as the string length is not very large. We'd have gone with double-point
or uniform crossover otherwise. After crossover, new solution pool is created. In the last step,
we performe bit-wise mutation to introduce variety in our solution space, with user-defined mutation probability.

The entire procedure is carried out for finite iterations and the final solution is obtained.
