
/**
 * \file      Enums.h
 * \authors   Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon
 * \date      21-02-2017
 * \copyright Copyright (C) 2016-2018 Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     Definition of enumerations
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

#ifndef __SigmaFGM__Enums__
#define __SigmaFGM__Enums__


/**
 * \brief   Type of phenotypic noise
 * \details --
 */
enum type_of_noise
{
  NONE         = 0, /*!< No phenotypic noise (classical FGM case) */
  ISOTROPIC    = 1, /*!< Isotropic noise                          */
  UNCORRELATED = 2, /*!< Anisotropic and uncorrelated noise       */
  FULL         = 3, /*!< Fully evolvable noise                    */
  OPTIMAL      = 4  /*!< Optimally shaped noise (based on maths)  */
};


#endif /* defined(__SigmaFGM__Enums__) */
