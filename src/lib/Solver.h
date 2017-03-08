
/**
 * \file      Solver.h
 * \authors   Charles Rocabert, Samuel Bernard
 * \date      07-06-2016
 * \copyright Copyright (C) 2016-2017 Charles Rocabert, Samuel Bernard. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     Solver class declaration
 */

/***********************************************************************
 * Copyright (C) 2016-2017 Charles Rocabert, Samuel Bernard
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

#ifndef __NoisyFGM__Solver__
#define __NoisyFGM__Solver__

#include <iostream>
#include <cmath>
#include <unordered_map>
#include <gsl/gsl_vector.h>
#include <tbb/tbb.h>
#include <assert.h>

#include "Parameters.h"
#include "Particle.h"
#include "Statistics.h"
#include "Prng.h"


class Solver
{
  
public:
  
  /*----------------------------
   * CONSTRUCTORS
   *----------------------------*/
  Solver( void ) = delete;
  Solver( Parameters* parameters );
  Solver( const Solver& solver ) = delete;
  
  /*----------------------------
   * DESTRUCTORS
   *----------------------------*/
  ~Solver( void );
  
  /*----------------------------
   * GETTERS
   *----------------------------*/
  inline Particle* get_first_particle( void );
  inline Particle* get_next_particle( void );
  inline size_t    get_number_of_particles( void ) const;
  inline size_t    get_step( void ) const;
  inline double    get_time( void ) const;
  inline double    get_mean_wmu( void ) const;
  
  /*----------------------------
   * SETTERS
   *----------------------------*/
  Solver& operator=(const Solver&) = delete;
  
  /*----------------------------
   * PUBLIC METHODS
   *----------------------------*/
  void initialize( void );
  void stabilize( void );
  void update( bool stabilize );
  void compute_statistics( void );
  void write_statistics( void );
  void close_statistics( void );
  
  void write_extra_statistics( std::ofstream& extra_file );
  
  /*----------------------------
   * PUBLIC ATTRIBUTES
   *----------------------------*/
  
protected:
  
  /*----------------------------
   * PROTECTED METHODS
   *----------------------------*/
  void initialize_particles_list( void );
  void initialize_solver_state( bool stabilize );
  void update_particle( Particle* particle, gsl_vector* z_opt );
  
  /*----------------------------
   * PROTECTED ATTRIBUTES
   *----------------------------*/
  
  /*----------------------------------------------- PARAMETERS */
  
  Parameters* _parameters; /*!< Parameters set */
  
  /*----------------------------------------------- LIST OF PARTICLES */
  
  std::unordered_map<size_t, Particle*>           _particles_list;     /*!< Dynamic list of particles   */
  std::unordered_map<size_t, Particle*>::iterator _iterator;           /*!< Particles list iterator     */
  size_t                                          _current_identifier; /*!< Current particle identifier */
  
  /*----------------------------------------------- DYNAMIC VARIABLES */
  
  gsl_vector* _z_opt_stab; /*!< Stabilization fitness optimum */
  gsl_vector* _z_opt;      /*!< Fitness optimum               */
  size_t      _step;       /*!< Current simulation step       */
  double      _t;          /*!< Current time                  */
  
  /*----------------------------------------------- STATISTICS */
  
  Statistics* _statistics; /*!< Statistics management */
  
};


/*----------------------------
 * GETTERS
 *----------------------------*/

/**
 * \brief    Get the first particle
 * \details  --
 * \param    Particle*
 * \return   \e void
 */
inline Particle* Solver::get_first_particle( void )
{
  _iterator = _particles_list.begin();
  if (_iterator != _particles_list.end())
  {
    return _iterator->second;
  }
  return NULL;
}

/**
 * \brief    Get the next particle
 * \details  --
 * \param    Particle*
 * \return   \e void
 */
inline Particle* Solver::get_next_particle( void )
{
  _iterator++;
  if (_iterator != _particles_list.end())
  {
    return _iterator->second;
  }
  return NULL;
}

/**
 * \brief    Get the current number of particles
 * \details  --
 * \param    size_t
 * \return   \e void
 */
inline size_t Solver::get_number_of_particles( void ) const
{
  return _particles_list.size();
}

/**
 * \brief    Get the current simulation step
 * \details  --
 * \param    size_t
 * \return   \e void
 */
inline size_t Solver::get_step( void ) const
{
  return _step;
}

/**
 * \brief    Get the current time
 * \details  --
 * \param    double
 * \return   \e void
 */
inline double Solver::get_time( void ) const
{
  return _t;
}

/**
 * \brief    Get the mean mu fitness
 * \details  --
 * \param    double
 * \return   \e void
 */
inline double Solver::get_mean_wmu( void ) const
{
  return _statistics->get_mean_wmu();
}

/*----------------------------
 * SETTERS
 *----------------------------*/


#endif /* defined(__NoisyFGM__Solver__) */
