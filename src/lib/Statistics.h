
/**
 * \file      Statistics.h
 * \authors   Charles Rocabert, Samuel Bernard
 * \date      07-06-2016
 * \copyright Copyright (C) 2016-2017 Charles Rocabert, Samuel Bernard. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     Statistics class declaration
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

#ifndef __NoisyFGM__Statistics__
#define __NoisyFGM__Statistics__

#include <iostream>
#include <fstream>
#include <assert.h>

#include "Parameters.h"
#include "Particle.h"


class Statistics
{
  
public:
  
  /*----------------------------
   * CONSTRUCTORS
   *----------------------------*/
  Statistics( void ) = delete;
  Statistics( Parameters* parameters );
  Statistics( const Statistics& statistics ) = delete;
  
  /*----------------------------
   * DESTRUCTORS
   *----------------------------*/
  ~Statistics( void );
  
  /*----------------------------
   * GETTERS
   *----------------------------*/
  inline double get_mean_wmu( void ) const;
  
  /*----------------------------
   * SETTERS
   *----------------------------*/
  Statistics& operator=(const Statistics&) = delete;
  
  /*----------------------------
   * PUBLIC METHODS
   *----------------------------*/
  void write_headers( void );
  void add_particle( Particle* particle );
  void compute_statistics( void );
  void write_statistics( size_t step, double time );
  void reset( void );
  void flush( void );
  void close( void );
  
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
  
  /*----------------------------------------------- PARAMETERS */
  
  Parameters* _parameters;   /*!< Parameters set      */
  size_t      _nb_particles; /*!< Number of particles */
  
  /*----------------------------------------------- BEST VALUES */
  
  double  _dmu_best;             /*!< Mean distance                 */
  double  _dp_best;              /*!< Instantaneous distance        */
  double  _wmu_best;             /*!< Mean fitness                  */
  double  _wp_best;              /*!< Instantaneous fitness         */
  double  _EV_best;              /*!< Best eigen value              */
  double  _EV_contribution_best; /*!< Best eigen value contribution */
  double  _EV_dot_product_best;  /*!< Best dot product              */
  
  /*----------------------------------------------- MEAN VALUES */
  
  double  _dmu_mean;             /*!< Mean distance                 */
  double  _dp_mean;              /*!< Instantaneous distance        */
  double  _wmu_mean;             /*!< Mean fitness                  */
  double  _wp_mean;              /*!< Instantaneous fitness         */
  double  _EV_mean;              /*!< Best eigen value              */
  double  _EV_contribution_mean; /*!< Best eigen value contribution */
  double  _EV_dot_product_mean;  /*!< Best dot product              */
  
  /*----------------------------------------------- STANDARD DEVIATION VALUES */
  
  double  _dmu_sd;             /*!< Mean distance                 */
  double  _dp_sd;              /*!< Instantaneous distance        */
  double  _wmu_sd;             /*!< Mean fitness                  */
  double  _wp_sd;              /*!< Instantaneous fitness         */
  double  _EV_sd;              /*!< Best eigen value              */
  double  _EV_contribution_sd; /*!< Best eigen value contribution */
  double  _EV_dot_product_sd;  /*!< Best dot product              */
  
  /*----------------------------------------------- STATISTIC FILES */
  
  std::ofstream _best_file; /*!< Best file     */
  std::ofstream _mean_file; /*!< Mean file     */
  std::ofstream _var_file;  /*!< Variance file */
};


/*----------------------------
 * GETTERS
 *----------------------------*/

/**
 * \brief    Get mean mu fitness
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Statistics::get_mean_wmu( void ) const
{
  return _wmu_mean;
}

/*----------------------------
 * SETTERS
 *----------------------------*/



#endif /* defined(__NoisyFGM__Statistics__) */
