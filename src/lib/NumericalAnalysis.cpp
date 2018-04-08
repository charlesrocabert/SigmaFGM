
/**
 * \file      NumericalAnalysis.cpp
 * \authors   Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon
 * \date      06-04-2018
 * \copyright Copyright (C) 2016-2018 Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     NumericalAnalysis class definition
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

#include "NumericalAnalysis.h"


/*----------------------------
 * CONSTRUCTORS
 *----------------------------*/

/**
 * \brief    Constructor
 * \details  --
 * \param    Parameters* parameters
 * \return   \e void
 */
NumericalAnalysis::NumericalAnalysis( Parameters* parameters )
{
  assert(parameters != NULL);
  
  /*----------------------------------------------- PARAMETERS */
  
  _parameters = parameters;
  _prng       = _parameters->get_prng();
  
}

/*----------------------------
 * DESTRUCTORS
 *----------------------------*/

/**
 * \brief    Destructor
 * \details  --
 * \param    void
 * \return   \e void
 */
NumericalAnalysis::~NumericalAnalysis( void )
{
  /*----------------------------------------------- PARAMETERS */
  
  _parameters = NULL;
  _prng       = NULL;
}

/*----------------------------
 * PUBLIC METHODS
 *----------------------------*/

/*----------------------------
 * PROTECTED METHODS
 *----------------------------*/

/**
 * \brief    Gaussian pdf
 * \details  --
 * \param    double x
 * \param    double mu
 * \param    double sigma
 * \return   \e double
 */
double NumericalAnalysis::gaussian_pdf( double x, double mu, double sigma )
{
  return gsl_ran_gaussian_pdf(x-mu, sigma);
}

/**
 * \brief    Gamma pdf
 * \details  --
 * \param    double x
 * \param    double k
 * \param    double theta
 * \return   \e double
 */
double NumericalAnalysis::gamma_pdf( double x, double k, double theta )
{
  return gsl_ran_gamma_pdf(x, k, theta);
}

/**
 * \brief    Compute the fitness of a phenotype
 * \details  --
 * \param    double z
 * \param    double alpha
 * \param    double beta
 * \param    double Q
 * \return   \e double
 */
double NumericalAnalysis::W( double z, double alpha, double beta, double Q )
{
  return (1.0-beta)*exp(-alpha*pow(z, Q))+beta;
}

/**
 * \brief    Integrand used to compute the mean fitness of a genotype
 * \details  W(z).p(z) dz
 * \param    double z
 * \param    void* params
 * \return   \e double
 */
double NumericalAnalysis::W1_integrand( double z, void* params )
{
  double* cast_param = (double*)params;
  double  X          = cast_param[0];
  double  Ve         = cast_param[1];
  double  alpha      = cast_param[2];
  double  beta       = cast_param[3];
  double  Q          = cast_param[4];
  return gaussian_pdf(z, X, Ve)*W(z, alpha, beta, Q);
}

/**
 * \brief    Compute W1 = int[ W(z).p(z) dz ]
 * \details  --
 * \param    double X
 * \param    double Ve
 * \param    double alpha
 * \param    double beta
 * \param    double Q
 * \return   \e double
 */
double NumericalAnalysis::W1( double X, double Ve, double alpha, double beta, double Q )
{
  if (Ve < MIN_SIGMA)
  {
    return W(X, alpha, beta, Q);
  }
  
  /*-----------------------------*/
  /* 1) Declare GSL objects      */
  /*-----------------------------*/
  gsl_integration_workspace* workspace = gsl_integration_workspace_alloc(LIMIT);
  gsl_function F;
  
  /*-----------------------------*/
  /* 2) Create parameters vector */
  /*-----------------------------*/
  double* params = new double[5];
  params[0]      = X;
  params[1]      = Ve;
  params[2]      = alpha;
  params[3]      = beta;
  params[4]      = Q;
  
  /*-----------------------------*/
  /* 3) Compute the integral     */
  /*-----------------------------*/
  F.function = &NumericalAnalysis::W1_integrand;
  F.params   = params;
  double result, error;
  gsl_integration_qagi(&F, EPSABS, ESPREL, LIMIT, workspace, &result, &error);
  gsl_integration_workspace_free(workspace);
  workspace = NULL;
  delete[] params;
  params = NULL;
  return result;
}

/**
 * \brief    Integrand used to compute the mean fitness among the distribution of genotypes
 * \details  p(X|X_bar,Vgx).W1
 * \param    double X
 * \param    void* params
 * \return   \e double
 */
double NumericalAnalysis::W2_integrand( double X, void* params )
{
  double* cast_param = (double*)params;
  double  X_bar      = cast_param[0];
  double  Vgx        = cast_param[1];
  double  Ve         = cast_param[2];
  double  alpha      = cast_param[3];
  double  beta       = cast_param[4];
  double  Q          = cast_param[5];
  return gaussian_pdf(X, X_bar, Vgx)*W1(X, Ve, alpha, beta, Q);
}

/**
 * \brief    Compute W2 = int[ p(X|X_bar,Vgx).W1 dX ]
 * \details  --
 * \param    double X_bar
 * \param    double Vgx
 * \param    double Ve
 * \param    double alpha
 * \param    double beta
 * \param    double Q
 * \return   \e double
 */
double NumericalAnalysis::W2( double X_bar, double Vgx, double Ve, double alpha, double beta, double Q )
{
  std::cout << Ve << "\n";
  /*-----------------------------*/
  /* 1) Declare GSL objects      */
  /*-----------------------------*/
  gsl_integration_workspace* workspace = gsl_integration_workspace_alloc(LIMIT);
  gsl_function F;
  
  /*-----------------------------*/
  /* 2) Create parameters vector */
  /*-----------------------------*/
  double* params = new double[6];
  params[0]      = X_bar;
  params[1]      = Vgx;
  params[2]      = Ve;
  params[3]      = alpha;
  params[4]      = beta;
  params[5]      = Q;
  
  /*-----------------------------*/
  /* 3) Compute the integral     */
  /*-----------------------------*/
  F.function = &NumericalAnalysis::W2_integrand;
  F.params   = params;
  double result, error;
  gsl_integration_qags(&F, -20.0, 20.0, EPSABS, ESPREL, LIMIT, workspace, &result, &error);
  gsl_integration_workspace_free(workspace);
  workspace = NULL;
  delete[] params;
  params = NULL;
  return result;
}

/**
 * \brief    Integrand used to compute the mean fitness among the distribution of noisy genotypes
 * \details  p(Ve|Ve_bar,Vge).W2
 * \param    double Ve
 * \param    void* params
 * \return   \e double
 */
double NumericalAnalysis::W3_integrand( double Ve, void* params )
{
  double* cast_param = (double*)params;
  double  Ve_bar     = cast_param[0];
  double  Vge        = cast_param[1];
  double  X_bar      = cast_param[2];
  double  Vgx        = cast_param[3];
  double  alpha      = cast_param[4];
  double  beta       = cast_param[5];
  double  Q          = cast_param[6];
  double  k          = Vge;
  double  theta      = Ve_bar/Vge;
  return gamma_pdf(Ve, k, theta)*W2(X_bar, Vgx, Ve, alpha, beta, Q);
}

/**
 * \brief    Compute W3 = int[ p(Ve|Ve_bar,Vge).W2 dVe ]
 * \details  --
 * \param    double Ve_bar
 * \param    double Vge
 * \param    double X_bar
 * \param    double Vgx
 * \param    double alpha
 * \param    double beta
 * \param    double Q
 * \return   \e double
 */
double NumericalAnalysis::W3( double Ve_bar, double Vge, double X_bar, double Vgx, double alpha, double beta, double Q )
{
  /*-----------------------------*/
  /* 1) Declare GSL objects      */
  /*-----------------------------*/
  gsl_integration_workspace* workspace = gsl_integration_workspace_alloc(LIMIT);
  gsl_function F;
  
  /*-----------------------------*/
  /* 2) Create parameters vector */
  /*-----------------------------*/
  double* params = new double[7];
  params[0]      = Ve_bar;
  params[1]      = Vge;
  params[2]      = X_bar;
  params[3]      = Vgx;
  params[4]      = alpha;
  params[5]      = beta;
  params[6]      = Q;
  
  /*-----------------------------*/
  /* 3) Compute the integral     */
  /*-----------------------------*/
  F.function = &NumericalAnalysis::W3_integrand;
  F.params   = params;
  double result, error;
  gsl_integration_qags(&F, 0.01, 20.0, EPSABS, ESPREL, LIMIT, workspace, &result, &error);
  gsl_integration_workspace_free(workspace);
  workspace = NULL;
  delete[] params;
  params = NULL;
  return result;
}


