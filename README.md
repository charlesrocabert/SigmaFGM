# <img src="logo/logo.png" width="48"> &sigma;FGM

&sigma;FGM is a numerical solver for Fisher's geometric model (FGM, Fisher 1930), with evolvable phenotypic noise.

## License

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see http://www.gnu.org/licenses/.

## Authors

### 1. Original authors
&sigma;FGM is being developed by Charles Rocabert, Samuel Bernard, Carole Knibbe and Guillaume Beslon.

## Installation instructions

Download the latest release of &sigma;FGM, and save it to a directory of your choice. Open a terminal and use the <code>cd</code> command to navigate to this directory. Then follow the steps below to compile and build the executables.

### 1. Supported platforms
&sigma;FGM software has been developed for Unix and OSX (macOS) systems.

### 2. Required dependencies
* A C++ compiler (GCC, LLVM, ...)
* CMake (command line version)
* zlib
* GSL
* CBLAS
* TBB

### 3. Software compilation

#### User mode
To compile &sigma;FGM, run the following instructions on the command line:

    cd cmake/

and

    bash make.sh

#### Debug mode
To compile the software in DEBUG mode, use <code>make_debug.sh</code> script instead of <code>make.sh</code>:

    bash make_debug.sh

This mode should only be used for test or development phases.

#### Executable files emplacement
Binary executable files are in <code>build/bin</code> folder.

## Typical usage

Coming soon ...

## References
* Fisher, R. A. (1930). <em>The genetical theory of natural selection: a complete variorum edition</em>. Oxford University Press, Oxford (UK).

