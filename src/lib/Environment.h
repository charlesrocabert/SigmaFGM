
/**
 * \file      Environment.h
 * \authors   Charles Rocabert, Guillaume Beslon, Carole Knibbe, Samuel Bernard
 * \date      04-04-2018
 * \copyright Copyright (C) 2016-2020 Charles Rocabert, Guillaume Beslon, Carole Knibbe, Samuel Bernard. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     Environment class declaration
 */

/***********************************************************************
 * Copyright (C) 2016-2020
 * Charles Rocabert, Guillaume Beslon, Carole Knibbe, Samuel Bernard
 * Web: https://github.com/charlesrocabert/SigmaFGM/
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

#ifndef __SigmaFGM__Environment__
#define __SigmaFGM__Environment__

#include <iostream>
#include <assert.h>
#include <gsl/gsl_vector.h>

#include "Macros.h"
#include "Enums.h"
#include "Prng.h"
#include "Parameters.h"


class Environment
{
  
public:
  
  /*----------------------------
   * CONSTRUCTORS
   *----------------------------*/
  Environment( void ) = delete;
  Environment( Parameters* parameters );
  Environment( const Environment& environment ) = delete;
  
  /*----------------------------
   * DESTRUCTORS
   *----------------------------*/
  ~Environment( void );
  
  /*----------------------------
   * GETTERS
   *----------------------------*/
  inline gsl_vector* get_z_opt( void );
  inline double      get_z_opt( int i );
  
  /*----------------------------
   * SETTERS
   *----------------------------*/
  Environment& operator=(const Environment&) = delete;
  
  /*----------------------------
   * PUBLIC METHODS
   *----------------------------*/
  void stabilizing_environment( void );
  void normal_environment( void );
  
  /*----------------------------
   * PUBLIC ATTRIBUTES
   *----------------------------*/
  
protected:
  
  /*----------------------------
   * PROTECTED METHODS
   *----------------------------*/
  
  /*----------------------------
   * PROTECTED ATTRIBUTES
   *----------------------------*/
  
  /*----------------------------------------------- PARAMETERS */
  
  Parameters* _parameters; /*!< Parameters                     */
  Prng*       _prng;       /*!< Pseudorandom numbers generator */
  
  /*----------------------------------------------- ENVIRONMENT */
  
  gsl_vector* _z_opt; /*!< Fitness optimum */
  
};

/*----------------------------
 * GETTERS
 *----------------------------*/

/**
 * \brief    Get the fitness optimum vector
 * \details  --
 * \param    void
 * \return   \e double*
 */
inline gsl_vector* Environment::get_z_opt( void )
{
  return _z_opt;
}

/**
 * \brief    Get the ith value of the fitness optimum vector
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Environment::get_z_opt( int i )
{
  assert(i >= 0);
  assert(i < _parameters->get_number_of_dimensions());
  return gsl_vector_get(_z_opt, i);
}

/*----------------------------
 * SETTERS
 *----------------------------*/


#endif /* defined(__SigmaFGM__Environment__) */
