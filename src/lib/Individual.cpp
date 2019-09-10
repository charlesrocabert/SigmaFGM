
/**
 * \file      Individual.cpp
 * \authors   Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon
 * \date      28-03-2018
 * \copyright Copyright (C) 2016-2019 Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     Individual class definition
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

#include "Individual.h"


/*----------------------------
 * CONSTRUCTORS
 *----------------------------*/

/**
 * \brief    Constructor
 * \details  --
 * \param    Prng* prng
 * \param    int n
 * \param    double X_init
 * \param    double Ve_init
 * \param    double Theta_init
 * \param    bool oneD_shift
 * \param    bool type_of_noise noise_type
 * \param    gsl_vector* z_opt
 * \return   \e void
 */
Individual::Individual( Prng* prng, int n, double X_init, double Ve_init, double Theta_init, bool oneD_shift, type_of_noise noise_type, gsl_vector* z_opt )
{
  /*----------------------------------------------- PARAMETERS */
  
  _prng       = prng;
  _n          = n;
  _noise_type = noise_type;
  _z_opt      = z_opt;
  
  /*----------------------------------------------- VARIABLES */
  
  _identifier = 0;
  _generation = 0;
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 1) Initialize matrices        */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  _Sigma    = NULL;
  _Cholesky = NULL;
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 2) Initialize X               */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  _X = gsl_vector_alloc(_n);
  if (oneD_shift)
  {
    gsl_vector_set_zero(_X);
    gsl_vector_set(_X, 0, X_init);
  }
  else
  {
    gsl_vector_set_all(_X, X_init);
  }
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 3) Initialize Ve              */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  _Ve = NULL;
  if (_noise_type != NONE)
  {
    _Ve = gsl_vector_alloc(_n);
    gsl_vector_set_all(_Ve, Ve_init);
  }
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 4) Initialize Theta           */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  _Theta = NULL;
  if (_n > 1 && _noise_type == FULL)
  {
    _Theta = gsl_vector_alloc(_n*(_n-1)/2);
    gsl_vector_set_all(_Theta, Theta_init);
  }
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 5) Initialize z               */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  _z = gsl_vector_alloc(_n);
  gsl_vector_set_zero(_z);
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 6) Initialize other variables */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  _dX = 0.0;
  _dz = 0.0;
  _WX = 0.0;
  _Wz = 0.0;
  
  /*----------------------------------------------- MAPPING PROPERTIES */
  
  _phenotype_is_built     = false;
  _max_Sigma_eigenvector  = NULL;
  _max_Sigma_eigenvalue   = 0.0;
  _max_Sigma_contribution = 0.0;
  _max_dot_product        = 0.0;
  
  /*----------------------------------------------- MUTATIONS */
  
  _r_X     = 0.0;
  _r_Ve    = 0.0;
  _r_Theta = 0.0;
}

/**
 * \brief    Copy constructor
 * \details  --
 * \param    const Individual& individual
 * \return   \e void
 */
Individual::Individual( const Individual& individual )
{
  /*----------------------------------------------- PARAMETERS */
  
  _prng       = individual._prng;
  _n          = individual._n;
  _noise_type = individual._noise_type;
  _z_opt      = individual._z_opt;
  
  /*----------------------------------------------- VARIABLES */
  
  _identifier = individual._identifier;
  _generation = individual._generation;
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 1) Initialize matrices        */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  _Sigma    = NULL;
  _Cholesky = NULL;
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 2) Initialize X               */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  _X = gsl_vector_alloc(_n);
  gsl_vector_memcpy(_X, individual._X);
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 3) Initialize Ve              */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  _Ve = NULL;
  if (_noise_type != NONE)
  {
    _Ve = gsl_vector_alloc(_n);
    gsl_vector_memcpy(_Ve, individual._Ve);
  }
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 4) Initialize Theta           */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  _Theta = NULL;
  if (_n > 1 && _noise_type == FULL)
  {
    _Theta = gsl_vector_alloc(_n*(_n-1)/2);
    gsl_vector_memcpy(_Theta, individual._Theta);
  }
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 5) Initialize z               */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  _z = gsl_vector_alloc(_n);
  gsl_vector_memcpy(_z, individual._z);
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 6) Initialize other variables */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  _dX = individual._dX;
  _dz = individual._dz;
  _WX = individual._WX;
  _Wz = individual._Wz;
  
  /*----------------------------------------------- MAPPING PROPERTIES */
  
  _phenotype_is_built     = false;
  _max_Sigma_eigenvector  = NULL;
  _max_Sigma_eigenvalue   = individual._max_Sigma_eigenvalue;
  _max_Sigma_contribution = individual._max_Sigma_contribution;
  _max_dot_product        = individual._max_dot_product;
  
  /*----------------------------------------------- MUTATIONS */
  
  _r_X     = individual._r_X;
  _r_Ve    = individual._r_Ve;
  _r_Theta = individual._r_Theta;
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
Individual::~Individual( void )
{
  _prng  = NULL;
  _z_opt = NULL;
  gsl_vector_free(_X);
  _X = NULL;
  if (_noise_type != NONE)
  {
    gsl_vector_free(_Ve);
    _Ve = NULL;
    gsl_matrix_free(_Sigma);
    _Sigma = NULL;
    gsl_matrix_free(_Cholesky);
    _Cholesky = NULL;
    gsl_vector_free(_max_Sigma_eigenvector);
    _max_Sigma_eigenvector = NULL;
    if (_n > 1 && _noise_type == FULL)
    {
      gsl_vector_free(_Theta);
      _Theta = NULL;
    }
  }
  gsl_vector_free(_z);
  _z = NULL;
}

/*----------------------------
 * PUBLIC METHODS
 *----------------------------*/

/**
 * \brief    Mutate the individual genotype
 * \details  --
 * \param    double m_X
 * \param    double m_Ve
 * \param    double m_Theta
 * \param    double s_X
 * \param    double s_Ve
 * \param    double s_Theta
 * \return   \e void
 */
void Individual::mutate( double m_X, double m_Ve, double m_Theta, double s_X, double s_Ve, double s_Theta )
{
  gsl_vector* previous_X     = NULL;
  gsl_vector* previous_Ve    = NULL;
  gsl_vector* previous_Theta = NULL;
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 1) Save current genotype  */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  previous_X = gsl_vector_alloc(_n);
  gsl_vector_memcpy(previous_X, _X);
  if (_noise_type != NONE)
  {
    previous_Ve = gsl_vector_alloc(_n);
    gsl_vector_memcpy(previous_Ve, _Ve);
    if (_n > 1 && _noise_type == FULL)
    {
      previous_Theta = gsl_vector_alloc(_n*(_n-1)/2);
      gsl_vector_memcpy(previous_Theta, _Theta);
    }
  }
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 2) Mutate X vector        */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  if (_prng->uniform() < m_X)
  {
    for (int i = 0; i < _n; i++)
    {
      gsl_vector_set(_X, i, gsl_vector_get(_X, i)+_prng->gaussian(0.0, s_X));
    }
    _phenotype_is_built = false;
  }
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 3) Mutate Ve vector       */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  if (_noise_type != NONE && _prng->uniform() < m_Ve)
  {
    if (_noise_type == ISOTROPIC)
    {
      double new_Ve = fabs(gsl_vector_get(_Ve, 0)+_prng->gaussian(0.0, s_Ve));
      gsl_vector_set_all(_Ve, new_Ve);
    }
    else if (_noise_type == UNCORRELATED || _noise_type == FULL)
    {
      for (int i = 0; i < _n; i++)
      {
        gsl_vector_set(_Ve, i, fabs(gsl_vector_get(_Ve, i)+_prng->gaussian(0.0, s_Ve)));
      }
    }
    _phenotype_is_built = false;
  }
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 4) Mutate Theta vector    */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  if (_n > 1 && _noise_type == FULL && _prng->uniform() < m_Theta)
  {
    for (int i = 0; i < _n*(_n-1)/2; i++)
    {
      gsl_vector_set(_Theta, i, gsl_vector_get(_Theta, i)+_prng->gaussian(0.0, s_Theta));
    }
  }
  _phenotype_is_built = false;
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 5) Compute mutation sizes */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  _r_X     = 0.0;
  _r_Ve    = 0.0;
  _r_Theta = 0.0;
  for (int i = 0; i < _n; i++)
  {
    double p_X  = gsl_vector_get(previous_X, i);
    double X    = gsl_vector_get(_X, i);
    _r_X       += (X-p_X)*(X-p_X);
    if (_noise_type != NONE)
    {
      double p_Ve  = gsl_vector_get(previous_Ve, i);
      double Ve    = gsl_vector_get(_Ve, i);
      _r_Ve       += (Ve-p_Ve)*(Ve-p_Ve);
    }
  }
  if (_n > 1 && _noise_type == FULL)
  {
    for (int i = 0; i < _n*(_n-1)/2; i++)
    {
      double p_Theta  = gsl_vector_get(previous_Theta, i);
      double Theta    = gsl_vector_get(_Theta, i);
      _r_Theta       += (Theta-p_Theta)*(Theta-p_Theta);
    }
  }
  
  _r_X     = sqrt(_r_X);
  _r_Ve    = sqrt(_r_Ve);
  _r_Theta = sqrt(_r_Theta);
  gsl_vector_free(previous_X);
  previous_X = NULL;
  gsl_vector_free(previous_Ve);
  previous_Ve = NULL;
  gsl_vector_free(previous_Theta);
  previous_Theta = NULL;
}

/**
 * \brief    Build the phenotype
 * \details  If the mapping is not built, build it and draw z. Else just draw z
 * \param    void
 * \return   \e void
 */
void Individual::build_phenotype( void )
{
  if (!_phenotype_is_built)
  {
    if (_noise_type != NONE)
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
 * \brief    Compute the fitness
 * \details  --
 * \param    double alpha
 * \param    double beta
 * \param    double Q
 * \return   \e void
 */
void Individual::compute_fitness( double alpha, double beta, double Q )
{
  _dX = 0.0;
  _dz = 0.0;
  for (int i = 0; i < _n; i++)
  {
    double X_diff  = gsl_vector_get(_X, i)-gsl_vector_get(_z_opt, i);
    double z_diff  = gsl_vector_get(_z, i)-gsl_vector_get(_z_opt, i);
    _dX           += X_diff*X_diff;
    _dz           += z_diff*z_diff;
  }
  _dX = sqrt(_dX);
  _dz = sqrt(_dz);
  _WX = (1.0-beta)*exp(-alpha*pow(_dX, Q))+beta;
  _Wz = (1.0-beta)*exp(-alpha*pow(_dz, Q))+beta;
}

/**
 * \brief    Compute the mean fitness
 * \details  --
 * \param    double alpha
 * \param    double beta
 * \param    double Q
 * \return   \e void
 */
void Individual::compute_mean_fitness( double alpha, double beta, double Q )
{
  double mean_WX = 0.0;
  double mean_Wz = 0.0;
  for (int i = 0; i < 1000; i++)
  {
    draw_z();
    compute_fitness(alpha, beta, Q);
    mean_WX += _WX;
    mean_Wz += _Wz;
  }
  _WX = mean_WX/1000.0;
  _Wz = mean_Wz/1000.0;
}

/*----------------------------
 * PROTECTED METHODS
 *----------------------------*/

/**
 * \brief    Rotate the matrix m by angle theta on the plane (a, b)
 * \details  --
 * \param    int a
 * \param    int b
 * \param    double theta
 * \return   \e void
 */
void Individual::rotate( gsl_matrix* m, int a, int b, double theta )
{
  gsl_matrix* newm = gsl_matrix_alloc(_n, _n);
  gsl_matrix_memcpy(newm, m);
  for (int k = 0; k < _n; k++)
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
void Individual::build_Sigma( void )
{
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 1) Create eigenvectors matrix         */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  gsl_matrix* X = gsl_matrix_alloc(_n, _n);
  gsl_matrix_set_identity(X);
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 2) Starting from identity matrix,     */
  /*    apply the n(n-1)/2 rotations to    */
  /*    the eigenvectors                   */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  if (_n > 1 && _noise_type == FULL)
  {
    int counter = 0;
    for (int a = 0; a < _n; a++)
    {
      for (int b = a+1; b < _n; b++)
      {
        rotate(X, a, b, gsl_vector_get(_Theta, counter));
        counter++;
      }
    }
    assert(counter == _n*(_n-1)/2);
  }
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 3) Create the matrix D of eigenvalues */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  _max_Sigma_eigenvalue = 0.0;
  int max_Ve_index      = 0;
  double Ve_sum         = 0.0;
  gsl_matrix* D = gsl_matrix_alloc(_n, _n);
  gsl_matrix_set_zero(D);
  for (int i = 0; i < _n; i++)
  {
    double Ve = gsl_vector_get(_Ve, i);
    gsl_matrix_set(D, i, i, Ve);
    Ve_sum += Ve;
    if (_max_Sigma_eigenvalue < Ve)
    {
      _max_Sigma_eigenvalue = Ve;
      max_Ve_index          = i;
    }
  }
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 4) Save maximum eigenvector and       */
  /*    eigenvalue contribution            */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  _max_Sigma_eigenvector  = gsl_vector_alloc(_n);
  _max_Sigma_contribution = _max_Sigma_eigenvalue/Ve_sum;
  for (int i = 0; i < _n; i++)
  {
    gsl_vector_set(_max_Sigma_eigenvector, i, gsl_matrix_get(X, i, max_Ve_index));
  }
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 5) Compute Sigma = X * D * X^-1       */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
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
void Individual::compute_dot_product( void )
{
  _max_dot_product = 0.0;
  gsl_vector* d    = gsl_vector_alloc(_n);
  gsl_vector_memcpy(d, _z_opt);
  gsl_vector_sub(d, _X);
  double norm = gsl_blas_dnrm2(d);
  for (int i = 0; i < _n; i++)
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
void Individual::Cholesky_decomposition( void )
{
  gsl_matrix_free(_Cholesky);
  _Cholesky = NULL;
  _Cholesky = gsl_matrix_alloc(_n, _n);
  gsl_matrix_memcpy(_Cholesky, _Sigma);
  gsl_linalg_cholesky_decomp(_Cholesky);
  /* L est dans le triangle inférieur */
}

/**
 * \brief    Draw the phenotype z in a multivariate normal law N(_X, _Ve)
 * \details  In details, we apply the cholesky decomposition method to transform centered-reduced normal points.
 * \param    void
 * \return   \e void
 */
void Individual::draw_z( void )
{
  if (_noise_type == NONE)
  {
    /* Copy mu vector in z vector */
    gsl_vector_memcpy(_z, _X);
  }
  else
  {
    /* Draw the uniform vector N(0,1) */
    for (int i = 0; i < _n; i++)
    {
      gsl_vector_set(_z, i, _prng->gaussian(0.0, 1.0));
    }
    
    /* Apply cholesky matrix */
    gsl_blas_dtrmv(CblasLower, CblasNoTrans, CblasNonUnit, _Cholesky, _z);
    gsl_vector_add(_z, _X);
  }
}

/**
 * \brief    Clear the memory
 * \details  --
 * \param    void
 * \return   \e void
 */
void Individual::clear_memory( void )
{
  gsl_matrix_free(_Sigma);
  _Sigma = NULL;
  gsl_vector_free(_max_Sigma_eigenvector);
  _max_Sigma_eigenvector = NULL;
}

/**
 * \brief    Delete all vectors and matrices
 * \details  --
 * \param    void
 * \return   \e void
 */
void Individual::delete_vectors_and_matrices( void )
{
  gsl_vector_free(_X);
  _X = NULL;
  if (_noise_type != NONE)
  {
    gsl_vector_free(_Ve);
    _Ve = NULL;
    gsl_matrix_free(_Sigma);
    _Sigma = NULL;
    gsl_matrix_free(_Cholesky);
    _Cholesky = NULL;
    gsl_vector_free(_max_Sigma_eigenvector);
    _max_Sigma_eigenvector = NULL;
    if (_n > 1 && _noise_type == FULL)
    {
      gsl_vector_free(_Theta);
      _Theta = NULL;
    }
  }
  gsl_vector_free(_z);
  _z = NULL;
}

