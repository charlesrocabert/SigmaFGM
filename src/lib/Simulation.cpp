
/**
 * \file      Simulation.h
 * \authors   Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon
 * \date      04-04-2018
 * \copyright Copyright (C) 2016-2020 Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     Simulation class definition
 */

/***********************************************************************
 * Copyright (C) 2016-2020
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

#include "Simulation.h"


/*----------------------------
 * CONSTRUCTORS
 *----------------------------*/

/**
 * \brief    Constructor
 * \details  --
 * \param    Parameters* parameters
 * \return   \e void
 */
Simulation::Simulation( Parameters* parameters )
{
  assert(parameters != NULL);
  
  /*----------------------------------------------- PARAMETERS */
  
  _parameters = parameters;
  _prng       = _parameters->get_prng();
  
  /*----------------------------------------------- SIMULATION */
  
  _environment = new Environment(_parameters);
  _tree        = new Tree();
  _population  = new Population(_parameters, _environment, _tree);
  _statistics  = new Statistics();
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
Simulation::~Simulation( void )
{
  /*----------------------------------------------- PARAMETERS */
  
  _parameters = NULL;
  _prng       = NULL;
  
  /*----------------------------------------------- SIMULATION */
  
  delete _environment;
  _environment = NULL;
  delete _population;
  _population = NULL;
  delete _tree;
  _tree = NULL;
  delete _statistics;
  _statistics = NULL;
}

/*----------------------------
 * PUBLIC METHODS
 *----------------------------*/

/**
 * \brief    Stabilize the population
 * \details  --
 * \param    int generations
 * \return   \e void
 */
void Simulation::stabilize( int generations )
{
  _environment->stabilizing_environment();
  for (int g = 1; g <= generations; g++)
  {
    _population->compute_next_generation(g);
  }
}

/**
 * \brief    Run the simulation
 * \details  --
 * \param    int time
 * \return   \e void
 */
void Simulation::run( int generations )
{
  _environment->normal_environment();
  _statistics->write_headers();
  for (int g = 1; g <= generations; g++)
  {
    _population->compute_next_generation(g);
    _statistics->reset();
    _statistics->compute_statistics(_population);
    _statistics->write_statistics(g);
    _statistics->flush();
  }
  _statistics->close();
  //_tree->write_best_lineage_statistics();
}

/**
 * \brief    Run the simulation with shutoff
 * \details  --
 * \param    double shutoff_distance
 * \param    int shutoff_generation
 * \return   \e void
 */
void Simulation::run_with_shutoff( double shutoff_distance, int shutoff_generation )
{
  _environment->normal_environment();
  _statistics->write_headers();
  int  g       = 0;
  bool shutoff = false;
  while (!shutoff)
  {
    g++;
    _population->compute_next_generation(g);
    _statistics->reset();
    _statistics->compute_statistics(_population);
    _statistics->write_statistics(g);
    _statistics->flush();
    if (fabs(_statistics->get_dmu_mean()) <= fabs(shutoff_distance))
    {
      shutoff = true;
    }
    if (g == shutoff_generation)
    {
      shutoff = true;
    }
  }
  _statistics->close();
  //_tree->write_best_lineage_statistics();
}

/*----------------------------
 * PROTECTED METHODS
 *----------------------------*/

