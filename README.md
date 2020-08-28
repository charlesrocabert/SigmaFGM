<h1 align="center">&sigma;FGM</h1>
<p align="center">
<img src="logo/logo.png" width="150">
<br/>
<em>Individual-based implementation of Fisher's geometric model with evolvable phenotypic noise</em>
<br/><br/>
<a href="https://github.com/charlesrocabert/SigmaFGM/releases/latest"><img src="https://img.shields.io/github/release/charlesrocabert/SigmaFGM/all.svg" /></a>&nbsp;
<a href="https://action-badges.now.sh/charlesrocabert/SigmaFGM"><img src="https://action-badges.now.sh/charlesrocabert/MetEvolSim" /></a>&nbsp;
<a href="https://github.com/charlesrocabert/SigmaFGM/LICENSE.html"><img src="https://img.shields.io/badge/License-GPLv3-blue.svg" /></a>
</p>

-----------------

<p align="justify">
Experimental studies demonstrate the existence of phenotypic diversity despite constant genotype and environment. Theoretical models based on a single phenotypic character predict that during an adaptation event, phenotypic noise should be positively selected far from the fitness optimum because it increases the fitness of the genotype, and then be selected against when the population reaches the optimum. It is suggested that because of this fitness gain, phenotypic noise should promote adaptive evolution. However, it is unclear how the selective advantage of phenotypic noise is linked to the rate of evolution, and whether any advantage would hold for more realistic, multi-dimensional phenotypes. Indeed, complex organisms suffer a cost of complexity, where beneficial mutations become rarer as the number of phenotypic characters increases (<a href="https://doi.org/10.1111/evo.14083">Rocabert et al. 2020</a>).
</p>

<p align="justify">
&sigma;FGM simulates adaptive evolution in Fisher's geometric model with an evolvable phenotypic noise. The fitness function is configurable and can adopt non-Gaussian shapes. Phenotypic noise is modeled by an evolvable multivariate normal distribution. See below for a first usage, and <a href="https://doi.org/10.1111/evo.14083">Rocabert et al. (2020)</a> for a full description of the simulation model.
</p>

<p align="justify">
&sigma;FGM has been developed by Charles Rocabert, Guillaume Beslon, Carole Knibbe and Samuel Bernard.
</p>

## Table of contents
- [Publications](#publications)
- [Installation instructions](#installation)
- [First usage](#first_usage)
- [Copyright](#copyright)
- [License](#license)

## Publications <a name="publications"></a>

• Rocabert C., Beslon G., Knibbe C. and Bernard S. (2020). Phenotypic Noise and the Cost of Complexity, _Evolution_, in press. https://doi.org/10.1111/evo.14083

## Installation instructions <a name="installation"></a>

Download the latest release of &sigma;FGM, and save it to a directory of your choice. Open a terminal and use the <code>cd</code> command to navigate to this directory. Then follow the steps below to compile and build the executables.

### 1. Supported platforms
&sigma;FGM software has been developed for Unix and OSX (macOS) systems.

### 2. Required dependencies
* A C++ compiler (GCC, LLVM, ...)
* CMake (command line version)
* GSL
* CBLAS

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

## Copyright <a name="copyright"></a>
Copyright &copy; 2016-2020 Charles Rocabert, Guillaume Beslon, Carole Knibbe, Samuel Bernard.
All rights reserved.

## License <a name="license"></a>
This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see http://www.gnu.org/licenses/.

