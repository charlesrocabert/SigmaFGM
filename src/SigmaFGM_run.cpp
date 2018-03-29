
/**
 * \file      run_solver.cpp
 * \authors   Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon
 * \date      07-06-2016
 * \copyright Copyright (C) 2016-2018 Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     Run the simulation
 */

/***********************************************************************
 * Copyright (C) 2016-2018
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
#include "./lib/Population.h"
#include "./lib/Statistics.h"

const std::string EXECUTABLE_NAME = "build/bin/run_solver";

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
  /****************************/
  /* 1) Read parameters       */
  /****************************/
  Parameters* parameters = new Parameters();
  readArgs(argc, argv, parameters);
  if (parameters->get_seed() == 0)
  {
    parameters->set_seed((unsigned long int)time(NULL));
  }
  parameters->print_parameters();
  
  /****************************/
  /* 2) Create the simulation */
  /****************************/
  Population* pop   = new Population(parameters);
  Statistics* stats = new Statistics();
  stats->write_headers();
  
  /****************************/
  /* 3) Run the simulation    */
  /****************************/
  for (int t = 1; t <= parameters->get_simulation_time(); t++)
  {
    stats->reset();
    stats->compute_statistics(pop);
    stats->write_statistics(t);
    stats->flush();
    pop->compute_next_generation();
  }
  stats->close();
  
  /****************************/
  /* 4) Free memory           */
  /****************************/
  delete stats;
  stats = NULL;
  delete pop;
  pop = NULL;
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
    /* Not mandatory */
    if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
    {
      printUsage();
      exit(EXIT_SUCCESS);
    }
    /* Not mandatory */
    else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0)
    {
      std::cout << PACKAGE << " (" << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH << ")\n";
      exit(EXIT_SUCCESS);
    }
    
    /****************************************************************/
    
    /* Mandatory */
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
    /* Mandatory */
    else if (strcmp(argv[i], "-simt") == 0 || strcmp(argv[i], "--simulation-time") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_simulation_time(atoi(argv[i+1]));
        counter++;
      }
    }
    /* Mandatory */
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
    /* Mandatory */
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
    /* Mandatory */
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
    /* Mandatory */
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
    /* Mandatory */
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
    /* Mandatory */
    else if (strcmp(argv[i], "-initmu") == 0 || strcmp(argv[i], "--initial-mu") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_initial_mu(atof(argv[i+1]));
        counter++;
      }
    }
    /* Mandatory */
    else if (strcmp(argv[i], "-initsigma") == 0 || strcmp(argv[i], "--initial-sigma") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_initial_sigma(atof(argv[i+1]));
        counter++;
      }
    }
    /* Mandatory */
    else if (strcmp(argv[i], "-inittheta") == 0 || strcmp(argv[i], "--initial-theta") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_initial_theta(atof(argv[i+1]));
        counter++;
      }
    }
    /* Mandatory */
    else if (strcmp(argv[i], "-mmu") == 0 || strcmp(argv[i], "--m-mu") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_m_mu(atof(argv[i+1]));
        counter++;
      }
    }
    /* Mandatory */
    else if (strcmp(argv[i], "-msigma") == 0 || strcmp(argv[i], "--m-sigma") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_m_sigma(atof(argv[i+1]));
        counter++;
      }
    }
    /* Mandatory */
    else if (strcmp(argv[i], "-mtheta") == 0 || strcmp(argv[i], "--m-theta") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_m_theta(atof(argv[i+1]));
        counter++;
      }
    }
    /* Mandatory */
    else if (strcmp(argv[i], "-smu") == 0 || strcmp(argv[i], "--s-mu") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_s_mu(atof(argv[i+1]));
        counter++;
      }
    }
    /* Mandatory */
    else if (strcmp(argv[i], "-ssigma") == 0 || strcmp(argv[i], "--s-sigma") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_s_sigma(atof(argv[i+1]));
        counter++;
      }
    }
    /* Mandatory */
    else if (strcmp(argv[i], "-stheta") == 0 || strcmp(argv[i], "--s-theta") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_s_theta(atof(argv[i+1]));
        counter++;
      }
    }
    /* Mandatory */
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
    
    /* Not mandatory */
    else if (strcmp(argv[i], "-stabt") == 0 || strcmp(argv[i], "--stabilizing-time") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_stabilizing_time(atoi(argv[i+1]));
      }
    }
    /* Not mandatory */
    else if (strcmp(argv[i], "-shutoffdistance") == 0 || strcmp(argv[i], "--shutoff-distance") == 0)
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
    /* Not mandatory */
    else if (strcmp(argv[i], "-shutofftime") == 0 || strcmp(argv[i], "--shutoff-time") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_shutoff_time(atoi(argv[i+1]));
      }
    }
    else if (strcmp(argv[i], "-oneDshift") == 0 || strcmp(argv[i], "--oneD-shift") == 0)
    {
      parameters->set_oneD_shift(true);
    }
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
  std::cout << " Copyright (C) 2016-2018                                             \n";
  std::cout << " Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon   \n";
  std::cout << "                                                                     \n";
  std::cout << " This program comes with ABSOLUTELY NO WARRANTY.                     \n";
  std::cout << " This is free software, and you are welcome to redistribute it under \n";
  std::cout << " certain conditions; See the GNU General Public License for details  \n";
  std::cout << "*********************************************************************\n";
  std::cout << "\n";
  std::cout << "Usage: run_solver -h or --help\n";
  std::cout << "   or: run_solver [options]\n";
  std::cout << "Options are:\n";
  std::cout << "  -h, --help\n";
  std::cout << "        print this help, then exit\n";
  std::cout << "  -v, --version\n";
  std::cout << "        print the current version, then exit\n";
  std::cout << "  -seed, --seed\n";
  std::cout << "        specify the prng seed (mandatory, random if 0)\n";
  std::cout << "  -stabt, --stabilizing-time\n";
  std::cout << "        specify the stabilizing time\n";
  std::cout << "  -simt, --simulation-time\n";
  std::cout << "        specify the simulation time (mandatory)\n";
  std::cout << "  -shutoffdistance, --shutoff-distance\n";
  std::cout << "        specify the shutoff distance\n";
  std::cout << "  -shutofftime, --shutoff-time\n";
  std::cout << "        specify the shutoff time\n";
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
  std::cout << "  -initmu, --initial-mu\n";
  std::cout << "        specify the initial mu value (mandatory)\n";
  std::cout << "  -initsigma, --initial-sigma\n";
  std::cout << "        specify initial sigma value (mandatory)\n";
  std::cout << "  -inittheta, --initial-theta\n";
  std::cout << "        specify initial theta value (mandatory)\n";
  std::cout << "  -oneDshift, --oneD-shift\n";
  std::cout << "        Indicates if the initial population is shifted in a single dimension\n";
  std::cout << "  -mmu, --m-mu\n";
  std::cout << "        specify the mu mutation rate (mandatory)\n";
  std::cout << "  -msigma, --m-sigma\n";
  std::cout << "        specify the sigma mutation rate (mandatory)\n";
  std::cout << "  -mtheta, --m-theta\n";
  std::cout << "        specify the theta mutation rate (mandatory)\n";
  std::cout << "  -smu, --s-mu\n";
  std::cout << "        specify the mu mutation size (mandatory)\n";
  std::cout << "  -ssigma, --s-sigma\n";
  std::cout << "        specify the sigma mutation size (mandatory)\n";
  std::cout << "  -stheta, --stheta\n";
  std::cout << "        specify the theta mutation size (mandatory)\n";
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
  std::cout << " Copyright (C) 2016-2018                                             \n";
  std::cout << " Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon   \n";
  std::cout << "                                                                     \n";
  std::cout << " This program comes with ABSOLUTELY NO WARRANTY.                     \n";
  std::cout << " This is free software, and you are welcome to redistribute it under \n";
  std::cout << " certain conditions; See the GNU General Public License for details  \n";
  std::cout << "*********************************************************************\n";
  std::cout << "\n";
}
