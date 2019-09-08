
/**
 * \file      Population.h
 * \authors   Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon
 * \date      28-03-2018
 * \copyright Copyright (C) 2016-2019 Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     Population class declaration
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

#ifndef __SigmaFGM__Population__
#define __SigmaFGM__Population__

#include <iostream>
#include <assert.h>

#include "Macros.h"
#include "Enums.h"
#include "Prng.h"
#include "Parameters.h"
#include "Individual.h"
#include "Environment.h"
#include "Tree.h"

class Population
{
  
public:
  
  /*----------------------------
   * CONSTRUCTORS
   *----------------------------*/
  Population( void ) = delete;
  Population( Parameters* parameters, Environment* environment, Tree* tree );
  Population( const Population& population ) = delete;
  
  /*----------------------------
   * DESTRUCTORS
   *----------------------------*/
  ~Population( void );
  
  /*----------------------------
   * GETTERS
   *----------------------------*/
  inline int         get_population_size( void ) const;
  inline Individual* get_individual( int i );
  
  /*----------------------------
   * SETTERS
   *----------------------------*/
  Population& operator=(const Population&) = delete;
  
  /*----------------------------
   * PUBLIC METHODS
   *----------------------------*/
  void compute_next_generation( int next_generation );
  
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
  
  Parameters*            _parameters;         /*!< Parameters                     */
  Prng*                  _prng;               /*!< Pseudorandom numbers generator */
  Environment*           _environment;        /*!< Environment (fitness optimum)  */
  Tree*                  _tree;               /*!< Lineage tree                   */
  unsigned long long int _current_identifier; /*!< Current individual identifier  */
  
  /*----------------------------------------------- POPULATION */
  
  Individual** _pop;   /*!< Population vector               */
  double*      _w;     /*!< Fitness vector                  */
  double       _w_sum; /*!< Fitness sum (for normalization) */
};

/*----------------------------
 * GETTERS
 *----------------------------*/

/**
 * \brief    Get the population size
 * \details  --
 * \param    void
 * \return   \e int
 */
inline int Population::get_population_size( void ) const
{
  return _parameters->get_population_size();
}

/**
 * \brief    Get individual i
 * \details  --
 * \param    int i
 * \return   \e Individual*
 */
inline Individual* Population::get_individual( int i )
{
  return _pop[i];
}

/*----------------------------
 * SETTERS
 *----------------------------*/


#endif /* defined(__SigmaFGM__Population__) */
