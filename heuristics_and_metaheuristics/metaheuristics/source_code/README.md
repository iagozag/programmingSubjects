# Euclidean Traveling Salesman Problem

## Compiling and Executing
1. In the root directory of the repository, compile the program:
   
        $ make
   
2. To execute, use the following command:

        $ ./main <file>

   #### Parameters:

   - <file\>: Path to a file containing the number of points and their coordinates.

       - The file must be located in the examples/ directory.
       - It must follow the TSPLIB format. For more details on this format, consult [TSPLIB specification](http://comopt.ifi.uni-heidelberg.de/software/TSPLIB95/tsp95.pdf).

### Examples

There is an example for the BRKGA algorithm:
        $ ./main kroA200.tsp