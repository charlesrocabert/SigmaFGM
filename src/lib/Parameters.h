
/**
 * \file      Parameters.h
 * \authors   Charles Rocabert, Samuel Bernard
 * \date      07-06-2016
 * \copyright Copyright (C) 2016 Charles Rocabert, Samuel Bernard. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     Parameters class declaration
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

#ifndef __NoisyFGM__Parameters__
#define __NoisyFGM__Parameters__

#include <iostream>
#include <vector>
#include <assert.h>

#include "Prng.h"


class Parameters
{
  
public:
  
  /*----------------------------
   * CONSTRUCTORS
   *----------------------------*/
  Parameters( void );
  Parameters( const Parameters& parameters ) = delete;
  
  /*----------------------------
   * DESTRUCTORS
   *----------------------------*/
  ~Parameters( void );
  
  /*----------------------------
   * GETTERS
   *----------------------------*/
  
  /*----------------------------------------------- PSEUDORANDOM NUMBERS GENERATOR SEED */
  
  inline Prng*             get_prng( void );
  inline unsigned long int get_prng_seed( void ) const;
  
  /*----------------------------------------------- SOLVER PROPERTIES */
  
  inline size_t get_stabilizing_time( void ) const;
  inline size_t get_time( void ) const;
  inline double get_shutoff_fitness( void ) const;
  inline size_t get_shutoff_time( void ) const;
  
  /*----------------------------------------------- PHENOTYPIC SPACE PROPERTIES */
  
  inline size_t get_number_of_dimensions( void ) const;
  
  /*----------------------------------------------- PARTICLES PROPERTIES */
  
  inline double get_number_of_particles( void ) const;
  inline double get_initial_mu( void ) const;
  inline double get_initial_sigma( void ) const;
  inline double get_initial_theta( void ) const;
  inline double get_delta_mu( void ) const;
  inline double get_delta_sigma( void ) const;
  inline double get_delta_theta( void ) const;
  
  /*----------------------------------------------- VARIOUS */
  
  inline bool get_statistics( void ) const;
  inline bool get_one_axis( void ) const;
  inline bool get_weight_fitness( void ) const;
  inline bool get_no_noise( void ) const;
  inline bool get_no_rotation( void ) const;
  
  /*----------------------------
   * SETTERS
   *----------------------------*/
  Parameters& operator=(const Parameters&) = delete;
  
  /*----------------------------------------------- PSEUDORANDOM NUMBERS GENERATOR SEED */
  
  inline void set_prng( Prng* prng );
  inline void set_prng_seed( unsigned long int seed );
  
  /*----------------------------------------------- SOLVER PROPERTIES */
  
  inline void set_stabilizing_time( size_t time );
  inline void set_time( size_t time );
  inline void set_shutoff_fitness( double shutoff_fitness );
  inline void set_shutoff_time( size_t shutoff_time );
  
  /*----------------------------------------------- PHENOTYPIC SPACE PROPERTIES */
  
  inline void set_number_of_dimensions( size_t number_of_dimensions );
  
  /*----------------------------------------------- PARTICLES PROPERTIES */
  
  inline void set_number_of_particles( double number_of_particles );
  inline void set_initial_mu( double initial_mu );
  inline void set_initial_sigma( double initial_sigma );
  inline void set_initial_theta( double initial_theta );
  inline void set_delta_mu( double delta_mu );
  inline void set_delta_sigma( double delta_sigma );
  inline void set_delta_theta( double delta_theta );
  
  /*----------------------------------------------- VARIOUS */
  
  inline void set_statistics( bool statistics );
  inline void set_one_axis( bool one_axis );
  inline void set_weight_fitness( bool weight_fitness );
  inline void set_no_noise( bool no_noise );
  inline void set_no_rotation( bool no_rotation );
  
  /*----------------------------
   * PUBLIC METHODS
   *----------------------------*/
  void print_parameters( void );
  
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
  
  /*----------------------------------------------- PSEUDORANDOM NUMBERS GENERATOR SEED */
  
  Prng*             _prng; /*!< Pseudorandom numbers generator */
  unsigned long int _seed; /*!< Prng seed                      */
  
  /*----------------------------------------------- SOLVER PROPERTIES */
  
  size_t _stabilizing_time; /*!< Stabilizing simulation time      */
  size_t _time;             /*!< Solving simulation time          */
  double _shutoff_fitness;  /*!< Shutoff fitness to reach         */
  size_t _shutoff_time;     /*!< Shutoff time to maintain fitness */
  
  /*----------------------------------------------- PHENOTYPIC SPACE PROPERTIES */
  
  size_t _number_of_dimensions; /*!< Number of dimensions */
  
  /*----------------------------------------------- PARTICLES PROPERTIES */
  
  double _number_of_particles; /*!< Number of particles */
  double _initial_mu;          /*!< Initial mu value    */
  double _initial_sigma;       /*!< Initial sigma value */
  double _initial_theta;       /*!< Initial theta value */
  double _delta_mu;            /*!< Mu mutation size    */
  double _delta_sigma;         /*!< Sigma mutation size */
  double _delta_theta;         /*!< Mu mutation size    */
  
  /*----------------------------------------------- VARIOUS */
  
  bool _statistics;     /*!< Indicates if statistics must be saved                                 */
  bool _one_axis;       /*!< Indicates if only one axis must be initialized                        */
  bool _weight_fitness; /*!< Indicates if the fitness must be weighted by the number of dimensions */
  bool _no_noise;       /*!< No noise                                                              */
  bool _no_rotation;    /*!< No rotation                                                           */
  
};


/*----------------------------
 * GETTERS
 *----------------------------*/

/*----------------------------------------------- PSEUDORANDOM NUMBERS GENERATOR SEED */

/**
 * \brief    Get the prng
 * \details  --
 * \param    void
 * \return   \e size_t
 */
inline Prng* Parameters::get_prng( void )
{
  return _prng;
}

/**
 * \brief    Get the prng seed
 * \details  --
 * \param    void
 * \return   \e size_t
 */
inline unsigned long int Parameters::get_prng_seed( void ) const
{
  return _seed;
}

/*----------------------------------------------- SOLVER PROPERTIES */

/**
 * \brief    Get the stabilizing time
 * \details  --
 * \param    void
 * \return   \e size_t
 */
inline size_t Parameters::get_stabilizing_time( void ) const
{
  return _stabilizing_time;
}

/**
 * \brief    Get the solving time
 * \details  --
 * \param    void
 * \return   \e size_t
 */
inline size_t Parameters::get_time( void ) const
{
  return _time;
}

/**
 * \brief    Get the shutoff fitness
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Parameters::get_shutoff_fitness( void ) const
{
  return _shutoff_fitness;
}

/**
 * \brief    Get the shutoff time
 * \details  --
 * \param    void
 * \return   \e size_t
 */
inline size_t Parameters::get_shutoff_time( void ) const
{
  return _shutoff_time;
}

/*----------------------------------------------- PHENOTYPIC SPACE PROPERTIES */

/**
 * \brief    Get the number of dimensions
 * \details  --
 * \param    void
 * \return   \e size_t
 */
inline size_t Parameters::get_number_of_dimensions( void ) const
{
  return _number_of_dimensions;
}

/*----------------------------------------------- PARTICLES PROPERTIES */


/**
 * \brief    Get the number of particles
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Parameters::get_number_of_particles( void ) const
{
  return _number_of_particles;
}

/**
 * \brief    Get the initial mu value
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Parameters::get_initial_mu( void ) const
{
  return _initial_mu;
}

/**
 * \brief    Get the initial sigma value
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Parameters::get_initial_sigma( void ) const
{
  return _initial_sigma;
}

/**
 * \brief    Get the initial theta value
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Parameters::get_initial_theta( void ) const
{
  return _initial_theta;
}

/**
 * \brief    Get the mu mutation size
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Parameters::get_delta_mu( void ) const
{
  return _delta_mu;
}

/**
 * \brief    Get the sigma mutation size
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Parameters::get_delta_sigma( void ) const
{
  return _delta_sigma;
}

/**
 * \brief    Get the theta mutation size
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Parameters::get_delta_theta( void ) const
{
  return _delta_theta;
}

/*----------------------------------------------- VARIOUS */

/**
 * \brief    Get the statistics boolean
 * \details  --
 * \param    void
 * \return   \e bool
 */
inline bool Parameters::get_statistics( void ) const
{
  return _statistics;
}

/**
 * \brief    Get the one axis boolean
 * \details  --
 * \param    void
 * \return   \e bool
 */
inline bool Parameters::get_one_axis( void ) const
{
  return _one_axis;
}

/**
 * \brief    Get the weight fitness boolean
 * \details  --
 * \param    void
 * \return   \e bool
 */
inline bool Parameters::get_weight_fitness( void ) const
{
  return _weight_fitness;
}

/**
 * \brief    Get the no noise boolean
 * \details  --
 * \param    void
 * \return   \e bool
 */
inline bool Parameters::get_no_noise( void ) const
{
  return _no_noise;
}

/**
 * \brief    Get the no rotation boolean
 * \details  --
 * \param    void
 * \return   \e bool
 */
inline bool Parameters::get_no_rotation( void ) const
{
  return _no_rotation;
}

/*----------------------------
 * SETTERS
 *----------------------------*/

/*----------------------------------------------- PSEUDORANDOM NUMBERS GENERATOR SEED */

inline void Parameters::set_prng( Prng* prng )
{
  delete _prng;
  _prng = new Prng(*prng);
}

inline void Parameters::set_prng_seed( unsigned long int seed )
{
  _prng->set_seed(seed);
  _seed = seed;
}

/*----------------------------------------------- SOLVER PROPERTIES */

/**
 * \brief    Set the stabilizing time
 * \details  --
 * \param    size_t time
 * \return   \e void
 */
inline void Parameters::set_stabilizing_time( size_t time )
{
  _stabilizing_time = time;
}

/**
 * \brief    Set the solving time
 * \details  --
 * \param    size_t time
 * \return   \e void
 */
inline void Parameters::set_time( size_t time )
{
  _time = time;
}

/**
 * \brief    Set the shutoff fitness
 * \details  --
 * \param    double shutoff_fitness
 * \return   \e void
 */
inline void Parameters::set_shutoff_fitness( double shutoff_fitness )
{
  assert(shutoff_fitness >= 0.0);
  _shutoff_fitness = shutoff_fitness;
}

/**
 * \brief    Set the shutoff time
 * \details  --
 * \param    size_t shutoff time
 * \return   \e void
 */
inline void Parameters::set_shutoff_time( size_t shutoff_time )
{
  _shutoff_time = shutoff_time;
}

/*----------------------------------------------- PHENOTYPIC SPACE PROPERTIES */

/**
 * \brief    Set the number of dimensions
 * \details  --
 * \param    size_t number_of_dimensions
 * \return   \e void
 */
inline void Parameters::set_number_of_dimensions( size_t number_of_dimensions )
{
  assert(number_of_dimensions > 0);
  _number_of_dimensions = number_of_dimensions;
}

/*----------------------------------------------- PARTICLES PROPERTIES */

/**
 * \brief    Set the number of particles
 * \details  --
 * \param    double number_of_particles
 * \return   \e void
 */
inline void Parameters::set_number_of_particles( double number_of_particles )
{
  assert(number_of_particles > 0);
  _number_of_particles = number_of_particles;
}

/**
 * \brief    Set the initial mu value
 * \details  --
 * \param    double initial_mu
 * \return   \e void
 */
inline void Parameters::set_initial_mu( double initial_mu )
{
  _initial_mu = initial_mu;
}

/**
 * \brief    Set the initial sigma value
 * \details  --
 * \param    double initial_sigma
 * \return   \e void
 */
inline void Parameters::set_initial_sigma( double initial_sigma )
{
  assert(initial_sigma >= 0.0);
  _initial_sigma = initial_sigma;
}

/**
 * \brief    Set the initial theta value
 * \details  --
 * \param    double initial_theta
 * \return   \e void
 */
inline void Parameters::set_initial_theta( double initial_theta )
{
  _initial_theta = initial_theta;
}

/**
 * \brief    Set the mu mutation size
 * \details  --
 * \param    double delta_mu
 * \return   \e void
 */
inline void Parameters::set_delta_mu( double delta_mu )
{
  assert(delta_mu >= 0.0);
  _delta_mu = delta_mu;
}

/**
 * \brief    Set the sigma mutation size
 * \details  --
 * \param    double delta_sigma
 * \return   \e void
 */
inline void Parameters::set_delta_sigma( double delta_sigma )
{
  assert(delta_sigma >= 0.0);
  _delta_sigma = delta_sigma;
}

/**
 * \brief    Set the theta mutation size
 * \details  --
 * \param    double delta_theta
 * \return   \e void
 */
inline void Parameters::set_delta_theta( double delta_theta )
{
  assert(delta_theta >= 0.0);
  _delta_theta = delta_theta;
}

/*----------------------------------------------- VARIOUS */

/**
 * \brief    Set the statistics boolean
 * \details  --
 * \param    bool statistics
 * \return   \e void
 */
inline void Parameters::set_statistics( bool statistics )
{
  _statistics = statistics;
}

/**
 * \brief    Set the one axis boolean
 * \details  --
 * \param    bool statistics
 * \return   \e void
 */
inline void Parameters::set_one_axis( bool one_axis )
{
  _one_axis = one_axis;
}

/**
 * \brief    Set the weight fitness boolean
 * \details  --
 * \param    bool statistics
 * \return   \e void
 */
inline void Parameters::set_weight_fitness( bool weight_fitness )
{
  _weight_fitness = weight_fitness;
}

/**
 * \brief    Set no noise boolean
 * \details  --
 * \param    bool no_noise
 * \return   \e void
 */
inline void Parameters::set_no_noise( bool no_noise )
{
  _no_noise = no_noise;
}

/**
 * \brief    Set no rotation boolean
 * \details  --
 * \param    bool no_rotation
 * \return   \e void
 */
inline void Parameters::set_no_rotation( bool no_rotation )
{
  _no_rotation = no_rotation;
}


#endif /* defined(__NoisyFGM__Parameters__) */
