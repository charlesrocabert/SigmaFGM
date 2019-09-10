
/**
 * \file      Environment.cpp
 * \authors   Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon
 * \date      04-04-2018
 * \copyright Copyright (C) 2016-2019 Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     Environment class definition
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

#include "Environment.h"


/*----------------------------
 * CONSTRUCTORS
 *----------------------------*/

/**
 * \brief    Constructor
 * \details  --
 * \param    Parameters* parameters
 * \return   \e void
 */
Environment::Environment( Parameters* parameters )
{
  assert(parameters != NULL);
  
  /*----------------------------------------------- PARAMETERS */
  
  _parameters = parameters;
  _prng       = _parameters->get_prng();
  
  /*----------------------------------------------- ENVIRONMENT */
  
  _z_opt = gsl_vector_alloc(_parameters->get_number_of_dimensions());
  gsl_vector_set_zero(_z_opt);
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
Environment::~Environment( void )
{
  _parameters = NULL;
  _prng       = NULL;
  gsl_vector_free(_z_opt);
  _z_opt = NULL;
}

/*----------------------------
 * PUBLIC METHODS
 *----------------------------*/

/**
 * \brief    Switch to the stabilizing environment
 * \details  --
 * \param    void
 * \return   \e void
 */
void Environment::stabilizing_environment( void )
{
  if (_parameters->get_oneD_shift())
  {
    gsl_vector_set_zero(_z_opt);
    gsl_vector_set(_z_opt, 0, _parameters->get_initial_mu());
  }
  else
  {
    gsl_vector_set_all(_z_opt, _parameters->get_initial_mu());
  }
}

/**
 * \brief    Switch to the normal environment
 * \details  --
 * \param    void
 * \return   \e void
 */
void Environment::normal_environment( void )
{
  gsl_vector_set_zero(_z_opt);
}

/*----------------------------
 * PROTECTED METHODS
 *----------------------------*/

