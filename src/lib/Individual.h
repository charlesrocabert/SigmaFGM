
/**
 * \file      Individual.h
 * \authors   Charles Rocabert, Guillaume Beslon, Carole Knibbe, Samuel Bernard
 * \date      28-03-2018
 * \copyright Copyright (C) 2016-2020 Charles Rocabert, Guillaume Beslon, Carole Knibbe, Samuel Bernard. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     Individual class declaration
 */

/***********************************************************************
 * Copyright (C) 2016-2020
 * Charles Rocabert, Guillaume Beslon, Carole Knibbe, Samuel Bernard
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

#ifndef __SigmaFGM__Individual__
#define __SigmaFGM__Individual__

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <gsl/gsl_math.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_randist.h>
#include <assert.h>

#include "Macros.h"
#include "Enums.h"
#include "Prng.h"


class Individual
{
  
public:
  
  /*----------------------------
   * CONSTRUCTORS
   *----------------------------*/
  Individual( void ) = delete;
  Individual( Prng* prng, int n, double mu_init, double sigma_init, double theta_init, bool oneD_shift, type_of_noise noise_type, gsl_vector* z_opt );
  Individual( const Individual& individual );
  
  /*----------------------------
   * DESTRUCTORS
   *----------------------------*/
  ~Individual( void );
  
  /*----------------------------
   * GETTERS
   *----------------------------*/
  
  /*----------------------------------------------- VARIABLES */
  
  inline unsigned long long int get_identifier( void ) const;
  inline int                    get_generation( void ) const;
  inline double                 get_mu( int i ) const;
  inline double                 get_sigma( int i ) const;
  inline double                 get_theta( int i ) const;
  inline double                 get_dmu( void ) const;
  inline double                 get_dz( void ) const;
  inline double                 get_Wmu( void ) const;
  inline double                 get_Wz( void ) const;
  
  /*----------------------------------------------- MAPPING PROPERTIES */
  
  inline double get_max_Sigma_eigenvalue( void ) const;
  inline double get_max_Sigma_contribution( void ) const;
  inline double get_max_dot_product( void ) const;
  
  /*----------------------------------------------- MUTATIONS */
  
  inline double get_r_mu( void ) const;
  inline double get_r_sigma( void ) const;
  inline double get_r_theta( void ) const;
  
  /*----------------------------
   * SETTERS
   *----------------------------*/
  Individual& operator=(const Individual&) = delete;
  
  inline void set_identifier( unsigned long long int identifier );
  inline void set_generation( int generation );
  
  /*----------------------------
   * PUBLIC METHODS
   *----------------------------*/
  void mutate( double m_mu, double m_sigma, double m_theta, double s_mu, double s_sigma, double s_theta );
  void build_phenotype( void );
  void compute_fitness( double alpha, double beta, double Q );
  void compute_mean_fitness( double alpha, double beta, double Q );
  void delete_vectors_and_matrices( void );
  void write_mu( int generation );
  void write_sigma( int generation );
  void write_theta( int generation );
  
  /*----------------------------
   * PUBLIC ATTRIBUTES
   *----------------------------*/
  
protected:
  
  /*----------------------------
   * PROTECTED METHODS
   *----------------------------*/
  void rotate( gsl_matrix* m, int a, int b, double theta );
  void build_Sigma( void );
  void compute_dot_product( void );
  void Cholesky_decomposition( void );
  void draw_z( void );
  void clear_memory( void );
  
  /*----------------------------
   * PROTECTED ATTRIBUTES
   *----------------------------*/
  
  /*----------------------------------------------- PARAMETERS */
  
  Prng*         _prng;       /*!< Pseudorandom numbers generator */
  int           _n;          /*!< Number of dimensions           */
  type_of_noise _noise_type; /*!< Phenotypic noise properties    */
  gsl_vector*   _z_opt;      /*!< Fitness optimum                */
  
  /*----------------------------------------------- VARIABLES */
  
  unsigned long long int _identifier; /*!< Individual's identifier       */
  int                    _generation; /*!< Individual's generation       */
  gsl_vector*            _mu;         /*!< mu vector                     */
  gsl_vector*            _sigma;      /*!< sigma vector                  */
  gsl_vector*            _theta;      /*!< theta vector                  */
  gsl_matrix*            _Sigma;      /*!< Co-variance matrix            */
  gsl_matrix*            _Cholesky;   /*!< Cholesky decomposition matrix */
  gsl_vector*            _z;          /*!< Instantaneous phenotype       */
  double                 _dmu;        /*!< Euclidean distance d(mu)      */
  double                 _dz;         /*!< Euclidean distance d(z)       */
  double                 _Wmu;        /*!< Fitness W(mu)                 */
  double                 _Wz;         /*!< Fitness W(z)                  */
  
  /*----------------------------------------------- MAPPING PROPERTIES */
  
  bool        _phenotype_is_built;     /*!< Indicates if the phenotype is built                             */
  gsl_vector* _max_Sigma_eigenvector;  /*!< Eigen vector corresponding to the maximum variance of Sigma     */
  double      _max_Sigma_eigenvalue;   /*!< Eigen value corresponding to the maximum variance of Sigma      */
  double      _max_Sigma_contribution; /*!< Eigen value contribution to the total variance                  */
  double      _max_dot_product;        /*!< Dot product of maximum Sigma eigen vector and optimum direction */
  
  /*----------------------------------------------- MUTATIONS */
  
  double _r_mu;    /*!< Euclidean size of mu mutation    */
  double _r_sigma; /*!< Euclidean size of sigma mutation */
  double _r_theta; /*!< Euclidean size of theta mutation */
  
};


/*----------------------------
 * GETTERS
 *----------------------------*/

/*----------------------------------------------- VARIABLES */

/**
 * \brief    Get individual's identifier
 * \details  --
 * \param    void
 * \return   \e unsigned long long int
 */
inline unsigned long long int Individual::get_identifier( void ) const
{
  return _identifier;
}

/**
 * \brief    Get individual's generation
 * \details  --
 * \param    void
 * \return   \e int
 */
inline int Individual::get_generation( void ) const
{
  return _generation;
}

/**
 * \brief    Get mu value at position i
 * \details  --
 * \param    int i
 * \return   \e double
 */
inline double Individual::get_mu( int i ) const
{
  assert(i < _n);
  return gsl_vector_get(_mu, i);
}

/**
 * \brief    Get sigma value at position i
 * \details  --
 * \param    int i
 * \return   \e double
 */
inline double Individual::get_sigma( int i ) const
{
  assert(i < _n);
  return gsl_vector_get(_sigma, i);
}

/**
 * \brief    Get theta value at position i
 * \details  --
 * \param    int i
 * \return   \e double
 */
inline double Individual::get_theta( int i ) const
{
  assert(i < _n*(_n-1)/2);
  return gsl_vector_get(_theta, i);
}

/**
 * \brief    Get the euclidean distance d(mu)
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Individual::get_dmu( void ) const
{
  return _dmu;
}

/**
 * \brief    Get the euclidean distance d(z)
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Individual::get_dz( void ) const
{
  return _dz;
}

/**
 * \brief    Get the fitness W(mu)
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Individual::get_Wmu( void ) const
{
  return _Wmu;
}

/**
 * \brief    Get the fitness W(z)
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Individual::get_Wz( void ) const
{
  return _Wz;
}

/*----------------------------------------------- MAPPING PROPERTIES */

/**
 * \brief    Get the maximum eigen value of Sigma
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Individual::get_max_Sigma_eigenvalue( void ) const
{
  return _max_Sigma_eigenvalue;
}

/**
 * \brief    Get the maximum eigen value contribution
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Individual::get_max_Sigma_contribution( void ) const
{
  return _max_Sigma_contribution;
}

/**
 * \brief    Get the dot product between Sigma maximum eigen vector and optimum direction
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Individual::get_max_dot_product( void ) const
{
  return _max_dot_product;
}

/*----------------------------------------------- MUTATIONS */

/**
 * \brief    Get the euclidean size of mu mutation
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Individual::get_r_mu( void ) const
{
  return _r_mu;
}

/**
 * \brief    Get the euclidean size of sigma mutation
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Individual::get_r_sigma( void ) const
{
  return _r_sigma;
}

/**
 * \brief    Get the euclidean size of theta mutation
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Individual::get_r_theta( void ) const
{
  return _r_theta;
}

/*----------------------------
 * SETTERS
 *----------------------------*/

/*----------------------------------------------- VARIABLES */

/**
 * \brief    Set individual's identifier
 * \details  --
 * \param    unsigned long long int identifier
 * \return   \e void
 */
inline void Individual::set_identifier( unsigned long long int identifier )
{
  _identifier = identifier;
}

/**
 * \brief    Set individual's generation
 * \details  --
 * \param    int generation
 * \return   \e void
 */
inline void Individual::set_generation( int generation )
{
  assert(generation >= 0);
  _generation = generation;
}


#endif /* defined(__SigmaFGM__Individual__) */
