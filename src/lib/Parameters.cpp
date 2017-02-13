
/**
 * \file      Parameters.cpp
 * \authors   Charles Rocabert, Samuel Bernard
 * \date      07-06-2016
 * \copyright Copyright (C) 2016 Charles Rocabert, Samuel Bernard. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     Parameters class definition
 */

/***********************************************************************
 * Copyright (C) 2016 Charles Rocabert, Samuel Bernard
 * E-mail: charles.rocabert@gmail.com
 * Web:
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
  
  /*----------------------------------------------- SOLVER PROPERTIES */
  
  _stabilizing_time = 0;
  _time             = 0;
  _shutoff_fitness  = 0.0;
  _shutoff_time     = 0;
  
  /*----------------------------------------------- PHENOTYPIC SPACE PROPERTIES */
  
  _number_of_dimensions = 0;
  
  /*----------------------------------------------- PARTICLES PROPERTIES */
  
  _number_of_particles = 0.0;
  _initial_mu          = 0.0;
  _initial_sigma       = 0.0;
  _initial_theta       = 0.0;
  _delta_mu            = 0.0;
  _delta_sigma         = 0.0;
  _delta_theta         = 0.0;
  
  /*----------------------------------------------- VARIOUS */
  
  _statistics     = false;
  _one_axis       = false;
  _weight_fitness = false;
  _no_noise       = false;
  _no_rotation    = false;
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
  std::cout << "stabilizing time    " << _stabilizing_time << "\n";
  std::cout << "time                " << _time << "\n";
  std::cout << "shutoff fitness     " << _shutoff_fitness << "\n";
  std::cout << "shutoff time        " << _shutoff_time << "\n";
  std::cout << "seed                " << _seed << "\n";
  std::cout << "dimensions          " << _number_of_dimensions << "\n";
  std::cout << "number of particles " << _number_of_particles << "\n";
  std::cout << "initial mu          " << _initial_mu << "\n";
  std::cout << "initial sigma       " << _initial_sigma << "\n";
  std::cout << "initial theta       " << _initial_theta << "\n";
  std::cout << "delta mu            " << _delta_mu << "\n";
  std::cout << "delta sigma         " << _delta_sigma << "\n";
  std::cout << "delta theta         " << _delta_theta << "\n";
  std::cout << "statistics          " << _statistics << "\n";
  std::cout << "one axis            " << _one_axis << "\n";
  std::cout << "weight fitness      " << _weight_fitness << "\n";
  std::cout << "no noise            " << _no_noise << "\n";
  std::cout << "no rotation         " << _no_rotation << "\n";
  std::cout << "#######################################\n";
}
