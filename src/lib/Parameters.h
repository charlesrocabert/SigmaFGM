
/**
 * \file      Parameters.h
 * \authors   Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon
 * \date      07-06-2016
 * \copyright Copyright (C) 2016-2020 Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     Parameters class declaration
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
  
  inline int    get_number_of_stabilizing_generations( void ) const;
  inline int    get_number_of_generations( void ) const;
  inline double get_shutoff_distance( void ) const;
  inline int    get_shutoff_generation( void ) const;
  
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
  inline bool   get_mean_fitness( void ) const;
  
  /*----------------------------------------------- MUTATIONS */
  
  inline double get_m_mu( void ) const;
  inline double get_m_sigma( void ) const;
  inline double get_m_theta( void ) const;
  inline double get_s_mu( void ) const;
  inline double get_s_sigma( void ) const;
  inline double get_s_theta( void ) const;
  
  /*----------------------------------------------- NOISE PROPERTIES */
  
  inline type_of_noise get_noise_type( void ) const;
  
  /*----------------------------
   * SETTERS
   *----------------------------*/
  Parameters& operator=(const Parameters&) = delete;
  
  /*----------------------------------------------- PSEUDORANDOM NUMBERS GENERATOR SEED */
  
  inline void set_prng( Prng* prng );
  inline void set_seed( unsigned long int seed );
  
  /*----------------------------------------------- SIMULATION TIME */
  
  inline void set_number_of_stabilizing_generations( int stabilizing_generations );
  inline void set_number_of_generations( int generations );
  inline void set_shutoff_distance( double shutoff_distance );
  inline void set_shutoff_generation( int shutoff_generation );
  
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
  inline void set_mean_fitness( bool mean_fitness );
  
  /*----------------------------------------------- MUTATIONS */
  
  inline void set_m_mu( double m_mu );
  inline void set_m_sigma( double m_sigma );
  inline void set_m_theta( double m_theta );
  inline void set_s_mu( double s_mu );
  inline void set_s_sigma( double s_sigma );
  inline void set_s_theta( double s_theta );
  
  /*----------------------------------------------- NOISE PROPERTIES */
  
  inline void set_noise_type( type_of_noise noise_type );
  
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
  
  int    _stabilizing_generations; /*!< Number of generations used to stabilize initial population  */
  int    _generations;             /*!< Number of generations                                       */
  double _shutoff_distance;        /*!< Shutoff distance to reach                                   */
  int    _shutoff_generation;      /*!< Maximum number of generations to reach the shutoff distance */
  
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
  bool   _mean_fitness;    /*!< The mean fitness is computed               */
  
  /*----------------------------------------------- MUTATIONS */
  
  double _m_mu;    /*!< mu mutation rate    */
  double _m_sigma; /*!< sigma mutation rate */
  double _m_theta; /*!< theta mutation rate */
  double _s_mu;    /*!< mu mutation size    */
  double _s_sigma; /*!< sigma mutation size */
  double _s_theta; /*!< theta mutation size */
  
  /*----------------------------------------------- NOISE PROPERTIES */
  
  type_of_noise _noise_type; /*!< Type of phenotypic noise (none, isotropic, ...) */
  
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
 * \brief    Get the number of stabilizing generations
 * \details  --
 * \param    void
 * \return   \e int
 */
inline int Parameters::get_number_of_stabilizing_generations( void ) const
{
  return _stabilizing_generations;
}

/**
 * \brief    Get the number of generations
 * \details  --
 * \param    void
 * \return   \e int
 */
inline int Parameters::get_number_of_generations( void ) const
{
  return _generations;
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
 * \brief    Get the shutoff generations number
 * \details  --
 * \param    void
 * \return   \e int
 */
inline int Parameters::get_shutoff_generation( void ) const
{
  return _shutoff_generation;
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

/**
 * \brief    Get mean fitness boolean
 * \details  --
 * \param    void
 * \return   \e double
 */
inline bool Parameters::get_mean_fitness( void ) const
{
  return _mean_fitness;
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
 * \brief    Set the number of stabilizing generations
 * \details  --
 * \param    int stabilizing_generations
 * \return   \e void
 */
inline void Parameters::set_number_of_stabilizing_generations( int stabilizing_generations )
{
  assert(stabilizing_generations >= 0);
  _stabilizing_generations = stabilizing_generations;
}

/**
 * \brief    Set the number of generations
 * \details  --
 * \param    int generations
 * \return   \e void
 */
inline void Parameters::set_number_of_generations( int generations )
{
  assert(generations >= 0);
  _generations = generations;
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
 * \brief    Set the shutoff generations number
 * \details  --
 * \param    int shutoff_generation
 * \return   \e void
 */
inline void Parameters::set_shutoff_generation( int shutoff_generation )
{
  assert(shutoff_generation >= 0);
  _shutoff_generation = shutoff_generation;
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
  assert(Q >= 0.0);
  assert((int)Q%2==0);
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

/**
 * \brief    Set the mean fitness boolean
 * \details  --
 * \param    bool mean_fitness
 * \return   \e void
 */
inline void Parameters::set_mean_fitness( bool mean_fitness )
{
  _mean_fitness = mean_fitness;
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


#endif /* defined(__SigmaFGM__Parameters__) */
