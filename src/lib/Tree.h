
/**
 * \file      Tree.h
 * \authors   Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon
 * \date      04-04-2018
 * \copyright Copyright (C) 2016-2018 Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     Tree class declaration
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

#ifndef __SigmaFGM__Tree__
#define __SigmaFGM__Tree__

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstring>
#include <cmath>
#include <fstream>
#include <sstream>

#include "Macros.h"
#include "Enums.h"
#include "Individual.h"
#include "Node.h"


class Tree
{
  
public:
  
  /*----------------------------
   * CONSTRUCTORS
   *----------------------------*/
  Tree( void );
  Tree( const Tree& tree ) = delete;
  
  /*----------------------------
   * DESTRUCTORS
   *----------------------------*/
  ~Tree( void );
  
  /*----------------------------
   * GETTERS
   *----------------------------*/
  inline int    get_number_of_nodes( void ) const;
  inline Node*  get_node( unsigned long long int identifier );
  inline Node*  get_first_node( void );
  inline Node*  get_next_node( void );
  inline Node*  get_best_alive_node( void );
  
  /*----------------------------
   * SETTERS
   *----------------------------*/
  Tree& operator=(const Tree&) = delete;
  
  /*----------------------------
   * PUBLIC METHODS
   *----------------------------*/
  void add_root( Individual* individual );
  void add_reproduction_event( Individual* parent, Individual* child );
  void delete_node( unsigned long long int node_identifier );
  void prune();
  void write_best_lineage_statistics( void );
  
  /*----------------------------
   * PUBLIC ATTRIBUTES
   *----------------------------*/
  
protected:
  
  /*----------------------------
   * PROTECTED METHODS
   *----------------------------*/
  void tag_tree();
  void untag_tree();
  void tag_offspring( Node* node, std::vector<Node*>* tagged_nodes );
  
  /*----------------------------
   * PROTECTED ATTRIBUTES
   *----------------------------*/
  std::unordered_map<unsigned long long int, Node*>           _node_map; /*!< Tree nodes map    */
  std::unordered_map<unsigned long long int, Node*>::iterator _iterator; /*!< Tree map iterator */
};


/*----------------------------
 * GETTERS
 *----------------------------*/

/**
 * \brief    Get the number of nodes of the tree
 * \details  --
 * \param    void
 * \return   \e int
 */
inline int Tree::get_number_of_nodes( void ) const
{
  return (int)_node_map.size();
}

/**
 * \brief    Get the node by its identifier
 * \details  Return NULL if the node do not exist
 * \param    unsigned long long int identifier
 * \return   \e Node*
 */
inline Node* Tree::get_node( unsigned long long int identifier )
{
  if (_node_map.find(identifier) != _node_map.end())
  {
    return _node_map[identifier];
  }
  return NULL;
}

/**
 * \brief    Get the first node of the map
 * \details  Return NULL if the tree is empty
 * \param    void
 * \return   \e Node*
 */
inline Node* Tree::get_first_node( void )
{
  _iterator = _node_map.begin();
  if (_iterator != _node_map.end())
  {
    return _iterator->second;
  }
  return NULL;
}

/**
 * \brief    Get the next node
 * \details  Return NULL if the end of the tree is reached
 * \param    void
 * \return   \e Node*
 */
inline Node* Tree::get_next_node( void )
{
  _iterator++;
  if (_iterator != _node_map.end())
  {
    return _iterator->second;
  }
  return NULL;
}

/**
 * \brief    Get best alive node
 * \details  --
 * \param    void
 * \return   \e Node*
 */
inline Node* Tree::get_best_alive_node( void )
{
  double best_w    = 0.0;
  Node*  best_node = NULL;
  for (_iterator = _node_map.begin(); _iterator != _node_map.end(); ++_iterator)
  {
    if (_iterator->second->isAlive())
    {
      if (best_w < _iterator->second->get_individual()->get_wp())
      {
        best_w    = _iterator->second->get_individual()->get_wp();
        best_node = _iterator->second;
      }
    }
  }
  return best_node;
}

/*----------------------------
 * SETTERS
 *----------------------------*/


#endif /* defined(__SigmaFGM__Tree__) */
