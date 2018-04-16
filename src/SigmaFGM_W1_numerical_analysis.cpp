
/**
 * \file      SigmaFGM_W1_numerical_analysis.cpp
 * \authors   Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon
 * \date      06-04-2018
 * \copyright Copyright (C) 2016-2018 Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     Compute W1 numerical analysis
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
#include <cstring>
#include <sys/stat.h>
#include <assert.h>

#include "./lib/Macros.h"
#include "./lib/Enums.h"
#include "./lib/Prng.h"
#include "./lib/Parameters.h"
#include "./lib/NumericalAnalysis.h"

const std::string EXECUTABLE_NAME = "build/bin/SigmaFGM_W1_numerical_analysis";

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
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 1) Read parameters        */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  std::cout << "> Read parameters ...\n";
  Parameters* parameters = new Parameters();
  readArgs(argc, argv, parameters);
  if (parameters->get_seed() == 0)
  {
    parameters->set_seed((unsigned long int)time(NULL));
  }
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 2) Run numerical analysis */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  std::cout << "> Run W1 numerical analysis ...\n";
  NumericalAnalysis* num = new NumericalAnalysis(parameters);
  
  double X_min   = parameters->get_X_min();
  double X_max   = parameters->get_X_max();
  double X_step  = parameters->get_X_step();
  double Ve_min  = parameters->get_Ve_min();
  double Ve_max  = parameters->get_Ve_max();
  double Ve_step = parameters->get_Ve_step();
  double alpha   = parameters->get_alpha();
  double beta    = parameters->get_beta();
  double Q       = parameters->get_Q();
  double epsilon = parameters->get_epsilon();
  
  num->explore_W1(X_min, X_max, X_step, Ve_min, Ve_max, Ve_step, alpha, beta, Q, epsilon);
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 3) Free memory            */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  
  delete num;
  num = NULL;
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
    else if (strcmp(argv[i], "-Xmin") == 0 || strcmp(argv[i], "--Xmin") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_X_min(atof(argv[i+1]));
        counter++;
      }
    }
    /* Mandatory */
    else if (strcmp(argv[i], "-Xmax") == 0 || strcmp(argv[i], "--Xmax") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_X_max(atof(argv[i+1]));
        counter++;
      }
    }
    /* Mandatory */
    else if (strcmp(argv[i], "-Xstep") == 0 || strcmp(argv[i], "--Xstep") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_X_step(atof(argv[i+1]));
        counter++;
      }
    }
    /* Mandatory */
    else if (strcmp(argv[i], "-Vemin") == 0 || strcmp(argv[i], "--Vemin") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_Ve_min(atof(argv[i+1]));
        counter++;
      }
    }
    /* Mandatory */
    else if (strcmp(argv[i], "-Vemax") == 0 || strcmp(argv[i], "--Vemax") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_Ve_max(atof(argv[i+1]));
        counter++;
      }
    }
    /* Mandatory */
    else if (strcmp(argv[i], "-Vestep") == 0 || strcmp(argv[i], "--Vestep") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_Ve_step(atof(argv[i+1]));
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
    else if (strcmp(argv[i], "-epsilon") == 0 || strcmp(argv[i], "--epsilon") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_epsilon(atof(argv[i+1]));
        counter++;
      }
    }
    
    /****************************************************************/
    
    /* Not mandatory */
    
  }
  if (counter < 10)
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
  std::cout << "Usage: SigmaFGM_W1_numerical_analysis -h or --help\n";
  std::cout << "   or: SigmaFGM_W1_numerical_analysis [options]\n";
  std::cout << "Options are:\n";
  std::cout << "  -h, --help\n";
  std::cout << "        print this help, then exit\n";
  std::cout << "  -v, --version\n";
  std::cout << "        print the current version, then exit\n";
  std::cout << "  -Xmin, --Xmin\n";
  std::cout << "        specify the minimal X value\n";
  std::cout << "  -Xmax, --Xmax\n";
  std::cout << "        specify the maximal X value\n";
  std::cout << "  -Xstep, --Xstep\n";
  std::cout << "        specify the X step\n";
  std::cout << "  -Vemin, --Vemin\n";
  std::cout << "        specify the minimal Ve value\n";
  std::cout << "  -Vemax, --Vemax\n";
  std::cout << "        specify the maximal Ve value\n";
  std::cout << "  -Vestep, --Vestep\n";
  std::cout << "        specify the Ve step\n";
  std::cout << "  -alpha, --alpha\n";
  std::cout << "        specify the alpha value\n";
  std::cout << "  -beta, --beta\n";
  std::cout << "        specify the beta value\n";
  std::cout << "  -Q, --Q\n";
  std::cout << "        specify the Q value\n";
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
