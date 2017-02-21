
/**
 * \file      integration_step_QAGI.cpp
 * \authors   Charles Rocabert, Samuel Bernard
 * \date      08-11-2016
 * \copyright Copyright (C) 2016 Charles Rocabert, Samuel Bernard. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     Integrate the fitness over the population distribution (no mutation, isotropic noise, one axis displacement), using QAGI method
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
#include <fstream>
#include <sstream>
#include <cstring>
#include <sys/stat.h>
#include <cmath>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_randist.h>
#include <assert.h>


#define PI 3.14159265359

#define EPSABS 0.0
#define ESPREL 1e-12
#define LIMIT  1000

void readArgs( int argc, char const** argv, size_t& dim, double& mu, double& sigma );
void printUsage( void );
void printHeader( void );

double gaussian_pdf( double x, double mu, double sigma );
double w( double x );
double f( double x, void* params );
void   QAGI( double* res, double mu, double sigma, gsl_integration_workspace* workspace, gsl_function* F );
void   QAGS( double* res, double mu, double sigma, gsl_integration_workspace* workspace, gsl_function* F );
void   QAGP( double* res, double mu, double sigma, gsl_integration_workspace* workspace, gsl_function* F );
void   W( double* mu, double sigma, size_t n, double& result, double& error );


/**
 * \brief    Main function
 * \details  --
 * \param    int argc
 * \param    char const** argv
 * \return   \e int
 */
int main( int argc, char const** argv )
{
  size_t dim   = 0;
  double mu    = 0.0;
  double sigma = 0.0;
  readArgs(argc, argv, dim, mu, sigma);
  
  double* mu_vec = new double[dim];
  for (size_t i = 0; i < dim; i++)
  {
    mu_vec[i] = 0.0;
  }
  mu_vec[0] = mu;
  double result = 0.0;
  double error  = 0.0;
  W(mu_vec, sigma, dim, result, error);
  delete[] mu_vec;
  mu_vec = NULL;
  /*
  std::stringstream filename;
  filename << dim << "_" << mu << "_" << sigma << ".txt";
  std::ofstream file(filename.str().c_str(), std::ios::out | std::ios::trunc);
  file << result << " " << error << "\n";
  file.close();
  */
  std::cout << result << " " << error << "\n";
  
  return EXIT_SUCCESS;
}

/**
 * \brief    Read command line arguments
 * \details  --
 * \param    int argc
 * \param    char const** argv
 * \param    size_t& dim
 * \param    double& mu
 * \param    double& sigma
 * \return   \e void
 */
void readArgs( int argc, char const** argv, size_t& dim, double& mu, double& sigma )
{
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
    else if (strcmp(argv[i], "-dim") == 0 || strcmp(argv[i], "--dim") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        dim = (size_t)atoi(argv[i+1]);
        counter++;
      }
    }
    else if (strcmp(argv[i], "-mu") == 0 || strcmp(argv[i], "--mu") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        mu = atof(argv[i+1]);
        counter++;
      }
    }
    else if (strcmp(argv[i], "-sigma") == 0 || strcmp(argv[i], "--sigma") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: command line parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        sigma = atof(argv[i+1]);
        counter++;
      }
    }
  }
  if (counter < 3)
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
  std::cout << "Integrate the fitness over the population distribution (no mutation,\n";
  std::cout << "isotropic noise, one axis displacement), using QAGI method:\n";
  std::cout << "-----------------------------------------------------------\n";
  std::cout << "Usage: integration_step_QAGI -h or --help\n";
  std::cout << "   or: integration_step_QAGI [options]\n";
  std::cout << "Options are:\n";
  std::cout << "  -h, --help\n";
  std::cout << "        print this help, then exit\n";
  std::cout << "  -v, --version\n";
  std::cout << "        print the current version, then exit\n";
  std::cout << "  -dim, --dim\n";
  std::cout << "        specify the number of dimensions (mandatory)\n";
  std::cout << "  -mu, --mu\n";
  std::cout << "        specify the mu value on axis 1 (mandatory)\n";
  std::cout << "  -sigma, --sigma\n";
  std::cout << "        specify the sigma value (mandatory)\n";
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
  std::cout << "Integrate the fitness over the population distribution (no mutation,\n";
  std::cout << "isotropic noise, one axis displacement), using QAGI method.\n";
  std::cout << "\n";
}

/**
 * \brief    Simple gaussian law pdf
 * \details  --
 * \param    double x
 * \param    double mu
 * \param    double sigma
 * \return   \e double
 */
double gaussian_pdf( double x, double mu, double sigma )
{
  //return 1.0/(sigma*sqrt(2.0*PI))*exp(-0.5*((x-mu)/sigma)*((x-mu)/sigma));
  return gsl_ran_gaussian_pdf(x-mu, sigma);
}

/**
 * \brief    Compute the most basic FGM fitness
 * \details  --
 * \param    double x
 * \return   \e double
 */
double w( double x )
{
  return exp(-x*x/2);
}

/**
 * \brief    Compute one 1d integration point
 * \details  --
 * \param    double x
 * \return   \e double
 */
double f( double x, void* params )
{
  double* cast_param = (double*)params;
  double mu          = cast_param[0];
  double sigma       = cast_param[1];
  return gaussian_pdf(x, mu, sigma)*w(x);
}

/**
 * \brief    Compute 1d QAGI integral
 * \details  --
 * \param    double mu
 * \param    double sigma
 * \return   \e void
 */
void QAGI( double* res, double mu, double sigma, gsl_integration_workspace* workspace, gsl_function* F )
{
  double* params = new double[2];
  params[0] = mu;
  params[1] = sigma;
  F->params = params;
  double result, error;
  gsl_integration_qagi(F, EPSABS, ESPREL, LIMIT, workspace, &result, &error);
  delete[] params;
  params = NULL;
  F->params = NULL;
  res[0] = result;
  res[1] = error;
}

/**
 * \brief    Compute 1d QAGS integral
 * \details  --
 * \param    double mu
 * \param    double sigma
 * \return   \e void
 */
void QAGS( double* res, double mu, double sigma, gsl_integration_workspace* workspace, gsl_function* F )
{
  double* params = new double[2];
  params[0] = mu;
  params[1] = sigma;
  F->params = params;
  double result, error;
  gsl_integration_qags(F, -5.0, 5.0, EPSABS, ESPREL, LIMIT, workspace, &result, &error);
  delete[] params;
  params = NULL;
  F->params = NULL;
  res[0] = result;
  res[1] = error;
}

/**
 * \brief    Compute 1d QAGP integral
 * \details  --
 * \param    double mu
 * \param    double sigma
 * \return   \e void
 */
void QAGP( double* res, double mu, double sigma, gsl_integration_workspace* workspace, gsl_function* F )
{
  double* params = new double[2];
  params[0] = mu;
  params[1] = sigma;
  F->params = params;
  double result, error;
  double* singularities = new double[3];
  singularities[0] = -10.0;
  singularities[1] = mu;
  singularities[2] = 10.0;
  gsl_integration_qagp(F, singularities, 3, EPSABS, ESPREL, LIMIT, workspace, &result, &error);
  delete[] singularities;
  singularities = NULL;
  delete[] params;
  params = NULL;
  F->params = NULL;
  res[0] = result;
  res[1] = error;
}

/**
 * \brief    Compute the complete integral
 * \details  --
 * \param    double* mu
 * \param    double sigma
 * \param    size_t n
 * \param    double& result
 * \param    double& error
 * \return   \e void
 */
void W( double* mu, double sigma, size_t n, double& result, double& error )
{
  gsl_integration_workspace* workspace = gsl_integration_workspace_alloc(LIMIT);
  gsl_function F;
  F.function  = &f;
  F.params    = NULL;
  result      = 1.0;
  error       = 0.0;
  double* res = new double[2];
  for (size_t i = 0; i < n; i++)
  {
    //QAGI(res, mu[i], sigma, workspace, &F);
    if (sigma > 0.0006)
    {
      QAGI(res, mu[i], sigma, workspace, &F);
      result *= res[0];
      error  += res[1];
    }
    else
    {
      result *= w(mu[i]);
    }
  }
  delete[] res;
  res = NULL;
  gsl_integration_workspace_free(workspace);
  workspace = NULL;
}







