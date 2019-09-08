
/**
 * \file      Simulation.h
 * \authors   Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon
 * \date      04-04-2018
 * \copyright Copyright (C) 2016-2019 Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     Simulation class declaration
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

#ifndef __SigmaFGM__Simulation__
#define __SigmaFGM__Simulation__

#include <iostream>
#include <assert.h>

#include "Macros.h"
#include "Enums.h"
#include "Prng.h"
#include "Parameters.h"
#include "Environment.h"
#include "Tree.h"
#include "Population.h"
#include "Statistics.h"


class Simulation
{
  
public:
  
  /*----------------------------
   * CONSTRUCTORS
   *----------------------------*/
  Simulation( void ) = delete;
  Simulation( Parameters* parameters );
  Simulation( const Simulation& simulation ) = delete;
  
  /*----------------------------
   * DESTRUCTORS
   *----------------------------*/
  ~Simulation( void );
  
  /*----------------------------
   * GETTERS
   *----------------------------*/
  
  /*----------------------------
   * SETTERS
   *----------------------------*/
  Simulation& operator=(const Simulation&) = delete;
  
  /*----------------------------
   * PUBLIC METHODS
   *----------------------------*/
  void stabilize( int generations );
  void run( int generations );
  void run_with_shutoff( double shutoff_distance, int shutoff_generation );
  
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
  
  Parameters*  _parameters; /*!< Parameters                     */
  Prng*        _prng;       /*!< Pseudorandom numbers generator */
  
  /*----------------------------------------------- SIMULATION */
  
  Environment* _environment; /*!< Environment  */
  Tree*        _tree;        /*!< Lineage tree */
  Population*  _population;  /*!< Population   */
  Statistics*  _statistics;  /*!< Statistics   */
  
};

/*----------------------------
 * GETTERS
 *----------------------------*/

/*----------------------------
 * SETTERS
 *----------------------------*/


#endif /* defined(__SigmaFGM__Simulation__) */
