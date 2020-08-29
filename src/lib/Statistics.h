
/**
 * \file      Statistics.h
 * \authors   Charles Rocabert, Guillaume Beslon, Carole Knibbe, Samuel Bernard
 * \date      07-06-2016
 * \copyright Copyright (C) 2016-2020 Charles Rocabert, Guillaume Beslon, Carole Knibbe, Samuel Bernard. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     Statistics class declaration
 */

/***********************************************************************
 * Copyright (C) 2016-2020
 * Charles Rocabert, Guillaume Beslon, Carole Knibbe, Samuel Bernard
 * Web: https://github.com/charlesrocabert/SigmaFGM/
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
  inline double get_dmu_mean( void ) const;
  inline double get_dz_mean( void ) const;
  inline double get_Wmu_mean( void ) const;
  inline double get_Wz_mean( void ) const;
  
  /*----------------------------
   * SETTERS
   *----------------------------*/
  Statistics& operator=(const Statistics&) = delete;
  
  /*----------------------------
   * PUBLIC METHODS
   *----------------------------*/
  void write_headers( void );
  void compute_statistics( Population* population );
  void write_statistics( int generation );
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
  
  double _dmu_mean;             /*!< Genetic distance                 */
  double _dz_mean;              /*!< Phenotypic distance              */
  double _Wmu_mean;             /*!< Genetic fitness                  */
  double _Wz_mean;              /*!< Phenotypic fitness               */
  double _EV_mean;              /*!< Best eigen value                 */
  double _EV_contribution_mean; /*!< Best eigen value contribution    */
  double _EV_dot_product_mean;  /*!< Best dot product                 */
  double _r_mu_mean;            /*!< Euclidean size of mu mutation    */
  double _r_sigma_mean;         /*!< Euclidean size of sigma mutation */
  double _r_theta_mean;         /*!< Euclidean size of theta mutation */
  
  /*----------------------------------------------- STANDARD DEVIATION VALUES */
  
  double _dmu_sd;             /*!< Genetic distance                 */
  double _dz_sd;              /*!< Phenotypic distance              */
  double _Wmu_sd;             /*!< Genetic fitness                  */
  double _Wz_sd;              /*!< Phenotypic fitness               */
  double _EV_sd;              /*!< Best eigen value                 */
  double _EV_contribution_sd; /*!< Best eigen value contribution    */
  double _EV_dot_product_sd;  /*!< Best dot product                 */
  double _r_mu_sd;            /*!< Euclidean size of mu mutation    */
  double _r_sigma_sd;         /*!< Euclidean size of sigma mutation */
  double _r_theta_sd;         /*!< Euclidean size of theta mutation */
  
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
inline double Statistics::get_dmu_mean( void ) const
{
  return _dmu_mean;
}

/**
 * \brief    Get mean phenotypic distance
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Statistics::get_dz_mean( void ) const
{
  return _dz_mean;
}

/**
 * \brief    Get mean genetic fitness
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Statistics::get_Wmu_mean( void ) const
{
  return _Wmu_mean;
}

/**
 * \brief    Get mean phenotypic fitness
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Statistics::get_Wz_mean( void ) const
{
  return _Wz_mean;
}

/*----------------------------
 * SETTERS
 *----------------------------*/



#endif /* defined(__SigmaFGM__Statistics__) */
