
/**
 * \file      run_solver.cpp
 * \authors   Charles Rocabert, Samuel Bernard
 * \date      07-06-2016
 * \copyright Copyright (C) 2016-2017 Charles Rocabert, Samuel Bernard. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     Run the solver
 */

/***********************************************************************
 * Copyright (C) 2016-2017 Charles Rocabert, Samuel Bernard
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

#include "./lib/Parameters.h"
#include "./lib/Solver.h"

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
  /**************************************************/
  /* 1) Read parameters                             */
  /**************************************************/
  Parameters* parameters = new Parameters();
  readArgs(argc, argv, parameters);
  if (parameters->get_prng_seed() == 0)
  {
    parameters->set_prng_seed((unsigned long int)time(NULL));
  }
  
  /**************************************************/
  /* 2) Create the solver                           */
  /**************************************************/
  Solver* solver = new Solver(parameters);
  solver->initialize();
  
  /**************************************************/
  /* 3) Bring the solver to an initial stable state */
  /**************************************************/
  if (parameters->get_stabilizing_time() > 0)
  {
    solver->stabilize();
  }
  
  /**************************************************/
  /* 4) Run the solver                              */
  /**************************************************/
  std::ofstream extra_2D_statistics;
  if (parameters->get_extra_2D_statistics())
  {
    extra_2D_statistics.open("2Dstatistics.txt", std::ios::out | std::ios::trunc);
    extra_2D_statistics << "step t mu1 mu2 sigma1 sigma2 theta\n";
  }
  bool   stop_criterion = false;
  size_t shutoff_count  = 0;
  while (!stop_criterion)
  {
    solver->update(false);
    if (parameters->get_statistics())
    {
      solver->compute_statistics();
      solver->write_statistics();
    }
    if (parameters->get_extra_2D_statistics())
    {
      solver->write_extra_statistics(extra_2D_statistics);
    }
    if (parameters->get_shutoff_fitness() == 0.0)
    {
      stop_criterion = (solver->get_step() >= parameters->get_time());
    }
    else
    {
      if (solver->get_mean_wmu() > parameters->get_shutoff_fitness())
      {
        shutoff_count++;
      }
      else
      {
        shutoff_count = 0;
      }
      if (shutoff_count >= parameters->get_shutoff_time())
      {
        stop_criterion = true;
      }
    }
    if (solver->get_step()%1000 == 0)
    {
      std::cout << "> " << solver->get_step() << " elapsed steps (" << solver->get_time() << " elapsed time, wmu=" << solver->get_mean_wmu() << ")...\n";
    }
  }
  if (parameters->get_statistics())
  {
    solver->close_statistics();
  }
  if (parameters->get_extra_2D_statistics())
  {
    extra_2D_statistics.close();
  }
  
  /**************************************************/
  /* 5) Free memory                                 */
  /**************************************************/
  delete solver;
  solver = NULL;
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
    else if (strcmp(argv[i], "-stabt") == 0 || strcmp(argv[i], "--stabilizing-time") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_stabilizing_time((size_t)atoi(argv[i+1]));
        counter++;
      }
    }
    else if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--time") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_time((size_t)atoi(argv[i+1]));
        counter++;
      }
    }
    else if (strcmp(argv[i], "-shutofffitness") == 0 || strcmp(argv[i], "--shutoff-fitness") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_shutoff_fitness(atof(argv[i+1]));
        counter++;
      }
    }
    else if (strcmp(argv[i], "-shutofftime") == 0 || strcmp(argv[i], "--shutoff-time") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_shutoff_time((size_t)atoi(argv[i+1]));
        counter++;
      }
    }
    else if (strcmp(argv[i], "-seed") == 0 || strcmp(argv[i], "--seed") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_prng_seed((unsigned long int)atoi(argv[i+1]));
        counter++;
      }
    }
    else if (strcmp(argv[i], "-nbdim") == 0 || strcmp(argv[i], "--nb-dimensions") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_number_of_dimensions((size_t)atoi(argv[i+1]));
        counter++;
      }
    }
    else if (strcmp(argv[i], "-nbparticles") == 0 || strcmp(argv[i], "--nb-particles") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_number_of_particles(atof(argv[i+1]));
        counter++;
      }
    }
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
    else if (strcmp(argv[i], "-dmu") == 0 || strcmp(argv[i], "--delta-mu") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_delta_mu(atof(argv[i+1]));
        counter++;
      }
    }
    else if (strcmp(argv[i], "-dsigma") == 0 || strcmp(argv[i], "--delta-sigma") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_delta_sigma(atof(argv[i+1]));
        counter++;
      }
    }
    else if (strcmp(argv[i], "-dtheta") == 0 || strcmp(argv[i], "--delta-theta") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_delta_theta(atof(argv[i+1]));
        counter++;
      }
    }
    else if (strcmp(argv[i], "-statistics") == 0 || strcmp(argv[i], "--statistics") == 0)
    {
      parameters->set_statistics(true);
    }
    else if (strcmp(argv[i], "-2Dstatistics") == 0 || strcmp(argv[i], "--2Dstatistics") == 0)
    {
      parameters->set_extra_2D_statistics(true);
    }
    else if (strcmp(argv[i], "-oneaxis") == 0 || strcmp(argv[i], "--oneaxis") == 0)
    {
      parameters->set_one_axis(true);
    }
    else if (strcmp(argv[i], "-weightfitness") == 0 || strcmp(argv[i], "--weightfitness") == 0)
    {
      parameters->set_weight_fitness(true);
    }
    else if (strcmp(argv[i], "-nonoise") == 0 || strcmp(argv[i], "--nonoise") == 0)
    {
      parameters->set_no_noise(true);
    }
    else if (strcmp(argv[i], "-isotropicnoise") == 0 || strcmp(argv[i], "--isotropicnoise") == 0)
    {
      parameters->set_isotropic_noise(true);
    }
    else if (strcmp(argv[i], "-norotation") == 0 || strcmp(argv[i], "--norotation") == 0)
    {
      parameters->set_no_rotation(true);
    }
    else if (strcmp(argv[i], "-qagi") == 0 || strcmp(argv[i], "--qagi") == 0)
    {
      parameters->set_qagi(true);
    }
  }
  if (counter < 11)
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
  std::cout << " Copyright (C) 2016-2017 Charles Rocabert, Samuel Bernard            \n";
  std::cout << "                                                                     \n";
  std::cout << " This program comes with ABSOLUTELY NO WARRANTY.                     \n";
  std::cout << " This is free software, and you are welcome to redistribute it under \n";
  std::cout << " certain conditions; See the GNU General Public License for details  \n";
  std::cout << "*********************************************************************\n";
  std::cout << "\n";
  std::cout << "Run the solver:\n";
  std::cout << "---------------\n";
  std::cout << "Usage: run_solver -h or --help\n";
  std::cout << "   or: run_solver [options]\n";
  std::cout << "Options are:\n";
  std::cout << "  -h, --help\n";
  std::cout << "        print this help, then exit\n";
  std::cout << "  -v, --version\n";
  std::cout << "        print the current version, then exit\n";
  std::cout << "  -stabt, --stabilizing-time\n";
  std::cout << "        specify the stabilizing time (mandatory)\n";
  std::cout << "  -t, --time\n";
  std::cout << "        specify the solving time (mandatory)\n";
  std::cout << "  -shutofffitness, --shutoff-fitness\n";
  std::cout << "        specify the shutoff fitness\n";
  std::cout << "  -shutofftime, --shutoff-time\n";
  std::cout << "        specify the shutoff time\n";
  std::cout << "  -seed, --seed\n";
  std::cout << "        specify the prng seed (mandatory, random if 0)\n";
  std::cout << "  -nbdim, --nb-dimensions\n";
  std::cout << "        specify the number of dimensions (mandatory)\n";
  std::cout << "  -nbparticles, --nb-particles\n";
  std::cout << "        specify the number of particles (mandatory)\n";
  std::cout << "  -initmu, --initial-mu\n";
  std::cout << "        specify the initial mu value (mandatory)\n";
  std::cout << "  -initsigma, --initial-sigma\n";
  std::cout << "        specify initial sigma value (mandatory)\n";
  std::cout << "  -inittheta, --initial-theta\n";
  std::cout << "        specify initial theta value (mandatory)\n";
  std::cout << "  -dmu, --delta-mu\n";
  std::cout << "        specify the mu mutation size (mandatory)\n";
  std::cout << "  -dsigma, --delta-sigma\n";
  std::cout << "        specify the sigma mutation size (mandatory)\n";
  std::cout << "  -dtheta, --delta-theta\n";
  std::cout << "        specify the theta mutation size (mandatory)\n";
  std::cout << "  -statistics, --statistics\n";
  std::cout << "        Activate statistics saving\n";
  std::cout << "  -2Dstatistics, --2Dstatistics\n";
  std::cout << "        Activate extra 2D statistics saving\n";
  std::cout << "  -oneaxis, --oneaxis\n";
  std::cout << "        Initialize only one axis\n";
  std::cout << "  -weightfitness, --weightfitness\n";
  std::cout << "        Weight the fitness by the number of dimensions\n";
  std::cout << "  -nonoise, --nonoise\n";
  std::cout << "        Individuals do not undergo noise\n";
  std::cout << "  -isotropicnoise, --isotropicnoise\n";
  std::cout << "        Noise is isotropic\n";
  std::cout << "  -norotation, --norotation\n";
  std::cout << "        Individuals do not undergo co-variance matrix rotations\n";
  std::cout << "  -qagi, --qagi\n";
  std::cout << "        Integrative fitness will be computed, instead of instantaneous one\n";
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
  std::cout << " Copyright (C) 2016-2017 Charles Rocabert, Samuel Bernard            \n";
  std::cout << "                                                                     \n";
  std::cout << " This program comes with ABSOLUTELY NO WARRANTY.                     \n";
  std::cout << " This is free software, and you are welcome to redistribute it under \n";
  std::cout << " certain conditions; See the GNU General Public License for details  \n";
  std::cout << "*********************************************************************\n";
  std::cout << "Run the solver.\n";
  std::cout << "\n";
}
