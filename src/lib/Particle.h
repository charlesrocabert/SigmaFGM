
/**
 * \file      Particle.h
 * \authors   Charles Rocabert, Samuel Bernard
 * \date      07-06-2016
 * \copyright Copyright (C) 2016-2017 Charles Rocabert, Samuel Bernard. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     Particle class declaration
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

#ifndef __NoisyFGM__Particle__
#define __NoisyFGM__Particle__

#include <iostream>
#include <cmath>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_randist.h>
#include <assert.h>

#include "Macros.h"
#include "Prng.h"


class Particle
{
  
public:
  
  /*----------------------------
   * CONSTRUCTORS
   *----------------------------*/
  Particle( void ) = delete;
  Particle( Prng* prng, size_t n, double delta_mu, double delta_sigma, double delta_theta, double mu_init, double sigma_init, double theta_init, bool one_axis, bool weight_fitness, bool no_noise, bool isotropic_noise, bool no_rotation );
  Particle( const Particle& particle );
  
  /*----------------------------
   * DESTRUCTORS
   *----------------------------*/
  ~Particle( void );
  
  /*----------------------------
   * GETTERS
   *----------------------------*/
  inline double get_mu( size_t i ) const;
  inline double get_sigma( size_t i ) const;
  inline double get_theta( size_t i ) const;
  inline double get_dmu( void ) const;
  inline double get_dp( void ) const;
  inline double get_wmu( void ) const;
  inline double get_wp( void ) const;
  inline double get_max_Sigma_eigenvalue( void ) const;
  inline double get_max_Sigma_contribution( void ) const;
  inline double get_max_dot_product( void ) const;
  
  /*----------------------------
   * SETTERS
   *----------------------------*/
  Particle& operator=(const Particle&) = delete;
  
  /*----------------------------
   * PUBLIC METHODS
   *----------------------------*/
  void jump( void );
  void build_phenotype( void );
  void compute_fitness( gsl_vector* z_opt );
  void compute_fitness_QAGI( void );
  
  /*----------------------------
   * PUBLIC ATTRIBUTES
   *----------------------------*/
  
protected:
  
  /*----------------------------
   * PROTECTED METHODS
   *----------------------------*/
  void rotate( gsl_matrix* m, size_t a, size_t b, double theta );
  void build_Sigma( void );
  void compute_dot_product( void );
  void Cholesky_decomposition( void );
  void draw_z( void );
  void clear_memory( void );
  
  static double gaussian_pdf( double x, double mu, double sigma );
  static double w( double x );
  static double f( double x, void* params );
  void          QAGI( double* res, double mu, double sigma, gsl_integration_workspace* workspace, gsl_function* F );
  void          W( double* mu, double sigma, size_t n, double& result, double& error );
  
  /*----------------------------
   * PROTECTED ATTRIBUTES
   *----------------------------*/
  
  /*----------------------------------------------- PARAMETERS */
  
  Prng*  _prng;            /*!< Pseudorandom numbers generator                 */
  size_t _n;               /*!< Number of dimensions                           */
  double _delta_mu;        /*!< Mu values mutation size                        */
  double _delta_sigma;     /*!< Sigma values mutation size                     */
  double _delta_theta;     /*!< Theta values mutation size                     */
  bool   _weight_fitness;  /*!< Indicates if the fitness must be weighted by n */
  bool   _no_noise;        /*!< Indicates if the noise must be applied         */
  bool   _isotropic_noise; /*!< Indicates if the noise is isotropic            */
  bool   _no_rotation;     /*!< Indicates if rotations must be applied         */
  
  /*----------------------------------------------- VARIABLES */
  
  gsl_vector* _mu;       /*!< Mu vector                     */
  gsl_vector* _sigma;    /*!< Sigma vector                  */
  gsl_vector* _theta;    /*!< Theta vector                  */
  gsl_matrix* _Sigma;    /*!< Co-variance matrix            */
  gsl_matrix* _Cholesky; /*!< Cholesky decomposition matrix */
  gsl_vector* _z;        /*!< Instantaneous phenotype       */
  double      _dmu;      /*!< Mean distance                 */
  double      _dp;       /*!< Instantaneous distance        */
  double      _wmu;      /*!< Mean fitness                  */
  double      _wp;       /*!< Instantaneous fitness         */
  
  /*----------------------------------------------- OTHER PARAMETERS */
  
  bool        _phenotype_is_built;     /*!< Indicates if the phenotype is built                             */
  gsl_vector* _max_Sigma_eigenvector;  /*!< Eigen vector corresponding to the maximum variance of Sigma     */
  double      _max_Sigma_eigenvalue;   /*!< Eigen value corresponding to the maximum variance of Sigma      */
  double      _max_Sigma_contribution; /*!< Eigen value contribution to the total variance                  */
  double      _max_dot_product;        /*!< Dot product of maximum Sigma eigen vector and optimum direction */
};


/*----------------------------
 * GETTERS
 *----------------------------*/

/**
 * \brief    Get mu value at position i
 * \details  --
 * \param    size_t i
 * \return   \e double
 */
inline double Particle::get_mu( size_t i ) const
{
  assert(i < _n);
  return gsl_vector_get(_mu, i);
}

/**
 * \brief    Get sigma value at position i
 * \details  --
 * \param    size_t i
 * \return   \e double
 */
inline double Particle::get_sigma( size_t i ) const
{
  assert(i < _n);
  return gsl_vector_get(_sigma, i);
}

/**
 * \brief    Get theta value at position i
 * \details  --
 * \param    size_t i
 * \return   \e double
 */
inline double Particle::get_theta( size_t i ) const
{
  assert(i < _n*(_n-1)/2);
  return gsl_vector_get(_theta, i);
}

/**
 * \brief    Get the mean distance dmu
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Particle::get_dmu( void ) const
{
  return _dmu;
}

/**
 * \brief    Get the instantaneous distance dp
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Particle::get_dp( void ) const
{
  return _dp;
}

/**
 * \brief    Get the mean fitness wmu
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Particle::get_wmu( void ) const
{
  return _wmu;
}

/**
 * \brief    Get the instantaneous fitness wp
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Particle::get_wp( void ) const
{
  return _wp;
}

/**
 * \brief    Get the maximum eigen value of Sigma
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Particle::get_max_Sigma_eigenvalue( void ) const
{
  return _max_Sigma_eigenvalue;
}

/**
 * \brief    Get the maximum eigen value contribution
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Particle::get_max_Sigma_contribution( void ) const
{
  return _max_Sigma_contribution;
}

/**
 * \brief    Get the dot product between Sigma maximum eigen vector and optimum direction
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Particle::get_max_dot_product( void ) const
{
  return _max_dot_product;
}

/*----------------------------
 * SETTERS
 *----------------------------*/


#endif /* defined(__NoisyFGM__Particle__) */
