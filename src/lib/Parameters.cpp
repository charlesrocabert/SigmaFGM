
/**
 * \file      Parameters.cpp
 * \authors   Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon
 * \date      07-06-2016
 * \copyright Copyright (C) 2016-2018 Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     Parameters class definition
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
  _initial_mu      = 0.0;
  _initial_sigma   = 0.0;
  _initial_theta   = 0.0;
  
  /*----------------------------------------------- MUTATIONS */
  
  _m_mu    = 0.0;
  _m_sigma = 0.0;
  _m_theta = 0.0;
  _s_mu    = 0.0;
  _s_sigma = 0.0;
  _s_theta = 0.0;
  
  /*----------------------------------------------- NOISE PROPERTIES */
  
  _noise_type = NONE;
  
  /*----------------------------------------------- NUMERICAL ANALYSIS */
  
  _X_min   = 0.0;
  _X_max   = 4.0;
  _X_step  = 0.1;
  _Ve_min  = 0.0;
  _Ve_max  = 4.0;
  _Ve_step = 0.1;
  _epsilon = 1e-6;
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
  std::cout << "initial mu        " << _initial_mu << "\n";
  std::cout << "initial sigma     " << _initial_sigma << "\n";
  std::cout << "initial theta     " << _initial_theta << "\n";
  std::cout << "mu mut rate       " << _m_mu << "\n";
  std::cout << "sigma mut rate    " << _m_sigma << "\n";
  std::cout << "theta mut rate    " << _m_theta << "\n";
  std::cout << "mu mut size       " << _s_mu << "\n";
  std::cout << "sigma mut size    " << _s_sigma << "\n";
  std::cout << "theta mut size    " << _s_theta << "\n";
  if (_noise_type == NONE) std::cout << "noise type        NONE\n";
  else if (_noise_type == ISOTROPIC) std::cout << "noise type        ISOTROPIC\n";
  else if (_noise_type == UNCORRELATED) std::cout << "noise type        UNCORRELATED\n";
  else if (_noise_type == FULL) std::cout << "noise type        FULL\n";
  std::cout << "#######################################\n";
}
