
/**
 * \file      Parameters.h
 * \authors   Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon
 * \date      07-06-2016
 * \copyright Copyright (C) 2016-2018 Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     Parameters class declaration
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

#ifndef __SigmaFGM__Parameters__
#define __SigmaFGM__Parameters__

#include <iostream>
#include <vector>
#include <assert.h>

#include "Macros.h"
#include "Enums.h"
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
  inline unsigned long int get_seed( void ) const;
  
  /*----------------------------------------------- SIMULATION TIME */
  
  inline int    get_stabilizing_time( void ) const;
  inline int    get_simulation_time( void ) const;
  inline double get_shutoff_distance( void ) const;
  inline int    get_shutoff_time( void ) const;
  
  /*----------------------------------------------- PHENOTYPIC COMPLEXITY */
  
  inline int get_number_of_dimensions( void ) const;
  
  /*----------------------------------------------- FITNESS FUNCTION */
  
  inline double get_alpha( void ) const;
  inline double get_beta( void ) const;
  inline double get_Q( void ) const;
  
  /*----------------------------------------------- POPULATION */
  
  inline int    get_population_size( void ) const;
  inline double get_initial_mu( void ) const;
  inline double get_initial_sigma( void ) const;
  inline double get_initial_theta( void ) const;
  inline bool   get_oneD_shift( void ) const;
  
  /*----------------------------------------------- MUTATIONS */
  
  inline double get_m_mu( void ) const;
  inline double get_m_sigma( void ) const;
  inline double get_m_theta( void ) const;
  inline double get_s_mu( void ) const;
  inline double get_s_sigma( void ) const;
  inline double get_s_theta( void ) const;
  
  /*----------------------------------------------- NOISE PROPERTIES */
  
  inline type_of_noise get_noise_type( void ) const;
  
  /*----------------------------------------------- NUMERICAL ANALYSIS */
  
  inline double get_X_min( void ) const;
  inline double get_X_max( void ) const;
  inline double get_X_step( void ) const;
  inline double get_Ve_min( void ) const;
  inline double get_Ve_max( void ) const;
  inline double get_Ve_step( void ) const;
  inline double get_epsilon( void ) const;
  
  /*----------------------------
   * SETTERS
   *----------------------------*/
  Parameters& operator=(const Parameters&) = delete;
  
  /*----------------------------------------------- PSEUDORANDOM NUMBERS GENERATOR SEED */
  
  inline void set_prng( Prng* prng );
  inline void set_seed( unsigned long int seed );
  
  /*----------------------------------------------- SIMULATION TIME */
  
  inline void set_stabilizing_time( int stabilizing_time );
  inline void set_simulation_time( int simulation_time );
  inline void set_shutoff_distance( double shutoff_distance );
  inline void set_shutoff_time( int shutoff_time );
  
  /*----------------------------------------------- PHENOTYPIC COMPLEXITY */
  
  inline void set_number_of_dimensions( int number_of_dimensions );
  
  /*----------------------------------------------- FITNESS FUNCTION */
  
  inline void set_alpha( double alpha );
  inline void set_beta( double beta );
  inline void set_Q( double Q );
  
  /*----------------------------------------------- POPULATION */
  
  inline void set_population_size( int population_size );
  inline void set_initial_mu( double initial_mu );
  inline void set_initial_sigma( double initial_sigma );
  inline void set_initial_theta( double initial_theta );
  inline void set_oneD_shift( bool oneD_shift );
  
  /*----------------------------------------------- MUTATIONS */
  
  inline void set_m_mu( double m_mu );
  inline void set_m_sigma( double m_sigma );
  inline void set_m_theta( double m_theta );
  inline void set_s_mu( double s_mu );
  inline void set_s_sigma( double s_sigma );
  inline void set_s_theta( double s_theta );
  
  /*----------------------------------------------- NOISE PROPERTIES */
  
  inline void set_noise_type( type_of_noise noise_type );
  
  /*----------------------------------------------- NUMERICAL ANALYSIS */
  
  inline void set_X_min( double X_min );
  inline void set_X_max( double X_max );
  inline void set_X_step( double X_step );
  inline void set_Ve_min( double Ve_min );
  inline void set_Ve_max( double Ve_max );
  inline void set_Ve_step( double Ve_step );
  inline void set_epsilon( double epsilon );
  
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
  
  /*----------------------------------------------- SIMULATION TIME */
  
  int    _stabilizing_time; /*!< Time used to stabilize initial population */
  int    _simulation_time;  /*!< Real simulation time                      */
  double _shutoff_distance; /*!< Shutoff distance to reach                 */
  int    _shutoff_time;     /*!< Shutoff time to maintain shutoff fitness  */
  
  /*----------------------------------------------- PHENOTYPIC COMPLEXITY */
  
  int _number_of_dimensions; /*!< Number of dimensions */
  
  /*----------------------------------------------- FITNESS FUNCTION */
  
  double _alpha; /*!< Alpha parameter (controls the decay rate)    */
  double _beta;  /*!< Beta parameter (controls the initial height) */
  double _Q;     /*!< Q parameter (controls the curvature)         */
  
  /*----------------------------------------------- POPULATION */
  
  int    _population_size; /*!< Number of particles                        */
  double _initial_mu;      /*!< Initial mu value                           */
  double _initial_sigma;   /*!< Initial sigma value                        */
  double _initial_theta;   /*!< Initial theta value                        */
  bool   _oneD_shift;      /*!< The population is shifted in one dimension */
  
  /*----------------------------------------------- MUTATIONS */
  
  double _m_mu;        /*!< Mu mutation rate    */
  double _m_sigma;     /*!< Sigma mutation rate */
  double _m_theta;     /*!< Mu mutation rate    */
  double _s_mu;        /*!< Mu mutation size    */
  double _s_sigma;     /*!< Sigma mutation size */
  double _s_theta;     /*!< Mu mutation size    */
  
  /*----------------------------------------------- NOISE PROPERTIES */
  
  type_of_noise _noise_type; /*!< Type of phenotypic noise (none, isotropic, ...) */
  
  /*----------------------------------------------- NUMERICAL ANALYSIS */
  
  double _X_min;   /*!< X minimal value     */
  double _X_max;   /*!< X maximal value     */
  double _X_step;  /*!< X exploration step  */
  double _Ve_min;  /*!< Ve minimal value    */
  double _Ve_max;  /*!< Ve maximal value    */
  double _Ve_step; /*!< Ve exploration step */
  double _epsilon; /*!< Derivative step     */
};


/*----------------------------
 * GETTERS
 *----------------------------*/

/*----------------------------------------------- PSEUDORANDOM NUMBERS GENERATOR SEED */

/**
 * \brief    Get the prng
 * \details  --
 * \param    void
 * \return   \e Prng*
 */
inline Prng* Parameters::get_prng( void )
{
  return _prng;
}

/**
 * \brief    Get the prng seed
 * \details  --
 * \param    void
 * \return   \e unsigned long int
 */
inline unsigned long int Parameters::get_seed( void ) const
{
  return _seed;
}

/*----------------------------------------------- SIMULATION TIME */

/**
 * \brief    Get the stabilizing time
 * \details  --
 * \param    void
 * \return   \e int
 */
inline int Parameters::get_stabilizing_time( void ) const
{
  return _stabilizing_time;
}

/**
 * \brief    Get the simulation time
 * \details  --
 * \param    void
 * \return   \e int
 */
inline int Parameters::get_simulation_time( void ) const
{
  return _simulation_time;
}

/**
 * \brief    Get the shutoff distance
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Parameters::get_shutoff_distance( void ) const
{
  return _shutoff_distance;
}

/**
 * \brief    Get the shutoff time
 * \details  --
 * \param    void
 * \return   \e int
 */
inline int Parameters::get_shutoff_time( void ) const
{
  return _shutoff_time;
}

/*----------------------------------------------- PHENOTYPIC COMPLEXITY */

/**
 * \brief    Get the number of dimensions
 * \details  --
 * \param    void
 * \return   \e int
 */
inline int Parameters::get_number_of_dimensions( void ) const
{
  return _number_of_dimensions;
}

/*----------------------------------------------- FITNESS FUNCTION */

/**
 * \brief    Get alpha parameter
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Parameters::get_alpha( void ) const
{
  return _alpha;
}

/**
 * \brief    Get beta parameter
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Parameters::get_beta( void ) const
{
  return _beta;
}

/**
 * \brief    Get Q parameter
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Parameters::get_Q( void ) const
{
  return _Q;
}

/*----------------------------------------------- POPULATION */


/**
 * \brief    Get the population size
 * \details  --
 * \param    void
 * \return   \e int
 */
inline int Parameters::get_population_size( void ) const
{
  return _population_size;
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
 * \brief    Get oneD shift boolean
 * \details  --
 * \param    void
 * \return   \e double
 */
inline bool Parameters::get_oneD_shift( void ) const
{
  return _oneD_shift;
}

/*----------------------------------------------- MUTATIONS */

/**
 * \brief    Get mu mutation rate
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Parameters::get_m_mu( void ) const
{
  return _m_mu;
}

/**
 * \brief    Get sigma mutation rate
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Parameters::get_m_sigma( void ) const
{
  return _m_sigma;
}

/**
 * \brief    Get theta mutation rate
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Parameters::get_m_theta( void ) const
{
  return _m_theta;
}

/**
 * \brief    Get mu mutation size
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Parameters::get_s_mu( void ) const
{
  return _s_mu;
}

/**
 * \brief    Get sigma mutation size
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Parameters::get_s_sigma( void ) const
{
  return _s_sigma;
}

/**
 * \brief    Get theta mutation size
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Parameters::get_s_theta( void ) const
{
  return _s_theta;
}

/*----------------------------------------------- NOISE PROPERTIES */

/**
 * \brief    Get phenotypic noise type
 * \details  --
 * \param    void
 * \return   \e double
 */
inline type_of_noise Parameters::get_noise_type( void ) const
{
  return _noise_type;
}

/*----------------------------------------------- NUMERICAL ANALYSIS */

/**
 * \brief    Get X minimal value
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Parameters::get_X_min( void ) const
{
  return _X_min;
}

/**
 * \brief    Get X maximal value
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Parameters::get_X_max( void ) const
{
  return _X_max;
}

/**
 * \brief    Get X step value
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Parameters::get_X_step( void ) const
{
  return _X_step;
}

/**
 * \brief    Get Ve minimal value
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Parameters::get_Ve_min( void ) const
{
  return _Ve_min;
}

/**
 * \brief    Get Ve maximal value
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Parameters::get_Ve_max( void ) const
{
  return _Ve_max;
}

/**
 * \brief    Get Ve step value
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Parameters::get_Ve_step( void ) const
{
  return _Ve_step;
}

/**
 * \brief    Get epsilon value
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Parameters::get_epsilon( void ) const
{
  return _epsilon;
}

/*----------------------------
 * SETTERS
 *----------------------------*/

/*----------------------------------------------- PSEUDORANDOM NUMBERS GENERATOR SEED */

/**
 * \brief    Set the prng
 * \details  --
 * \param    Prng* prng
 * \return   \e void
 */
inline void Parameters::set_prng( Prng* prng )
{
  delete _prng;
  _prng = new Prng(*prng);
}

/**
 * \brief    Set the prng seed
 * \details  --
 * \param    unsigned long int seed
 * \return   \e void
 */
inline void Parameters::set_seed( unsigned long int seed )
{
  _prng->set_seed(seed);
  _seed = seed;
}

/*----------------------------------------------- SIMULATION TIME */

/**
 * \brief    Set the stabilizing time
 * \details  --
 * \param    int stabilizing_time
 * \return   \e void
 */
inline void Parameters::set_stabilizing_time( int stabilizing_time)
{
  assert(stabilizing_time >= 0);
  _stabilizing_time = stabilizing_time;
}

/**
 * \brief    Set the simulation time
 * \details  --
 * \param    int simulation_time
 * \return   \e void
 */
inline void Parameters::set_simulation_time( int simulation_time )
{
  assert(simulation_time >= 0);
  _simulation_time = simulation_time;
}

/**
 * \brief    Set the shutoff distance
 * \details  --
 * \param    double shutoff_distance
 * \return   \e void
 */
inline void Parameters::set_shutoff_distance( double shutoff_distance )
{
  assert(shutoff_distance >= 0.0);
  _shutoff_distance = shutoff_distance;
}

/**
 * \brief    Set the shutoff time
 * \details  --
 * \param    int shutoff time
 * \return   \e void
 */
inline void Parameters::set_shutoff_time( int shutoff_time )
{
  assert(shutoff_time >= 0);
  _shutoff_time = shutoff_time;
}

/*----------------------------------------------- PHENOTYPIC COMPLEXITY */

/**
 * \brief    Set the number of dimensions
 * \details  --
 * \param    int number_of_dimensions
 * \return   \e void
 */
inline void Parameters::set_number_of_dimensions( int number_of_dimensions )
{
  assert(number_of_dimensions > 0);
  _number_of_dimensions = number_of_dimensions;
}

/*----------------------------------------------- FITNESS FUNCTION */

/**
 * \brief    Set alpha parameter
 * \details  --
 * \param    double alpha
 * \return   \e void
 */
inline void Parameters::set_alpha( double alpha )
{
  _alpha = alpha;
}

/**
 * \brief    Set beta parameter
 * \details  --
 * \param    double beta
 * \return   \e void
 */
inline void Parameters::set_beta( double beta )
{
  assert(beta >= 0.0);
  assert(beta <= 1.0);
  _beta = beta;
}

/**
 * \brief    Set Q parameter
 * \details  --
 * \param    double Q
 * \return   \e void
 */
inline void Parameters::set_Q( double Q )
{
  assert(Q >= 0);
  _Q = Q;
}

/*----------------------------------------------- POPULATION */

/**
 * \brief    Set the population size
 * \details  --
 * \param    int population_size
 * \return   \e void
 */
inline void Parameters::set_population_size( int population_size )
{
  assert(population_size > 0);
  _population_size = population_size;
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
 * \brief    Set the oneD shift boolean
 * \details  --
 * \param    bool oneD_shift
 * \return   \e void
 */
inline void Parameters::set_oneD_shift( bool oneD_shift )
{
  _oneD_shift = oneD_shift;
}

/*----------------------------------------------- MUTATIONS */

/**
 * \brief    Set the mu mutation rate
 * \details  --
 * \param    double m_mu
 * \return   \e void
 */
inline void Parameters::set_m_mu( double m_mu )
{
  assert(m_mu >= 0.0);
  assert(m_mu <= 1.0);
  _m_mu = m_mu;
}

/**
 * \brief    Set the sigma mutation rate
 * \details  --
 * \param    double m_sigma
 * \return   \e void
 */
inline void Parameters::set_m_sigma( double m_sigma )
{
  assert(m_sigma >= 0.0);
  assert(m_sigma <= 1.0);
  _m_sigma = m_sigma;
}

/**
 * \brief    Set the theta mutation rate
 * \details  --
 * \param    double m_theta
 * \return   \e void
 */
inline void Parameters::set_m_theta( double m_theta )
{
  assert(m_theta >= 0.0);
  assert(m_theta <= 1.0);
  _m_theta = m_theta;
}

/**
 * \brief    Set the mu mutation size
 * \details  --
 * \param    double s_mu
 * \return   \e void
 */
inline void Parameters::set_s_mu( double s_mu )
{
  assert(s_mu >= 0.0);
  _s_mu = s_mu;
}

/**
 * \brief    Set the sigma mutation size
 * \details  --
 * \param    double s_sigma
 * \return   \e void
 */
inline void Parameters::set_s_sigma( double s_sigma )
{
  assert(s_sigma >= 0.0);
  _s_sigma = s_sigma;
}

/**
 * \brief    Set the theta mutation size
 * \details  --
 * \param    double s_theta
 * \return   \e void
 */
inline void Parameters::set_s_theta( double s_theta )
{
  assert(s_theta >= 0.0);
  _s_theta = s_theta;
}

/*----------------------------------------------- NOISE PROPERTIES */

/**
 * \brief    Set phenotypic noise type
 * \details  --
 * \param    type_of_noise noise_type
 * \return   \e void
 */
inline void Parameters::set_noise_type( type_of_noise noise_type )
{
  _noise_type = noise_type;
}

/*----------------------------------------------- NUMERICAL ANALYSIS */

/**
 * \brief    Set X minimal value
 * \details  --
 * \param    double X_min
 * \return   \e void
 */
inline void Parameters::set_X_min( double X_min )
{
  _X_min = X_min;
}

/**
 * \brief    Set X maximal value
 * \details  --
 * \param    double X_max
 * \return   \e void
 */
inline void Parameters::set_X_max( double X_max )
{
  _X_max = X_max;
}

/**
 * \brief    Set X step value
 * \details  --
 * \param    double X_step
 * \return   \e void
 */
inline void Parameters::set_X_step( double X_step )
{
  _X_step = X_step;
}

/**
 * \brief    Set Ve minimal value
 * \details  --
 * \param    double Ve_min
 * \return   \e void
 */
inline void Parameters::set_Ve_min( double Ve_min )
{
  _Ve_min = Ve_min;
}

/**
 * \brief    Set Ve maximal value
 * \details  --
 * \param    double Ve_max
 * \return   \e void
 */
inline void Parameters::set_Ve_max( double Ve_max )
{
  _Ve_max = Ve_max;
}

/**
 * \brief    Set Ve step value
 * \details  --
 * \param    double Ve_step
 * \return   \e void
 */
inline void Parameters::set_Ve_step( double Ve_step )
{
  _Ve_step = Ve_step;
}

/**
 * \brief    Set epsilon value
 * \details  --
 * \param    double epsilon
 * \return   \e void
 */
inline void Parameters::set_epsilon( double epsilon )
{
  _epsilon = epsilon;
}


#endif /* defined(__SigmaFGM__Parameters__) */
