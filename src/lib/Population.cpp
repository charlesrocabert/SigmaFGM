
/**
 * \file      Population.cpp
 * \authors   Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon
 * \date      28-03-2018
 * \copyright Copyright (C) 2016-2018 Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     Population class definition
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

#include "Population.h"


/*----------------------------
 * CONSTRUCTORS
 *----------------------------*/

/**
 * \brief    Constructor
 * \details  --
 * \param    Parameters* parameters
 * \param    Environment* environment
 * \return   \e void
 */
Population::Population( Parameters* parameters, Environment* environment )
{
  assert(parameters != NULL);
  assert(environment != NULL);
  
  /*----------------------------------------------- PARAMETERS */
  
  _prng        = parameters->get_prng();
  _parameters  = parameters;
  _environment = environment;
  
  /*----------------------------------------------- POPULATION */
  
  _pop   = new Individual*[_parameters->get_population_size()];
  _w     = new double[_parameters->get_population_size()];
  _w_sum = 0.0;
  for (int i = 0; i < _parameters->get_population_size(); i++)
  {
    _pop[i] = new Individual(_prng, _parameters->get_number_of_dimensions(), _parameters->get_initial_mu(), _parameters->get_initial_sigma(), _parameters->get_initial_sigma(), _parameters->get_oneD_shift(), _parameters->get_noise_type(), _environment->get_z_opt());
    _pop[i]->build_phenotype();
    _pop[i]->compute_fitness(_parameters->get_alpha(), _parameters->get_beta(), _parameters->get_Q());
    _w[i]   = _pop[i]->get_wp();
    _w_sum += _w[i];
  }
  for (int i = 0; i < _parameters->get_population_size(); i++)
  {
    _w[i] /= _w_sum;
  }
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
Population::~Population( void )
{
  _prng        = NULL;
  _environment = NULL;
  for (int i = 0; i < _parameters->get_population_size(); i++)
  {
    delete _pop[i];
    _pop[i] = NULL;
  }
  delete[] _pop;
  _pop = NULL;
  delete[] _w;
  _w = NULL;
  _parameters = NULL;
}

/*----------------------------
 * PUBLIC METHODS
 *----------------------------*/

/**
 * \brief    Compute the next generation
 * \details  --
 * \param    void
 * \return   \e void
 */
void Population::compute_next_generation( void )
{
  Individual**  new_pop   = new Individual*[_parameters->get_population_size()];
  unsigned int* draws     = new unsigned int[_parameters->get_population_size()];
  int           new_index = 0;
  _prng->multinomial(draws, _w, _parameters->get_population_size(), _parameters->get_population_size());
  for (int i = 0; i < _parameters->get_population_size(); i++)
  {
    for (unsigned int j = 0; j < draws[i]; j++)
    {
      new_pop[new_index] = new Individual(*_pop[i]);
      new_pop[new_index]->mutate(_parameters->get_m_mu(), _parameters->get_m_sigma(), _parameters->get_m_theta(), _parameters->get_s_mu(), _parameters->get_s_sigma(), _parameters->get_s_theta());
      new_pop[new_index]->build_phenotype();
      _pop[i]->compute_fitness(_parameters->get_alpha(), _parameters->get_beta(), _parameters->get_Q());
      _w[new_index]  = _pop[i]->get_wp();
      _w_sum        += _w[new_index];
      new_index++;
    }
    delete _pop[i];
    _pop[i] = NULL;
  }
  delete[] _pop;
  _pop = new_pop;
  delete[] draws;
  draws = NULL;
  for (int i = 0; i < _parameters->get_population_size(); i++)
  {
    _w[i] /= _w_sum;
  }
}

/*----------------------------
 * PROTECTED METHODS
 *----------------------------*/

