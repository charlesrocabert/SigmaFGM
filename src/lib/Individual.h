
/**
 * \file      Individual.h
 * \authors   Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon
 * \date      28-03-2018
 * \copyright Copyright (C) 2016-2019 Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     Individual class declaration
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

#ifndef __SigmaFGM__Individual__
#define __SigmaFGM__Individual__

#include <iostream>
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
  Individual( Prng* prng, int n, double X_init, double Ve_init, double Theta_init, bool oneD_shift, type_of_noise noise_type, gsl_vector* z_opt );
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
  inline double                 get_X( int i ) const;
  inline double                 get_Ve( int i ) const;
  inline double                 get_Theta( int i ) const;
  inline double                 get_dX( void ) const;
  inline double                 get_dz( void ) const;
  inline double                 get_WX( void ) const;
  inline double                 get_Wz( void ) const;
  
  /*----------------------------------------------- MAPPING PROPERTIES */
  
  inline double get_max_Sigma_eigenvalue( void ) const;
  inline double get_max_Sigma_contribution( void ) const;
  inline double get_max_dot_product( void ) const;
  
  /*----------------------------------------------- MUTATIONS */
  
  inline double get_r_X( void ) const;
  inline double get_r_Ve( void ) const;
  inline double get_r_Theta( void ) const;
  
  /*----------------------------
   * SETTERS
   *----------------------------*/
  Individual& operator=(const Individual&) = delete;
  
  inline void set_identifier( unsigned long long int identifier );
  inline void set_generation( int generation );
  
  /*----------------------------
   * PUBLIC METHODS
   *----------------------------*/
  void mutate( double m_X, double m_Ve, double m_Theta, double s_X, double s_Ve, double s_Theta );
  void build_phenotype( void );
  void compute_fitness( double alpha, double beta, double Q );
  void compute_mean_fitness( double alpha, double beta, double Q );
  void delete_vectors_and_matrices( void );
  
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
  gsl_vector*            _X;          /*!< X vector                      */
  gsl_vector*            _Ve;         /*!< Ve vector                     */
  gsl_vector*            _Theta;      /*!< Theta vector                  */
  gsl_matrix*            _Sigma;      /*!< Co-variance matrix            */
  gsl_matrix*            _Cholesky;   /*!< Cholesky decomposition matrix */
  gsl_vector*            _z;          /*!< Instantaneous phenotype       */
  double                 _dX;         /*!< Euclidean distance d(X)       */
  double                 _dz;         /*!< Euclidean distance d(z)       */
  double                 _WX;         /*!< Fitness W(X)                  */
  double                 _Wz;         /*!< Fitness W(z)                  */
  
  /*----------------------------------------------- MAPPING PROPERTIES */
  
  bool        _phenotype_is_built;     /*!< Indicates if the phenotype is built                             */
  gsl_vector* _max_Sigma_eigenvector;  /*!< Eigen vector corresponding to the maximum variance of Sigma     */
  double      _max_Sigma_eigenvalue;   /*!< Eigen value corresponding to the maximum variance of Sigma      */
  double      _max_Sigma_contribution; /*!< Eigen value contribution to the total variance                  */
  double      _max_dot_product;        /*!< Dot product of maximum Sigma eigen vector and optimum direction */
  
  /*----------------------------------------------- MUTATIONS */
  
  double _r_X;     /*!< Euclidean size of X mutation     */
  double _r_Ve;    /*!< Euclidean size of Ve mutation    */
  double _r_Theta; /*!< Euclidean size of Theta mutation */
  
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
 * \brief    Get X value at position i
 * \details  --
 * \param    int i
 * \return   \e double
 */
inline double Individual::get_X( int i ) const
{
  assert(i < _n);
  return gsl_vector_get(_X, i);
}

/**
 * \brief    Get Ve value at position i
 * \details  --
 * \param    int i
 * \return   \e double
 */
inline double Individual::get_Ve( int i ) const
{
  assert(i < _n);
  return gsl_vector_get(_Ve, i);
}

/**
 * \brief    Get Theta value at position i
 * \details  --
 * \param    int i
 * \return   \e double
 */
inline double Individual::get_Theta( int i ) const
{
  assert(i < _n*(_n-1)/2);
  return gsl_vector_get(_Theta, i);
}

/**
 * \brief    Get the euclidean distance d(X)
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Individual::get_dX( void ) const
{
  return _dX;
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
 * \brief    Get the fitness W(X)
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Individual::get_WX( void ) const
{
  return _WX;
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
 * \brief    Get the euclidean size of X mutation
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Individual::get_r_X( void ) const
{
  return _r_X;
}

/**
 * \brief    Get the euclidean size of Ve mutation
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Individual::get_r_Ve( void ) const
{
  return _r_Ve;
}

/**
 * \brief    Get the euclidean size of Theta mutation
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Individual::get_r_Theta( void ) const
{
  return _r_Theta;
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
