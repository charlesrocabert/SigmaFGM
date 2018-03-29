
/**
 * \file      Statistics.h
 * \authors   Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon
 * \date      07-06-2016
 * \copyright Copyright (C) 2016-2018 Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     Statistics class declaration
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

#ifndef __SigmaFGM__Statistics__
#define __SigmaFGM__Statistics__

#include <iostream>
#include <fstream>
#include <assert.h>

#include "Population.h"


class Statistics
{
  
public:
  
  /*----------------------------
   * CONSTRUCTORS
   *----------------------------*/
  Statistics( void );
  Statistics( const Statistics& statistics ) = delete;
  
  /*----------------------------
   * DESTRUCTORS
   *----------------------------*/
  ~Statistics( void );
  
  /*----------------------------
   * GETTERS
   *----------------------------*/
  inline double get_dg_mean( void ) const;
  inline double get_wg_mean( void ) const;
  
  /*----------------------------
   * SETTERS
   *----------------------------*/
  Statistics& operator=(const Statistics&) = delete;
  
  /*----------------------------
   * PUBLIC METHODS
   *----------------------------*/
  void write_headers( void );
  void compute_statistics( Population* population );
  void write_statistics( int simulation_time );
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
  
  /*----------------------------------------------- MEAN VALUES */
  
  double _dg_mean;              /*!< Genetic distance                 */
  double _dp_mean;              /*!< Phenotypic distance              */
  double _wg_mean;              /*!< Genetic fitness                  */
  double _wp_mean;              /*!< Phenotypic fitness               */
  double _EV_mean;              /*!< Best eigen value                 */
  double _EV_contribution_mean; /*!< Best eigen value contribution    */
  double _EV_dot_product_mean;  /*!< Best dot product                 */
  double _r_mu_mean;            /*!< Euclidean size of Mu mutation    */
  double _r_sigma_mean;         /*!< Euclidean size of Sigma mutation */
  double _r_theta_mean;         /*!< Euclidean size of Theta mutation */
  
  /*----------------------------------------------- STANDARD DEVIATION VALUES */
  
  double _dg_sd;              /*!< Genetic distance                 */
  double _dp_sd;              /*!< Phenotypic distance              */
  double _wg_sd;              /*!< Genetic fitness                  */
  double _wp_sd;              /*!< Phenotypic fitness               */
  double _EV_sd;              /*!< Best eigen value                 */
  double _EV_contribution_sd; /*!< Best eigen value contribution    */
  double _EV_dot_product_sd;  /*!< Best dot product                 */
  double _r_mu_sd;            /*!< Euclidean size of Mu mutation    */
  double _r_sigma_sd;         /*!< Euclidean size of Sigma mutation */
  double _r_theta_sd;         /*!< Euclidean size of Theta mutation */
  
  /*----------------------------------------------- STATISTIC FILES */
  
  std::ofstream _mean_file; /*!< Mean file               */
  std::ofstream _sd_file;   /*!< Standard deviation file */
};


/*----------------------------
 * GETTERS
 *----------------------------*/

/**
 * \brief    Get mean genetic distance
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Statistics::get_dg_mean( void ) const
{
  return _dg_mean;
}

/**
 * \brief    Get mean genetic fitness
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Statistics::get_wg_mean( void ) const
{
  return _wg_mean;
}

/*----------------------------
 * SETTERS
 *----------------------------*/



#endif /* defined(__SigmaFGM__Statistics__) */
