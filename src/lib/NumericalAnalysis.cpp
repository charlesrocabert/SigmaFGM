
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

/**
 * \brief    Explore The fitness of genotypes W1(X, Ve)
 * \details  Data is saved in file "W1.txt"
 * \param    double X_min
 * \param    double X_max
 * \param    double X_step
 * \param    double Ve_min
 * \param    double Ve_max
 * \param    double Ve_step
 * \param    double alpha
 * \param    double beta
 * \param    double Q
 * \param    double epsilon
 * \return   \e void
 */
void NumericalAnalysis::explore_W1( double X_min, double X_max, double X_step, double Ve_min, double Ve_max, double Ve_step, double alpha, double beta, double Q, double epsilon )
{
  std::ofstream file1("W1.txt", std::ios::out | std::ios::trunc);
  std::ofstream file2("dW1_dVe_isocline.txt", std::ios::out | std::ios::trunc);
  std::ofstream file3("dlnW1_dXdVe_isocline.txt", std::ios::out | std::ios::trunc);
  std::ofstream file4("fitness.txt", std::ios::out | std::ios::trunc);
  file1 << "X Ve W1 lnW1 dW1_dX dW1_dVe dlnW1_dX dlnW1_dVe d2lnW1_dXdVE\n";
  file2 << "X Ve W1\n";
  file3 << "X Ve lnW1_dX\n";
  file4 << "z W lnW dW_dz dlnW_dz\n";
  
  for (double X = X_min; X < X_max; X += X_step)
  {
    double W1_best     = 0.0;
    double Ve1_best    = 0.0;
    double lnW1dX_best = 1e+10;
    double Ve2_best    = 0.0;
    for (double Ve = Ve_min; Ve < Ve_max; Ve += Ve_step)
    {
      double w1           = W1(X, Ve, alpha, beta, Q);
      double dw1_dx       = dW1_dX(X, Ve, alpha, beta, Q, epsilon);
      double dw1_dve      = dW1_dVe(X, Ve, alpha, beta, Q, epsilon);
      double dlnw1_dx     = dlnW1_dX(X, Ve, alpha, beta, Q, epsilon);
      double dlnw1_dve    = dlnW1_dVe(X, Ve, alpha, beta, Q, epsilon);
      double d2lnw1_dxdve = d2lnW1_dXdVE(X, Ve, alpha, beta, Q, epsilon);
      if (W1_best < w1)
      {
        W1_best  = w1;
        Ve1_best = Ve;
      }
      if (lnW1dX_best > dlnw1_dx)
      {
        lnW1dX_best = dlnw1_dx;
        Ve2_best    = Ve;
      }
      file1 << X << " " << Ve << " " << w1 << " " << log(w1) << " " << dw1_dx << " " << dw1_dve << " " << dlnw1_dx << " " << dlnw1_dve << " " << d2lnw1_dxdve << "\n";
      file1.flush();
    }
    file2 << X << " " << Ve1_best << " " << W1_best << "\n";
    file3 << X << " " << Ve2_best << " " << lnW1dX_best << "\n";
    file4 << X << " " << W(X, alpha, beta, Q) << " " << log(W(X, alpha, beta, Q)) << " " << dW_dz(X, alpha, beta, Q, epsilon) << " " << dlnW_dz(X, alpha, beta, Q, epsilon) << "\n";
    file2.flush();
    file3.flush();
    file4.flush();
  }
  file1.close();
  file2.close();
  file3.close();
  file4.close();
}

/**
 * \brief    Explore The fitness of the population W3(X_bar, Ve_bar)
 * \details  Data is saved in file "W3.txt"
 * \param    double Xbar_min
 * \param    double Xbar_max
 * \param    double Xbar_step
 * \param    double Vebar_min
 * \param    double Vebar_max
 * \param    double Vebar_step
 * \param    double Vgx
 * \param    double Vge
 * \param    double alpha
 * \param    double beta
 * \param    double Q
 * \param    double epsilon
 * \return   \e void
 */
void NumericalAnalysis::explore_W3( double Xbar_min, double Xbar_max, double Xbar_step, double Vebar_min, double Vebar_max, double Vebar_step, double Vgx, double Vge, double alpha, double beta, double Q, double epsilon )
{
  std::ofstream file("W3.txt", std::ios::out | std::ios::trunc);
  file << "X_bar Ve_bar W3\n";
  for (double X_bar = Xbar_min; X_bar < Xbar_max; X_bar += Xbar_step)
  {
    for (double Ve_bar = Vebar_min; Ve_bar < Vebar_max; Ve_bar += Vebar_step)
    {
      std::cout << X_bar << " " << Ve_bar << "\n";
      double w3 = W3(Ve_bar, Vge, X_bar, Vgx, alpha, beta, Q);
      file << X_bar << " " << Ve_bar << " " << w3 << "\n";
      file.flush();
    }
  }
  file.close();
}

/**
 * \brief    Compute dW1/dVe and d2lnW1/dXdVe isoclines
 * \details  Data is saved in file "<alpha>_<beta>_<Q>.txt"
 * \param    double X_min
 * \param    double X_max
 * \param    double X_step
 * \param    double Ve_min
 * \param    double Ve_max
 * \param    double Ve_step
 * \param    double alpha
 * \param    double beta
 * \param    double Q
 * \param    double epsilon
 * \return   \e void
 */
void NumericalAnalysis::compute_isoclines( double X_min, double X_max, double X_step, double Ve_min, double Ve_max, double Ve_step, double alpha, double beta, double Q, double epsilon )
{
  std::stringstream filename;
  filename << alpha << "_" << beta << "_" << Q << ".txt";
  std::ofstream file(filename.str(), std::ios::out | std::ios::trunc);
  file << "X Ve1 Ve2\n";
  
  for (double X = X_min; X < X_max; X += X_step)
  {
    double W1_best     = 0.0;
    double Ve1_best    = 0.0;
    double lnW1dX_best = 1e+10;
    double Ve2_best    = 0.0;
    for (double Ve = Ve_min; Ve < Ve_max; Ve += Ve_step)
    {
      double w1       = W1(X, Ve, alpha, beta, Q);
      double dlnw1_dx = dlnW1_dX(X, Ve, alpha, beta, Q, epsilon);
      if (W1_best < w1)
      {
        W1_best  = w1;
        Ve1_best = Ve;
      }
      if (lnW1dX_best > dlnw1_dx)
      {
        lnW1dX_best = dlnw1_dx;
        Ve2_best    = Ve;
      }
    }
    file << X << " " << Ve1_best << " " << Ve2_best << "\n";
    file.flush();
  }
  file.close();
}

/**
 * \brief    Compute mean population trajectory through time
 * \details  --
 * \param    int t
 * \param    double dt
 * \param    double Xbar_init
 * \param    double Vebar_init
 * \param    double Vgx
 * \param    double Vge
 * \param    double alpha
 * \param    double beta
 * \param    double Q
 * \param    double epsilon
 * \return   \e void
 */
void NumericalAnalysis::compute_trajectory( int t, double dt, double Xbar_init, double Vebar_init, double Vgx, double Vge, double alpha, double beta, double Q, double epsilon )
{
  std::ofstream file("trajectory.txt", std::ios::out | std::ios::trunc);
  file << "t dt X_bar Ve_bar\n";
  double X_bar  = Xbar_init;
  double Ve_bar = Vebar_init;
  double time   = 0.0;
  file << time << " " << dt << " " << X_bar << " " << Ve_bar << "\n";
  while (time <= t)
  {
    X_bar  += dlnW3_dX(X_bar, Ve_bar, Vgx, Vge, alpha, beta, Q, epsilon)*dt;
    Ve_bar += dlnW3_dVe(X_bar, Ve_bar, Vgx, Vge, alpha, beta, Q, epsilon)*dt;
    time   += dt;
    file << time << " " << dt << " " << X_bar << " " << Ve_bar << "\n";
    file.flush();
  }
  file.close();
}

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
  return gaussian_pdf(Ve, Ve_bar, Vge)*W2(X_bar, Vgx, fabs(Ve), alpha, beta, Q);
}

/**
 * \brief    Compute W1 = int[ p(z|X,Ve).W(z) dz ]
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
  gsl_integration_cquad_workspace* workspace = gsl_integration_cquad_workspace_alloc(LIMIT);
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
  size_t nevals;
  gsl_integration_cquad(&F, X-BOUNDARY, X+BOUNDARY, EPSABS, ESPREL, workspace, &result, &error, &nevals);
  gsl_integration_cquad_workspace_free(workspace);
  workspace = NULL;
  delete[] params;
  params = NULL;
  return result;
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
  if (Vgx < MIN_SIGMA)
  {
    return W1(X_bar, Ve, alpha, beta, Q);
  }
  
  /*-----------------------------*/
  /* 1) Declare GSL objects      */
  /*-----------------------------*/
  gsl_integration_cquad_workspace* workspace = gsl_integration_cquad_workspace_alloc(LIMIT);
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
  size_t nevals;
  gsl_integration_cquad(&F, X_bar-BOUNDARY, X_bar+BOUNDARY, EPSABS, ESPREL, workspace, &result, &error, &nevals);
  gsl_integration_cquad_workspace_free(workspace);
  workspace = NULL;
  delete[] params;
  params = NULL;
  return result;
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
  if (Vge < MIN_SIGMA)
  {
    return W2(X_bar, Vgx, Ve_bar, alpha, beta, Q);
  }
  
  /*-----------------------------*/
  /* 1) Declare GSL objects      */
  /*-----------------------------*/
  gsl_integration_cquad_workspace* workspace = gsl_integration_cquad_workspace_alloc(LIMIT);
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
  size_t nevals;
  gsl_integration_cquad(&F, Ve_bar-BOUNDARY, Ve_bar+BOUNDARY, EPSABS, ESPREL, workspace, &result, &error, &nevals);
  gsl_integration_cquad_workspace_free(workspace);
  workspace = NULL;
  delete[] params;
  params = NULL;
  return result;
}

/**
 * \brief    Compute dW/dz
 * \details  --
 * \param    double z
 * \param    double alpha
 * \param    double beta
 * \param    double Q
 * \param    double epsilon
 * \return   \e double
 */
double NumericalAnalysis::dW_dz( double z, double alpha, double beta, double Q, double epsilon )
{
  double v1 = W(z, alpha, beta, Q);
  double v2 = W(z+epsilon, alpha, beta, Q);
  return (v2-v1)/(epsilon);
}

/**
 * \brief    Compute dlnW/dz
 * \details  --
 * \param    double z
 * \param    double alpha
 * \param    double beta
 * \param    double Q
 * \param    double epsilon
 * \return   \e double
 */
double NumericalAnalysis::dlnW_dz( double z, double alpha, double beta, double Q, double epsilon )
{
  double v1 = log(W(z, alpha, beta, Q));
  double v2 = log(W(z+epsilon, alpha, beta, Q));
  return (v2-v1)/(epsilon);
}

/**
 * \brief    Compute dW1/dX
 * \details  --
 * \param    double X
 * \param    double Ve
 * \param    double alpha
 * \param    double beta
 * \param    double Q
 * \param    double epsilon
 * \return   \e double
 */
double NumericalAnalysis::dW1_dX( double X, double Ve, double alpha, double beta, double Q, double epsilon )
{
  double v1 = W1(X, Ve, alpha, beta, Q);
  double v2 = W1(X+epsilon, Ve, alpha, beta, Q);
  return (v2-v1)/(epsilon);
}

/**
 * \brief    Compute dW1/dVe
 * \details  --
 * \param    double X
 * \param    double Ve
 * \param    double alpha
 * \param    double beta
 * \param    double Q
 * \param    double epsilon
 * \return   \e double
 */
double NumericalAnalysis::dW1_dVe( double X, double Ve, double alpha, double beta, double Q, double epsilon )
{
  double v1 = W1(X, Ve, alpha, beta, Q);
  double v2 = W1(X, Ve+epsilon, alpha, beta, Q);
  return (v2-v1)/(epsilon);
}

/**
 * \brief    Compute d2W1/dXdVe
 * \details  --
 * \param    double X
 * \param    double Ve
 * \param    double alpha
 * \param    double beta
 * \param    double Q
 * \param    double epsilon
 * \return   \e double
 */
double NumericalAnalysis::d2W1_dXdVE( double X, double Ve, double alpha, double beta, double Q, double epsilon )
{
  double v1 = W1(X+epsilon, Ve+epsilon, alpha, beta, Q);
  double v2 = W1(X, Ve, alpha, beta, Q);
  double v3 = W1(X+epsilon, Ve, alpha, beta, Q);
  double v4 = W1(X, Ve+epsilon, alpha, beta, Q);
  return (v1+v2-v3-v4)/(epsilon*epsilon);
}

/**
 * \brief    Compute dlnW1/dX
 * \details  --
 * \param    double X
 * \param    double Ve
 * \param    double alpha
 * \param    double beta
 * \param    double Q
 * \param    double epsilon
 * \return   \e double
 */
double NumericalAnalysis::dlnW1_dX( double X, double Ve, double alpha, double beta, double Q, double epsilon )
{
  double v1 = W1(X, Ve, alpha, beta, Q);
  double v2 = W1(X+epsilon, Ve, alpha, beta, Q);
  return (v2-v1)/(epsilon*v1);
}

/**
 * \brief    Compute dlnW1/dVe
 * \details  --
 * \param    double X
 * \param    double Ve
 * \param    double alpha
 * \param    double beta
 * \param    double Q
 * \param    double epsilon
 * \return   \e double
 */
double NumericalAnalysis::dlnW1_dVe( double X, double Ve, double alpha, double beta, double Q, double epsilon )
{
  double v1 = W1(X, Ve, alpha, beta, Q);
  double v2 = W1(X, Ve+epsilon, alpha, beta, Q);
  return (v2-v1)/(epsilon*v1);
}

/**
 * \brief    Compute d2lnW1/dXdVe
 * \details  --
 * \param    double X
 * \param    double Ve
 * \param    double alpha
 * \param    double beta
 * \param    double Q
 * \param    double epsilon
 * \return   \e double
 */
double NumericalAnalysis::d2lnW1_dXdVE( double X, double Ve, double alpha, double beta, double Q, double epsilon )
{
  double v1 = W1(X+epsilon, Ve+epsilon, alpha, beta, Q);
  double v2 = W1(X, Ve, alpha, beta, Q);
  double v3 = W1(X+epsilon, Ve, alpha, beta, Q);
  double v4 = W1(X, Ve+epsilon, alpha, beta, Q);
  return (v1+v2-v3-v4)/(epsilon*epsilon*v2);
}

/**
 * \brief    Compute dlnW3/dX
 * \details  --
 * \param    double X_bar
 * \param    double Ve_bar
 * \param    double Vgx
 * \param    double Vge
 * \param    double alpha
 * \param    double beta
 * \param    double Q
 * \param    double epsilon
 * \return   \e double
 */
double NumericalAnalysis::dlnW3_dX( double X_bar, double Ve_bar, double Vgx, double Vge, double alpha, double beta, double Q, double epsilon )
{
  double v1 = W3(Ve_bar, Vge, X_bar, Vgx, alpha, beta, Q);
  double v2 = W3(Ve_bar, Vge, X_bar+epsilon, Vgx, alpha, beta, Q);
  return (v2-v1)/(epsilon*v1);
}

/**
 * \brief    Compute dlnW3/dVe
 * \details  --
 * \param    double X_bar
 * \param    double Ve_bar
 * \param    double Vgx
 * \param    double Vge
 * \param    double alpha
 * \param    double beta
 * \param    double Q
 * \param    double epsilon
 * \return   \e double
 */
double NumericalAnalysis::dlnW3_dVe( double X_bar, double Ve_bar, double Vgx, double Vge, double alpha, double beta, double Q, double epsilon )
{
  double v1 = W3(Ve_bar, Vge, X_bar, Vgx, alpha, beta, Q);
  double v2 = W3(Ve_bar+epsilon, Vge, X_bar, Vgx, alpha, beta, Q);
  return (v2-v1)/(epsilon*v1);
}

