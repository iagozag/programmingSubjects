# Euclidean Traveling Salesman Problem

## Installing LEMON:

1. Step into the root of the source directory.

        $ cd lemon-1.3.1

 2. Create a build subdirectory and step into it.

        $ mkdir build
        $ cd build

 3. Perform system checks and create the makefiles.

        $ cmake ..

    By default, LEMON will be installed under /usr/local (you will need root
    privileges to be able to do that). If you want to install it to
    some other location, then pass the
    -DCMAKE_INSTALL_PREFIX=DIRECTORY flag to cmake.
    
    For example:

        $ cmake -DCMAKE_INSTALL_PREFIX=/home/username/lemon'

 5. Build LEMON.

        $ make

6. Install LEMON

    If you are installing under /usr/local:

        $ sudo make install

    Else:

        $ make install

## Compiling and Executing
1. In the root directory of the repository, compile the program:
   
        $ make
   
2. To execute, use the following command:

        $ ./main <file> <algorithm>

   #### Parameters:

   - <file\>: Path to a file containing the number of points and their coordinates.

       - The file must be located in the examples/ directory.
       - It must follow the TSPLIB format. For more details on this format, consult [TSPLIB specification](http://comopt.ifi.uni-heidelberg.de/software/TSPLIB95/tsp95.pdf).

   - <algorithm\> : Specifies the algorithm to execute.
  
       - 1: Twice Around The Tree
       - 2: Christofides

### Examples

There is an example for each algorithm:

- Twice Around The Tree:

        $ ./main kroA200.tsp 1
  
- Christofides:

        $ ./main berlin52.tsp 2
