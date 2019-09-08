
/**
 * \file      SigmaFGM_simulation.cpp
 * \authors   Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon
 * \date      07-06-2016
 * \copyright Copyright (C) 2016-2019 Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     Run a simulation
 */

/***********************************************************************
 * Copyright (C) 2016-2019
 * Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************/

#include "../cmake/Config.h"

#include <iostream>
#include <sstream>
#include <cstring>
#include <sys/stat.h>
#include <assert.h>

#include "./lib/Macros.h"
#include "./lib/Enums.h"
#include "./lib/Parameters.h"
#include "./lib/Simulation.h"

void readArgs( int argc, char const** argv, Parameters* parameters );
void printUsage( void );
void printHeader( void );


/**
 * \brief    Main function
 * \details  --
 * \param    int argc
 * \param    char const** argv
 * \return   \e int
 */
int main( int argc, char const** argv )
{
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 1) Read parameters                 */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  Parameters* parameters = new Parameters();
  readArgs(argc, argv, parameters);
  if (parameters->get_seed() == 0)
  {
    parameters->set_seed((unsigned long int)time(NULL));
  }
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 2) Create the simulation           */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  Simulation* simulation = new Simulation(parameters);
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 3) Stabilize the population        */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  if (parameters->get_number_of_stabilizing_generations() > 0)
  {
    simulation->stabilize(parameters->get_number_of_stabilizing_generations());
  }
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 4) Run the simulation              */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  if (parameters->get_shutoff_distance() == 0)
  {
    simulation->run(parameters->get_number_of_generations());
  }
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 5) Run the simulation with shutoff */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  if (parameters->get_shutoff_distance() > 0.0)
  {
    simulation->run_with_shutoff(parameters->get_shutoff_distance(), parameters->get_shutoff_generation());
  }
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 6) Free memory                     */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  delete simulation;
  simulation = NULL;
  delete parameters;
  parameters = NULL;
  
  return EXIT_SUCCESS;
}

/**
 * \brief    Read command line arguments
 * \details  --
 * \param    int argc
 * \param    char const** argv
 * \param    Parameters* parameters
 * \return   \e void
 */
void readArgs( int argc, char const** argv, Parameters* parameters )
{
  if (argc == 1)
  {
    printf("You must provide all the mandatory arguments (see -h or --help). Exit.\n");
    exit(EXIT_SUCCESS);
  }
  int counter = 0;
  for (int i = 0; i < argc; i++)
  {
    /****************************************************************/
    
    if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
    {
      printUsage();
      exit(EXIT_SUCCESS);
    }
    else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0)
    {
      std::cout << PACKAGE << " (" << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH << ")\n";
      exit(EXIT_SUCCESS);
    }
    
    /*----------------------------------------------- PSEUDORANDOM NUMBERS GENERATOR SEED */
    
    else if (strcmp(argv[i], "-seed") == 0 || strcmp(argv[i], "--seed") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_seed((unsigned long int)atoi(argv[i+1]));
        counter++;
      }
    }
    
    /*----------------------------------------------- SIMULATION TIME */
    
    else if (strcmp(argv[i], "-stabg") == 0 || strcmp(argv[i], "--stabilizing-generations") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_number_of_stabilizing_generations(atoi(argv[i+1]));
      }
    }
    else if (strcmp(argv[i], "-g") == 0 || strcmp(argv[i], "--generations") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_number_of_generations(atoi(argv[i+1]));
        counter++;
      }
    }
    else if (strcmp(argv[i], "-shutoffd") == 0 || strcmp(argv[i], "--shutoff-distance") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_shutoff_distance(atof(argv[i+1]));
      }
    }
    else if (strcmp(argv[i], "-shutoffg") == 0 || strcmp(argv[i], "--shutoff-generation") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_shutoff_generation(atoi(argv[i+1]));
      }
    }
    
    /*----------------------------------------------- PHENOTYPIC COMPLEXITY */
    
    else if (strcmp(argv[i], "-nbdim") == 0 || strcmp(argv[i], "--nb-dimensions") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_number_of_dimensions(atoi(argv[i+1]));
        counter++;
      }
    }
    
    /*----------------------------------------------- FITNESS FUNCTION */
    
    else if (strcmp(argv[i], "-alpha") == 0 || strcmp(argv[i], "--alpha") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_alpha(atof(argv[i+1]));
        counter++;
      }
    }
    else if (strcmp(argv[i], "-beta") == 0 || strcmp(argv[i], "--beta") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_beta(atof(argv[i+1]));
        counter++;
      }
    }
    else if (strcmp(argv[i], "-Q") == 0 || strcmp(argv[i], "--Q") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_Q(atof(argv[i+1]));
        counter++;
      }
    }
    
    /*----------------------------------------------- POPULATION */
    
    else if (strcmp(argv[i], "-popsize") == 0 || strcmp(argv[i], "--population-size") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_population_size(atoi(argv[i+1]));
        counter++;
      }
    }
    else if (strcmp(argv[i], "-initx") == 0 || strcmp(argv[i], "--initial-x") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_initial_X(atof(argv[i+1]));
        counter++;
      }
    }
    else if (strcmp(argv[i], "-initve") == 0 || strcmp(argv[i], "--initial-ve") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_initial_Ve(atof(argv[i+1]));
        counter++;
      }
    }
    else if (strcmp(argv[i], "-inittheta") == 0 || strcmp(argv[i], "--initial-theta") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_initial_Theta(atof(argv[i+1]));
        counter++;
      }
    }
    else if (strcmp(argv[i], "-oneDshift") == 0 || strcmp(argv[i], "--oneD-shift") == 0)
    {
      parameters->set_oneD_shift(true);
    }
    
    /*----------------------------------------------- MUTATIONS */
    
    else if (strcmp(argv[i], "-mx") == 0 || strcmp(argv[i], "--m-x") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_m_X(atof(argv[i+1]));
        counter++;
      }
    }
    else if (strcmp(argv[i], "-mve") == 0 || strcmp(argv[i], "--m-ve") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_m_Ve(atof(argv[i+1]));
        counter++;
      }
    }
    else if (strcmp(argv[i], "-mtheta") == 0 || strcmp(argv[i], "--m-theta") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_m_Theta(atof(argv[i+1]));
        counter++;
      }
    }
    else if (strcmp(argv[i], "-sx") == 0 || strcmp(argv[i], "--s-x") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_s_X(atof(argv[i+1]));
        counter++;
      }
    }
    else if (strcmp(argv[i], "-sve") == 0 || strcmp(argv[i], "--s-ve") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_s_Ve(atof(argv[i+1]));
        counter++;
      }
    }
    else if (strcmp(argv[i], "-stheta") == 0 || strcmp(argv[i], "--s-theta") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_s_Theta(atof(argv[i+1]));
        counter++;
      }
    }
    
    /*----------------------------------------------- NOISE PROPERTIES */
    
    else if (strcmp(argv[i], "-noise") == 0 || strcmp(argv[i], "--noise-type") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        if (strcmp(argv[i+1], "NONE") == 0)
        {
          parameters->set_noise_type(NONE);
        }
        else if (strcmp(argv[i+1], "ISOTROPIC") == 0)
        {
          parameters->set_noise_type(ISOTROPIC);
        }
        else if (strcmp(argv[i+1], "UNCORRELATED") == 0)
        {
          parameters->set_noise_type(UNCORRELATED);
        }
        else if (strcmp(argv[i+1], "FULL") == 0)
        {
          parameters->set_noise_type(FULL);
        }
        else
        {
          std::cout << "Error: wrong value for parameter -noise (--noise-type).\n";
          exit(EXIT_FAILURE);
        }
        counter++;
      }
    }
    
    /****************************************************************/
  }
  if (counter < 17)
  {
    printf("You must provide all the mandatory arguments (see -h or --help). Exit.\n");
    exit(EXIT_SUCCESS);
  }
}

/**
 * \brief    Print usage
 * \details  --
 * \param    void
 * \return   \e void
 */
void printUsage( void )
{
  std::cout << "\n";
  std::cout << "*********************************************************************\n";
#ifdef DEBUG
  std::cout << " " << PACKAGE << " " << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH << " ( debug )\n";
#endif
#ifdef NDEBUG
  std::cout << " " << PACKAGE << " " << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH << " ( release )\n";
#endif
  std::cout << "                                                                     \n";
  std::cout << " Copyright (C) 2016-2019                                             \n";
  std::cout << " Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon   \n";
  std::cout << "                                                                     \n";
  std::cout << " This program comes with ABSOLUTELY NO WARRANTY.                     \n";
  std::cout << " This is free software, and you are welcome to redistribute it under \n";
  std::cout << " certain conditions; See the GNU General Public License for details  \n";
  std::cout << "*********************************************************************\n";
  std::cout << "\n";
  std::cout << "Usage: SigmaFGM_simulation -h or --help\n";
  std::cout << "   or: SigmaFGM_simulation [options]\n";
  std::cout << "Options are:\n";
  std::cout << "  -h, --help\n";
  std::cout << "        print this help, then exit\n";
  std::cout << "  -v, --version\n";
  std::cout << "        print the current version, then exit\n";
  std::cout << "  -seed, --seed\n";
  std::cout << "        specify the prng seed (mandatory, random if 0)\n";
  std::cout << "  -stabg, --stabilizing-generations\n";
  std::cout << "        specify the number of stabilizing generations\n";
  std::cout << "  -g, --generations\n";
  std::cout << "        specify the number of generations (mandatory)\n";
  std::cout << "  -shutoffd, --shutoff-distance\n";
  std::cout << "        specify the shutoff distance\n";
  std::cout << "  -shutoffg, --shutoff-generation\n";
  std::cout << "        specify the shutoff generation\n";
  std::cout << "  -nbdim, --nb-dimensions\n";
  std::cout << "        specify the number of dimensions (mandatory)\n";
  std::cout << "  -alpha, --alpha\n";
  std::cout << "        specify the alpha parameter of the fitness function (0.0 < mandatory)\n";
  std::cout << "  -beta, --beta\n";
  std::cout << "        specify the beta parameter of the fitness function (0.0 <= mandatory <= 1.0)\n";
  std::cout << "  -Q, --Q\n";
  std::cout << "        specify the Q parameter of the fitness function (0.0 <= mandatory)\n";
  std::cout << "  -popsize, --population-size\n";
  std::cout << "        specify the population size (mandatory)\n";
  std::cout << "  -initx, --initial-x\n";
  std::cout << "        specify the initial X value (mandatory)\n";
  std::cout << "  -initve, --initial-ve\n";
  std::cout << "        specify initial Ve value (mandatory)\n";
  std::cout << "  -inittheta, --initial-theta\n";
  std::cout << "        specify initial Theta value (mandatory)\n";
  std::cout << "  -oneDshift, --oneD-shift\n";
  std::cout << "        Indicates if the initial population is shifted in a single dimension\n";
  std::cout << "  -mx, --m-x\n";
  std::cout << "        specify the X mutation rate (mandatory)\n";
  std::cout << "  -mve, --m-ve\n";
  std::cout << "        specify the Ve mutation rate (mandatory)\n";
  std::cout << "  -mtheta, --m-theta\n";
  std::cout << "        specify the Theta mutation rate (mandatory)\n";
  std::cout << "  -sx, --s-x\n";
  std::cout << "        specify the X mutation size (mandatory)\n";
  std::cout << "  -sve, --s-ve\n";
  std::cout << "        specify the Ve mutation size (mandatory)\n";
  std::cout << "  -stheta, --stheta\n";
  std::cout << "        specify the Theta mutation size (mandatory)\n";
  std::cout << "  -noise, --noise-type\n";
  std::cout << "        Specify the type of noise (mandatory, NONE/ISOTROPIC/UNCORRELATED/FULL)\n";
  std::cout << "\n";
}

/**
 * \brief    Print header
 * \details  --
 * \param    void
 * \return   \e void
 */
void printHeader( void )
{
  std::cout << "\n";
  std::cout << "*********************************************************************\n";
#ifdef DEBUG
  std::cout << " " << PACKAGE << " " << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH << " ( debug )\n";
#endif
#ifdef NDEBUG
  std::cout << " " << PACKAGE << " " << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH << " ( release )\n";
#endif
  std::cout << "                                                                     \n";
  std::cout << " Copyright (C) 2016-2019                                             \n";
  std::cout << " Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon   \n";
  std::cout << "                                                                     \n";
  std::cout << " This program comes with ABSOLUTELY NO WARRANTY.                     \n";
  std::cout << " This is free software, and you are welcome to redistribute it under \n";
  std::cout << " certain conditions; See the GNU General Public License for details  \n";
  std::cout << "*********************************************************************\n";
  std::cout << "\n";
}
