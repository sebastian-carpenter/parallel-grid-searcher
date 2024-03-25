# parallel-grid-searcher

This project takes most of its inital inspiration from problem 11 of the Euler project.
I developed a solution for it and later decided to parallelize it. The normal version and parallelized version are both shown in this repository.

The important parallelized code is at **./version_1/cversion/parallel/parallel_search.c**.
This version is functional and has been tested. The results of testing can be found in version_1.xlsx

When compiling the parallelized programs be sure to use the appropriate pthread compile flag this may be something like **pthread** or **lpthread**.

Generally I compile with gcc -o parallel_search parallel_search.c ../../array_generator.c ../../calculate.c ../../parallel_helper.c -Wall -pthread

In the root of each version you will notice three files array_generator, calculate, and parallel_helper. These files are used by various sections of the program and thus represent different modules that are used during runtime. These will be explained later.

The most important folder is version_1 which houses the actual working version of the parallel grid searcher.

The grids folder houses a utility for creating grids and is also where the grids are stored.

All the original code (which includes the dregs) is stored in version_0

The normversion folder, in version_0, holds the altered version of my solution to problem 11 of the Euler project.

Lastly, pyversion, in version_0, contains the program I attempted to make which would utilize .so versions of my .c files, that way I could parallelize the program through Python (this failed).

# version_1

## ./parallel/parallel_search.c

This is better by a mile than legacy_rev_row.c.

The major inconsistencies with speed present in legacy_rev_row are fixed in this version due to how information is now accessed and stored by threads. Additionally various parts of the program have been rewritten or reworked.

A general catalog of changes is contained below:

    * Variable access and assignment with threads is now optimized.
    
    * calculate.c has been optimized.
    
    * There is more of an overhead for starting the program but runtime is much faster.
    
        * This is more apparent with complex calculations; with simple calculations, like this program, the overhead can take longer than before.
        
    * Answers are now stored more efficiently and with less wasted space.
    
        * Answers are now much faster to search through as well.
        
    * array_generator and parallel_helper have been altered to conform to the changes.
    

## ./serial/serial_search.c

This is much better than the previous serial algorithm present in version_0.

This version has been reprogrammed to mesh with the new files used for parallel_search.c.

Performance expectation - a little under twice as fast as before.

This performance is mostly thanks to the optimizations done for parallel_search. I think this is about the limit for performance on serial_search though.

# version_0 - deprecated

# ./cversion

Folders 'test' and 'mk2' can be ignored as they hold either nothing or just test programs.

## ./cversion/legacy

The files in this folder will not run unless you alter the headers to mesh appropriately. These are old attempts at parallelization which I decided to keep as reference.

### legacy_row.c
parameters - .txt grid file, size of grid, multiplier, number of threads

legacy_row is the direct precursor for legacy_rev_row - the current parallel grid searcher. It contains a rough implementation for running multiple threads and laid the foundation for how the future program should be structured. Particulary, this version was the first to give each thread its own row to calculate.

### legacy_cell.c
parameters - .txt grid file, size of grid, multiplier, number of threads

legacy_cell is a derivative of legacy_row and so is the same in many ways. The important thing to note with this program is that each thread gets its own cell to calculate but this is very slow. I do not recommend trying to run this version (though, at the moment, it is unable to run anyway).

## ./cversion/legacy_rev

The only file in this folder is legacy_rev_row.c and it is effectively the current version of parallel grid searcher.

### legacy_rev_row.c
parameters - .txt grid file, size of grid, multiplier, number of threads

Much like legacy_row.c, legacy_rev_row gives each thread a unique row to calculate. The method for providing this row differs slightly since it uses an altered struct (still used for passing arguments when creating a thread) and a new struct which holds information throughout the duration of the program.

A new header file was created called parallel_helper which 'helps' modularize the parallel function calls.

The other two header files were also edited since I needed to redefine my allocation of arrays and I also needed to define pointer arithmetic.

## ./cversion/serial

This folder contains the serial.c program which is compared as a control against the current parallel version.

### serial.c
parameters - .txt grid file, size of grid, multiplier

This program is an optimized version of my original solution to the Euler project, problem 11. It uses two of the same headers as the current parallel program so its runtime behavior is very similar just without parallelization.

Mainly, the way serial.c differs from legacy_rev_row.c is that it computes the largest value and determines if it is the largest immediately rather than later.

# ./grids

This folder contains the grid creator and .txt files for running the programs in this repository.

### grid_creator.c
parameters - .txt grid file output name, size of grid

This takes in a name for a file to output and the size of grid to create (square), then creates the appropriate file which can be used with the programs in this repository.

### default.txt

This is a 20x20 grid which should result in the value 70600674 when computed. This is basically a control to make sure the programs work. Serial.c also works as a control for making sure the parallel programs are correct.

# ./normversion

This folder houses the somewhat original solution to the Euler project, problem 11.

### 11_1_advanced.c

This one does not work anymore because it relies on two header files which have been changed extensively. The original solution to problem 11 was not as modular as this one which is why this one is denoted advanced. It is the precursor to legacy_row.c

# ./pyversion

Without going into too much detail, this is my failed attempt at parallelizing the .c programs using Python as a medium. Since I have reworked my code it might be possible to get this working but I am unsure if I will do so in the future.

# header files

# version_1

## array_generator

This one creates the structs used throughout the program. The create_structs function requires file I/O and can return an error. Grids are allocated using malloc so grids might be limited in size, but I am unsure if there is an actual limit. I tried with a 100000x100000 grid and it never stopped allocating until I ran out of patience.

## calculate

This does all the calculations for the programs. Currently it computes the largest product of 4 numbers in the vertical, horizontal and both diagonal directions. Each function call revolves around a cell which serves as the origin for performing the 4 computations. The handling of variables is a little funky but it improves performance.

## parallel_helper

This is the middleman for the parallel functions. When a pthread is started up it will call calculate_step and begin calculating a row.

# version_0

## array_generator

This one generates the 2D and 3D arrays used throughout the program. The 2D array requires file I/O and so is more complex than the 3D one to allocate. The answer array and grid are allocated using malloc so they might be limited in size, but I am unsure if there is an actual limit. I tried with a 100000x100000 grid and it never stopped allocating until I ran out of patience.

## calculate

This does all the calculations for the programs. Currently it computes the largest product of 4 numbers in the vertical, horizontal and both diagonal directions. Each function call revolves around a cell which serves as the origin for performing the 4 computations.

## parallel_helper

This is the middleman for the parallel functions. When a pthread is started up one of the functions will be called which will determine what the pthread does for its lifetime.
