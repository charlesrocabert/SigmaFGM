
/**
 * \file      Node.cpp
 * \authors   Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon
 * \date      04-04-2018
 * \copyright Copyright (C) 2016-2018 Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     Node class definition
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

#include "Node.h"


/*----------------------------
 * CONSTRUCTORS
 *----------------------------*/

/**
 * \brief    Constructor
 * \details  --
 * \param    unsigned long long int identifier
 * \param    int generation
 * \return   \e void
 */
Node::Node( unsigned long long int identifier, int generation )
{
  assert(generation >= 0);
  _identifier = identifier;
  _generation = generation;
  _individual = NULL;
  _parent     = NULL;
  _children.clear();
  _node_class = MASTER_ROOT;
  _node_state = DEAD;
  _tagged     = false;
}

/**
 * \brief    Alive node constructor
 * \details  --
 * \param    Individual* individual
 * \return   \e void
 */
Node::Node( Individual* individual )
{
  _identifier = individual->get_identifier();
  _generation = individual->get_generation();
  _individual = new Individual(*individual);
  _parent     = NULL;
  _children.clear();
  _node_class = NORMAL;
  _node_state = ALIVE;
  _tagged     = false;
}

/*----------------------------
 * DESTRUCTORS
 *----------------------------*/

/**
 * \brief    Destructor
 * \details  --
 * \param    void
 * \return   \e void
 */
Node::~Node( void )
{
  delete _individual;
  _individual = NULL;
  _children.clear();
}

/*----------------------------
 * PUBLIC METHODS
 *----------------------------*/

/**
 * \brief    Add a child
 * \details  --
 * \param    Node* node
 * \return   \e void
 */
void Node::add_child( Node* node )
{
  for (int i = 0; i < (int)_children.size(); i++)
  {
    assert(node->get_identifier() != _children[i]->get_identifier());
  }
  _children.push_back(node);
}

/**
 * \brief    Remove a child
 * \details  --
 * \param    Node* node
 * \return   \e void
 */
void Node::remove_child( Node* node )
{
  int pos = -1;
  for (int i = 0; i < (int)_children.size(); i++)
  {
    if (node->get_identifier() == _children[i]->get_identifier() && pos == -1)
    {
      pos = (int)i;
    }
    else if (node->get_identifier() == _children[i]->get_identifier() && pos >= 0)
    {
      printf("Error in Node::remove_child(): multiple occurences of a node in children list. Exit.\n");
      exit(EXIT_FAILURE);
    }
  }
  if (pos == -1)
  {
    printf("Error in Node::remove_child(): node to remove do not exist. Exit.\n");
    exit(EXIT_FAILURE);
  }
  else
  {
    _children.erase(_children.begin()+pos);
  }
}

/**
 * \brief    Replace this child by its own children
 * \details  --
 * \param    Node* node_to_remove
 * \return   \e void
 */
void Node::replace_children( Node* child_to_remove )
{
  /*---------------------------------------*/
  /* 1) remove the node from children list */
  /*---------------------------------------*/
  remove_child(child_to_remove);
  
  /*---------------------------------------*/
  /* 2) add children to the children list  */
  /*---------------------------------------*/
  for (int i = 0; i < child_to_remove->get_number_of_children(); i++)
  {
    add_child(child_to_remove->get_child(i));
  }
}

/**
 * \brief    Tag the lineage of this node
 * \details  --
 * \param    void
 * \return   \e void
 */
void Node::tag_lineage( void )
{
  _tagged = true;
  Node* node = _parent;
  while (node != NULL)
  {
    node->tag();
    node = node->get_parent();
    if (node != NULL)
    {
      if (node->isTagged())
      {
        node = NULL;
      }
    }
  }
}

/**
 * \brief    Untag the lineage of this node
 * \details  --
 * \param    void
 * \return   \e void
 */
void Node::untag_lineage( void )
{
  _tagged = false;
  Node* node = _parent;
  while (node != NULL)
  {
    node->untag();
    node = node->get_parent();
    if (node != NULL)
    {
      if (!node->isTagged())
      {
        node = NULL;
      }
    }
  }
}

/*----------------------------
 * PROTECTED METHODS
 *----------------------------*/
