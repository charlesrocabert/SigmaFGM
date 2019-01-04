
/**
 * \file      Enums.h
 * \authors   Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon
 * \date      21-02-2017
 * \copyright Copyright (C) 2016-2019 Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     Definition of enumerations
 */

/***********************************************************************
 * Copyright (C) 2016-2019
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
 * \details Defines the type of phenotypic noise
 */
enum type_of_noise
{
  NONE         = 0, /*!< No phenotypic noise (classical FGM case) */
  ISOTROPIC    = 1, /*!< Isotropic noise                          */
  UNCORRELATED = 2, /*!< Anisotropic and uncorrelated noise       */
  FULL         = 3  /*!< Fully evolvable noise                    */
};

/******************************************************************************************/

/**
 * \brief   Node class
 * \details Defines the class of a node in the tree (master root, root or normal).
 */
enum node_class
{
  MASTER_ROOT = 1, /*!< The node is the master root */
  ROOT        = 2, /*!< The node is a root          */
  NORMAL      = 3  /*!< The node is normal          */
};

/******************************************************************************************/

/**
 * \brief   Node state
 * \details Defines the state of a node in the tree, depending on cell's status (dead or alive).
 */
enum node_state
{
  DEAD  = 1, /*!< The cell is dead  */
  ALIVE = 2  /*!< The cell is alive */
};


#endif /* defined(__SigmaFGM__Enums__) */
