
/**
 * \file      NumericalAnalysis.h
 * \authors   Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon
 * \date      06-04-2018
 * \copyright Copyright (C) 2016-2018 Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     NumericalAnalysis class declaration
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

#ifndef __SigmaFGM__NumericalAnalysis__
#define __SigmaFGM__NumericalAnalysis__

#include <iostream>
#include <cmath>
#include <assert.h>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_randist.h>

#include "Macros.h"
#include "Enums.h"
#include "Structs.h"
#include "Prng.h"
#include "Parameters.h"


class NumericalAnalysis
{
  
public:
  
  /*----------------------------
   * CONSTRUCTORS
   *----------------------------*/
  NumericalAnalysis( Parameters* parameters );
  NumericalAnalysis( const NumericalAnalysis& numerical_analysis ) = delete;
  
  /*----------------------------
   * DESTRUCTORS
   *----------------------------*/
  ~NumericalAnalysis( void );
  
  /*----------------------------
   * GETTERS
   *----------------------------*/
  
  /*----------------------------
   * SETTERS
   *----------------------------*/
  NumericalAnalysis& operator=(const NumericalAnalysis&) = delete;
  
  /*----------------------------
   * PUBLIC METHODS
   *----------------------------*/
  
  /*----------------------------
   * PUBLIC ATTRIBUTES
   *----------------------------*/
  
  /* Whole function is:
   * Wbar( X_bar, Ve_bar, Vgx, Vge )
   * = int int int [ W(z).p(z|X,Ve).p(X|X_bar,Vgx).p(Ve|Ve_bar,Vge) dz dX dVe ]
   * = int[ p(Ve|Ve_bar,Vge) . int[ p(X|X_bar,Vgx) . int[ W(z).p(z|X,Ve)dz ] dX ] dVe ]
   * W1 = int[ W(z).p(z|X,Ve) dz ]
   * W2 = int[ p(X|X_bar,Vgx).W1 dX ]
   * W3 = int[ p(Ve|Ve_bar,Vge).W2 dVe ]
   */
  
  static double gaussian_pdf( double x, double mu, double sigma );
  static double gamma_pdf( double x, double k, double theta );
  
  static double W( double z, double alpha, double beta, double Q );
  
  static double W1_integrand( double z, void* params );
  static double W1( double X, double Ve, double alpha, double beta, double Q );
  
  static double W2_integrand( double X, void* params );
  static double W2( double X_bar, double Vgx, double Ve, double alpha, double beta, double Q );
  
  static double W3_integrand( double Ve, void* params );
  static double W3( double Ve_bar, double Vge, double X_bar, double Vgx, double alpha, double beta, double Q );
  
protected:
  
  /*----------------------------
   * PROTECTED METHODS
   *----------------------------*/
  
  /*----------------------------
   * PROTECTED ATTRIBUTES
   *----------------------------*/
  
  /*----------------------------------------------- PARAMETERS */
  
  Parameters* _parameters; /*!< Parameters                     */
  Prng*       _prng;       /*!< Pseudorandom numbers generator */
  
  /*----------------------------------------------- INTEGRATION VARIABLES */
  
};

/*----------------------------
 * GETTERS
 *----------------------------*/

/*----------------------------
 * SETTERS
 *----------------------------*/


#endif /* defined(__SigmaFGM__NumericalAnalysis__) */
