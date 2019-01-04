
/**
 * \file      Parameters.cpp
 * \authors   Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon
 * \date      07-06-2016
 * \copyright Copyright (C) 2016-2019 Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     Parameters class definition
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

#include "Parameters.h"


/*----------------------------
 * CONSTRUCTORS
 *----------------------------*/

/**
 * \brief    Default constructor
 * \details  --
 * \param    void
 * \return   \e void
 */
Parameters::Parameters( void )
{
  /*----------------------------------------------- PSEUDORANDOM NUMBERS GENERATOR SEED */
  
  _prng = new Prng();
  _seed = 0;
  
  /*----------------------------------------------- SIMULATION TIME */
  
  _stabilizing_time = 0;
  _simulation_time  = 0;
  _shutoff_distance = 0.0;
  _shutoff_time     = 0;
  
  /*----------------------------------------------- PHENOTYPIC COMPLEXITY */
  
  _number_of_dimensions = 0;
  
  /*----------------------------------------------- FITNESS FUNCTION */
  
  _alpha = 0.5;
  _beta  = 0.0;
  _Q     = 2.0;
  
  /*----------------------------------------------- POPULATION */
  
  _population_size = 0.0;
  _initial_X       = 0.0;
  _initial_Ve      = 0.0;
  _initial_Theta   = 0.0;
  
  /*----------------------------------------------- MUTATIONS */
  
  _m_X     = 0.0;
  _m_Ve    = 0.0;
  _m_Theta = 0.0;
  _s_X     = 0.0;
  _s_Ve    = 0.0;
  _s_Theta = 0.0;
  
  /*----------------------------------------------- NOISE PROPERTIES */
  
  _noise_type = NONE;
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
Parameters::~Parameters( void )
{
  delete _prng;
  _prng = NULL;
}

/*----------------------------
 * PUBLIC METHODS
 *----------------------------*/

/**
 * \brief    Print the parameters
 * \details  --
 * \param    void
 * \return   \e void
 */
void Parameters::print_parameters( void )
{
  std::cout << "### Parameters ########################\n";
  std::cout << "seed              " << _seed << "\n";
  std::cout << "stabilizing time  " << _stabilizing_time << "\n";
  std::cout << "simulation time   " << _simulation_time << "\n";
  std::cout << "shutoff distance  " << _shutoff_distance << "\n";
  std::cout << "shutoff time      " << _shutoff_time << "\n";
  std::cout << "dimensions        " << _number_of_dimensions << "\n";
  std::cout << "alpha             " << _alpha << "\n";
  std::cout << "beta              " << _beta << "\n";
  std::cout << "Q                 " << _Q << "\n";
  std::cout << "population size   " << _population_size << "\n";
  std::cout << "initial X         " << _initial_X << "\n";
  std::cout << "initial Ve        " << _initial_Ve << "\n";
  std::cout << "initial Theta     " << _initial_Theta << "\n";
  std::cout << "X mut rate        " << _m_X << "\n";
  std::cout << "Ve mut rate       " << _m_Ve << "\n";
  std::cout << "Theta mut rate    " << _m_Theta << "\n";
  std::cout << "X mut size        " << _s_X << "\n";
  std::cout << "Ve mut size       " << _s_Ve << "\n";
  std::cout << "Theta mut size    " << _s_Theta << "\n";
  if (_noise_type == NONE) std::cout << "noise type        NONE\n";
  else if (_noise_type == ISOTROPIC) std::cout << "noise type        ISOTROPIC\n";
  else if (_noise_type == UNCORRELATED) std::cout << "noise type        UNCORRELATED\n";
  else if (_noise_type == FULL) std::cout << "noise type        FULL\n";
  std::cout << "#######################################\n";
}
