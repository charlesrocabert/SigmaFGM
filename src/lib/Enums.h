
/**
 * \file      Enums.h
 * \authors   Charles Rocabert, Samuel Bernard
 * \date      21-02-2017
 * \copyright Copyright (C) 2016-2017 Charles Rocabert, Samuel Bernard. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     Definition of enumerations
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

#ifndef __SigmaFGM__Enums__
#define __SigmaFGM__Enums__


/**
 * \brief   Shape of the fitness function
 * \details THe fitness function can else be an exponential, a cauchy, a linear or a step function
 */
enum fitness_function_shape
{
  EXPONENTIAL = 0, /*!< Exponential function */
  CAUCHY      = 1, /*!< Cauchy function      */
  LINEAR      = 2, /*!< Linear function      */
  STEP        = 3  /*!< Step function        */
};


#endif /* defined(__SigmaFGM__Enums__) */
