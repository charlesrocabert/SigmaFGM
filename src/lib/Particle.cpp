
/**
 * \file      Particle.cpp
 * \authors   Charles Rocabert, Samuel Bernard
 * \date      07-06-2016
 * \copyright Copyright (C) 2016-2017 Charles Rocabert, Samuel Bernard. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     Particle class definition
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

#include "Particle.h"


/*----------------------------
 * CONSTRUCTORS
 *----------------------------*/

/**
 * \brief    Constructor
 * \details  --
 * \param    Prng* prng
 * \param    size_t n
 * \param    double delta_mu
 * \param    double delta_sigma
 * \param    double delta_theta
 * \param    double mu_init
 * \param    double sigma_init
 * \param    double theta_init
 * \param    bool one_axis
 * \param    bool weight_fitness
 * \param    bool no_noise
 * \param    bool no_rotation
 * \return   \e void
 */
Particle::Particle( Prng* prng, size_t n, double delta_mu, double delta_sigma, double delta_theta, double mu_init, double sigma_init, double theta_init, bool one_axis, bool weight_fitness, bool no_noise, bool no_rotation )
{
  /*----------------------------------------------- PARAMETERS */
  
  _prng           = prng;
  _n              = n;
  _delta_mu       = delta_mu;
  _delta_sigma    = delta_sigma;
  _delta_theta    = delta_theta;
  _weight_fitness = weight_fitness;
  _no_noise       = no_noise;
  _no_rotation    = no_rotation;
  
  /*----------------------------------------------- VARIABLES */
  
  /* Initialize matrices */
  _Sigma    = NULL;
  _Cholesky = NULL;
  
  /* Initialize mu */
  _mu = gsl_vector_alloc(_n);
  if (one_axis)
  {
    gsl_vector_set_zero(_mu);
    gsl_vector_set(_mu, 0, mu_init);
  }
  else
  {
    gsl_vector_set_all(_mu, mu_init);
  }
  
  /* Initialize sigma */
  _sigma = NULL;
  if (!_no_noise)
  {
    _sigma = gsl_vector_alloc(_n);
    gsl_vector_set_all(_sigma, sigma_init);
  }
  
  /* Initialize theta */
  _theta = NULL;
  if (!_no_noise && !_no_rotation && _n > 1)
  {
    _theta = gsl_vector_alloc(_n*(_n-1)/2);
    gsl_vector_set_all(_theta, theta_init);
  }
  
  /* Initialize z */
  _z = gsl_vector_alloc(_n);
  gsl_vector_set_zero(_z);
  
  /* Initialize other variables */
  _dmu = 0.0;
  _dp  = 0.0;
  _wmu = 0.0;
  _wp  = 0.0;
  
  /*----------------------------------------------- OTHER PARAMETERS */
  
  _phenotype_is_built     = false;
  _max_Sigma_eigenvector  = NULL;
  _max_Sigma_eigenvalue   = 0.0;
  _max_Sigma_contribution = 0.0;
  _max_dot_product        = 0.0;
}

/**
 * \brief    Copy constructor
 * \details  --
 * \param    const Particle& particle
 * \return   \e void
 */
Particle::Particle( const Particle& particle )
{
  /*----------------------------------------------- PARAMETERS */
  
  _prng           = particle._prng;
  _n              = particle._n;
  _delta_mu       = particle._delta_mu;
  _delta_sigma    = particle._delta_sigma;
  _delta_theta    = particle._delta_theta;
  _weight_fitness = particle._weight_fitness;
  _no_noise       = particle._no_noise;
  _no_rotation    = particle._no_rotation;
  
  /*----------------------------------------------- VARIABLES */
  
  /* Initialize matrices */
  _Sigma    = NULL;
  _Cholesky = NULL;
  
  /* Initialize mu */
  _mu = gsl_vector_alloc(_n);
  gsl_vector_memcpy(_mu, particle._mu);
  
  /* Initialize sigma */
  _sigma = NULL;
  if (!_no_noise)
  {
    _sigma = gsl_vector_alloc(_n);
    gsl_vector_memcpy(_sigma, particle._sigma);
  }
  
  /* Initialize theta */
  _theta = NULL;
  if (!_no_noise && !_no_rotation && _n > 1)
  {
    _theta = gsl_vector_alloc(_n*(_n-1)/2);
    gsl_vector_memcpy(_theta, particle._theta);
  }
  
  /* Initialize z */
  _z = gsl_vector_alloc(_n);
  gsl_vector_memcpy(_z, particle._z);
  
  /* Initialize other variables */
  _dmu = particle._dmu;
  _dp  = particle._dp;
  _wmu = particle._wmu;
  _wp  = particle._wp;
  
  /*----------------------------------------------- OTHER PARAMETERS */
  
  _phenotype_is_built     = false;
  _max_Sigma_eigenvector  = NULL;
  _max_Sigma_eigenvalue   = particle._max_Sigma_eigenvalue;
  _max_Sigma_contribution = particle._max_Sigma_contribution;
  _max_dot_product        = particle._max_dot_product;
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
Particle::~Particle( void )
{
  gsl_vector_free(_mu);
  _mu = NULL;
  if (!_no_noise)
  {
    gsl_vector_free(_sigma);
    _sigma = NULL;
    gsl_matrix_free(_Sigma);
    _Sigma = NULL;
    gsl_matrix_free(_Cholesky);
    _Cholesky = NULL;
    gsl_vector_free(_max_Sigma_eigenvector);
    _max_Sigma_eigenvector = NULL;
    if (_n > 1 && !_no_rotation)
    {
      gsl_vector_free(_theta);
      _theta = NULL;
    }
  }
  gsl_vector_free(_z);
  _z = NULL;
}

/*----------------------------
 * PUBLIC METHODS
 *----------------------------*/

/**
 * \brief    Jump in the profile space
 * \details  The profile space is the composition of mu, sigma and theta space --> (3n+n^2)/2 dimensions
 * \param    void
 * \return   \e void
 */
void Particle::jump( void )
{
  /**************************/
  /* 1) Mutate mu vector    */
  /**************************/
  if (_delta_mu > 0.0)
  {
    for (size_t i = 0; i < _n; i++)
    {
      gsl_vector_set(_mu, i, gsl_vector_get(_mu, i)+_prng->gaussian(0.0, _delta_mu));
    }
  }
  
  /**************************/
  /* 2) Mutate sigma vector */
  /**************************/
  if (!_no_noise && _delta_sigma > 0.0)
  {
    for (size_t i = 0; i < _n; i++)
    {
      gsl_vector_set(_sigma, i, fabs(gsl_vector_get(_sigma, i)+_prng->gaussian(0.0, _delta_sigma)));
    }
  }
  
  /**************************/
  /* 3) Mutate theta vector */
  /**************************/
  if (!_no_noise && !_no_rotation && _n > 1 && _delta_theta > 0.0)
  {
    for (size_t i = 0; i < _n*(_n-1)/2; i++)
    {
      gsl_vector_set(_theta, i, gsl_vector_get(_theta, i)+_prng->gaussian(0.0, _delta_theta));
    }
  }
  _phenotype_is_built = false;
}

/**
 * \brief    Build the phenotype
 * \details  If the mapping is not built, build it and draw z. Else just draw z
 * \param    void
 * \return   \e void
 */
void Particle::build_phenotype( void )
{
  if (!_phenotype_is_built)
  {
    if (!_no_noise)
    {
      build_Sigma();
      compute_dot_product();
      Cholesky_decomposition();
      clear_memory();
    }
    _phenotype_is_built = true;
  }
  draw_z();
}

/**
 * \brief    Compute the instantaneous fitness
 * \details  --
 * \param    gsl_vector* z_opt
 * \return   \e void
 */
void Particle::compute_fitness( gsl_vector* z_opt )
{
  _dmu = 0.0;
  _dp  = 0.0;
  for (size_t i = 0; i < _n; i++)
  {
    _dmu += (gsl_vector_get(_mu, i)-gsl_vector_get(z_opt, i))*(gsl_vector_get(_mu, i)-gsl_vector_get(z_opt, i));
    _dp  += (gsl_vector_get(_z, i)-gsl_vector_get(z_opt, i))*(gsl_vector_get(_z, i)-gsl_vector_get(z_opt, i));
  }
  _dmu = sqrt(_dmu);
  _dp  = sqrt(_dp);
  if (_weight_fitness)
  {
    _wmu = exp(-_dmu*_dmu/(2.0*_n));
    _wp  = exp(-_dp*_dp/(2.0*_n));
  }
  else
  {
    _wmu = exp(-_dmu*_dmu/2.0);
    _wp  = exp(-_dp*_dp/2.0);
  }
}

/**
 * \brief    Compute the phenotype distribution fitness
 * \details  --
 * \param    void
 * \return   \e void
 */
void Particle::compute_fitness_QAGI( void )
{
  if (_n > 1)
  {
    printf("Error in Particle::compute_fitness_QAGI(): this method is only available in 1D. Exit.\n");
    exit(EXIT_FAILURE);
  }
  if (_weight_fitness)
  {
    printf("Error in Particle::compute_fitness_QAGI(): this method doesn't work with option \"weight fitness\". Exit.\n");
    exit(EXIT_FAILURE);
  }
  _dmu = 0.0;
  _dp  = 0.0;
  _dmu += gsl_vector_get(_mu, 0)*gsl_vector_get(_mu, 0);
  _dp  += gsl_vector_get(_z, 0)*gsl_vector_get(_z, 0);
  _dmu = sqrt(_dmu);
  _dp  = sqrt(_dp);
  _wmu = exp(-_dmu*_dmu/2.0);
  double mu_vec[1];
  mu_vec[0] = gsl_vector_get(_mu, 0);
  double error;
  W(mu_vec, gsl_vector_get(_sigma, 0), _n, _wp, error);
}

/*----------------------------
 * PROTECTED METHODS
 *----------------------------*/

/**
 * \brief    Rotate the matrix m by angle theta on the plane (a, b)
 * \details  --
 * \param    size_t a
 * \param    size_t b
 * \param    double theta
 * \return   \e void
 */
void Particle::rotate( gsl_matrix* m, size_t a, size_t b, double theta )
{
  gsl_matrix* newm = gsl_matrix_alloc(_n, _n);
  gsl_matrix_memcpy(newm, m);
  for (size_t k = 0; k < _n; k++)
  {
    gsl_matrix_set(newm, a, k, cos(theta)*gsl_matrix_get(m, a, k)-sin(theta)*gsl_matrix_get(m, b, k));
    gsl_matrix_set(newm, b, k, sin(theta)*gsl_matrix_get(m, a, k)+cos(theta)*gsl_matrix_get(m, b, k));
  }
  gsl_matrix_memcpy(m, newm);
  gsl_matrix_free(newm);
  newm = NULL;
}

/**
 * \brief    Build the co-variance matrix Sigma
 * \details  --
 * \param    void
 * \return   \e void
 */
void Particle::build_Sigma( void )
{
  /*****************************************/
  /* 1) Create eigenvectors matrix         */
  /*****************************************/
  gsl_matrix* X = gsl_matrix_alloc(_n, _n);
  gsl_matrix_set_identity(X);
  
  /*****************************************/
  /* 2) Starting from identitity matrix,   */
  /*    apply the n(n-1)/2 rotations to    */
  /*    the eigenvectors                   */
  /*****************************************/
  if (!_no_rotation && _n > 1)
  {
    size_t counter = 0;
    for (size_t a = 0; a < _n; a++)
    {
      for (size_t b = a+1; b < _n; b++)
      {
        rotate(X, a, b, gsl_vector_get(_theta, counter));
        counter++;
      }
    }
    assert(counter == _n*(_n-1)/2);
  }
  
  /*****************************************/
  /* 3) Create the matrix D of eigenvalues */
  /*****************************************/
  _max_Sigma_eigenvalue  = 0.0;
  size_t max_sigma_index = 0;
  double sigma_sum       = 0.0;
  gsl_matrix* D = gsl_matrix_alloc(_n, _n);
  gsl_matrix_set_zero(D);
  for (size_t i = 0; i < _n; i++)
  {
    double sigma = gsl_vector_get(_sigma, i);
    gsl_matrix_set(D, i, i, sigma);
    sigma_sum += sigma;
    if (_max_Sigma_eigenvalue < sigma)
    {
      _max_Sigma_eigenvalue = sigma;
      max_sigma_index       = i;
    }
  }
  
  /*****************************************/
  /* 4) Save maximum eigenvector and       */
  /*    eigenvalue contribution            */
  /*****************************************/
  _max_Sigma_eigenvector  = gsl_vector_alloc(_n);
  _max_Sigma_contribution = _max_Sigma_eigenvalue/sigma_sum;
  for (size_t i = 0; i < _n; i++)
  {
    gsl_vector_set(_max_Sigma_eigenvector, i, gsl_matrix_get(X, i, max_sigma_index));
  }
  
  /*****************************************/
  /* 5) Compute Sigma = X * D * D^-1       */
  /*****************************************/
  gsl_matrix* P = gsl_matrix_alloc(_n, _n);
  _Sigma        = gsl_matrix_alloc(_n, _n);
  
  gsl_blas_dgemm(CblasNoTrans, CblasTrans, 1.0, D, X, 0.0, P);
  gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, X, P, 0.0, _Sigma);
  gsl_matrix_free(X);
  X = NULL;
  gsl_matrix_free(D);
  D = NULL;
  gsl_matrix_free(P);
  P = NULL;
}

/**
 * \brief    Compute the dot product between Sigma eigen vector and optimum direction
 * \details  --
 * \param    void
 * \return   \e void
 */
void Particle::compute_dot_product( void )
{
  _max_dot_product = 0.0;
  gsl_vector* d    = gsl_vector_alloc(_n);
  gsl_vector_set_zero(d);
  gsl_vector_sub(d, _mu);
  double norm = gsl_blas_dnrm2(d);
  for (size_t i = 0; i < _n; i++)
  {
    gsl_vector_set(d, i, gsl_vector_get(d, i)/norm);
  }
  gsl_blas_ddot(d, _max_Sigma_eigenvector, &_max_dot_product);
  gsl_vector_free(d);
  d = NULL;
  _max_dot_product = fabs(_max_dot_product);
}

/**
 * \brief    Compute cholesky decomposition
 * \details  --
 * \param    void
 * \return   \e void
 */
void Particle::Cholesky_decomposition( void )
{
  gsl_matrix_free(_Cholesky);
  _Cholesky = NULL;
  _Cholesky = gsl_matrix_alloc(_n, _n);
  gsl_matrix_memcpy(_Cholesky, _Sigma);
  gsl_linalg_cholesky_decomp(_Cholesky);
  /* L est dans le triangle inférieur */
}

/**
 * \brief    Draw the phenotype z in a multivariate normal law N(_mu, _Sigma)
 * \details  In details, we apply the cholesky decomposition method to transform centered-reduced normal points.
 * \param    void
 * \return   \e void
 */
void Particle::draw_z( void )
{
  if (_no_noise)
  {
    /* Copy mu vector in z vector */
    gsl_vector_memcpy(_z, _mu);
  }
  else
  {
    /* Draw the uniform vector N(0,1) */
    for (size_t i = 0; i < _n; i++)
    {
      gsl_vector_set(_z, i, _prng->gaussian(0.0, 1.0));
    }
    
    /* Apply cholesky matrix */
    gsl_blas_dtrmv(CblasLower, CblasNoTrans, CblasNonUnit, _Cholesky, _z);
    gsl_vector_add(_z, _mu);
  }
}

/**
 * \brief    Clear the memory
 * \details  --
 * \param    void
 * \return   \e void
 */
void Particle::clear_memory( void )
{
  gsl_matrix_free(_Sigma);
  _Sigma = NULL;
  gsl_vector_free(_max_Sigma_eigenvector);
  _max_Sigma_eigenvector = NULL;
}

/**
 * \brief    Simple gaussian law pdf
 * \details  --
 * \param    double x
 * \param    double mu
 * \param    double sigma
 * \return   \e double
 */
double Particle::gaussian_pdf( double x, double mu, double sigma )
{
  return gsl_ran_gaussian_pdf(x-mu, sigma);
}

/**
 * \brief    Compute the most basic FGM fitness
 * \details  --
 * \param    double x
 * \return   \e double
 */
double Particle::w( double x )
{
  return exp(-x*x/2);
}

/**
 * \brief    Compute one 1d integration point
 * \details  --
 * \param    double x
 * \return   \e double
 */
double Particle::f( double x, void* params )
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
void Particle::QAGI( double* res, double mu, double sigma, gsl_integration_workspace* workspace, gsl_function* F )
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
 * \brief    Compute the complete integral
 * \details  --
 * \param    double* mu
 * \param    double sigma
 * \param    size_t n
 * \param    double& result
 * \param    double& error
 * \return   \e void
 */
void Particle::W( double* mu, double sigma, size_t n, double& result, double& error )
{
  gsl_integration_workspace* workspace = gsl_integration_workspace_alloc(LIMIT);
  gsl_function F;
  F.function  = &(Particle::f);
  F.params    = NULL;
  result      = 1.0;
  error       = 0.0;
  double* res = new double[2];
  for (size_t i = 0; i < n; i++)
  {
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
