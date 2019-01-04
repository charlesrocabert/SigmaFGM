
/**
 * \file      Tree.cpp
 * \authors   Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon
 * \date      04-04-2018
 * \copyright Copyright (C) 2016-2019 Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     Tree class definition
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

#include "Tree.h"


/*----------------------------
 * CONSTRUCTORS
 *----------------------------*/

/**
 * \brief    Default constructor
 * \details  The tree starts with one node called the master root
 * \param    --
 * \return   \e void
 */
Tree::Tree( void )
{
  _node_map.clear();
  _iterator         = _node_map.begin();
  Node* master_root = new Node(0, 0);
  _node_map[0]      = master_root;
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
Tree::~Tree( void )
{
  _iterator = _node_map.begin();
  for (_iterator = _node_map.begin(); _iterator != _node_map.end(); ++_iterator)
  {
    delete _iterator->second;
    _iterator->second = NULL;
  }
  _node_map.clear();
}

/*----------------------------
 * PUBLIC METHODS
 *----------------------------*/

/**
 * \brief    Add a root to the tree
 * \details  --
 * \param    Individual* individual
 * \return   \e void
 */
void Tree::add_root( Individual* individual )
{
  /*-----------------------------*/
  /* 1) Get the master root      */
  /*-----------------------------*/
  Node* master_root = _node_map[0];
  
  /*-----------------------------*/
  /* 2) Create the node          */
  /*-----------------------------*/
  Node* node = new Node(individual);
  
  /*-----------------------------*/
  /* 3) Update nodes attributes  */
  /*-----------------------------*/
  node->set_root();
  node->set_parent(master_root);
  master_root->add_child(node);
  
  /*-----------------------------*/
  /* 4) Add the node to the tree */
  /*-----------------------------*/
  assert(_node_map.find(node->get_identifier()) == _node_map.end());
  _node_map[node->get_identifier()] = node;
}

/**
 * \brief    Add a reproduction event
 * \details  --
 * \param    Individual* parent
 * \param    Individual* child
 * \return   \e void
 */
void Tree::add_reproduction_event( Individual* parent, Individual* child )
{
  /*---------------------------------*/
  /* 1) Get parental node            */
  /*---------------------------------*/
  assert(_node_map.find(parent->get_identifier()) != _node_map.end());
  Node* parent_node = _node_map[parent->get_identifier()];
  parent_node->set_dead();
  
  /*---------------------------------*/
  /* 2) Create child node            */
  /*---------------------------------*/
  Node* child_node = new Node(child);
  
  /*---------------------------------*/
  /* 3) Update child node attributes */
  /*---------------------------------*/
  child_node->set_parent(parent_node);
  parent_node->add_child(child_node);
  
  /*---------------------------------*/
  /* 4) Add child node to the tree   */
  /*---------------------------------*/
  _node_map[child_node->get_identifier()] = child_node;
}

/**
 * \brief    Delete a node and remove all links
 * \details  --
 * \param    unsigned long long int node_identifier
 * \return   \e void
 */
void Tree::delete_node( unsigned long long int node_identifier )
{
  assert(_node_map.find(node_identifier) != _node_map.end());
  Node* node = _node_map[node_identifier];
  assert(node->get_identifier() == node_identifier);
  assert(!node->isAlive());
  
  /*----------------------------------*/
  /* 1) Update parental children list */
  /*----------------------------------*/
  node->get_parent()->replace_children(node);
  
  /*-----------------------------------*/
  /* 2) Set the new parent of children */
  /*-----------------------------------*/
  for (int i = 0; i < node->get_parent()->get_number_of_children(); i++)
  {
    node->get_parent()->get_child(i)->set_parent(node->get_parent());
  }
  
  /*----------------------------------*/
  /* 3) Delete node                   */
  /*----------------------------------*/
  delete _node_map[node_identifier];
  _node_map[node_identifier] = NULL;
  _node_map.erase(node_identifier);
}

/**
 * \brief    Prune the tree
 * \details  Remove all dead branches
 * \param    void
 * \return   \e void
 */
void Tree::prune()
{
  untag_tree();
  
  /*-------------------------------------*/
  /* 1) Tag alive cells lineage          */
  /*-------------------------------------*/
  for (_iterator = _node_map.begin(); _iterator != _node_map.end(); ++_iterator)
  {
    assert(_iterator->first == _iterator->second->get_identifier());
    if (_iterator->second->isAlive())
    {
      _iterator->second->tag_lineage();
    }
  }
  
  /*-------------------------------------*/
  /* 2) Build the list of untagged nodes */
  /*-------------------------------------*/
  std::vector<unsigned long long int> remove_list;
  for (_iterator = _node_map.begin(); _iterator != _node_map.end(); ++_iterator)
  {
    if (!_iterator->second->isTagged() && !_iterator->second->isMasterRoot())
    {
      remove_list.push_back(_iterator->first);
    }
  }
  
  /*-------------------------------------*/
  /* 3) Delete untagged nodes            */
  /*-------------------------------------*/
  for (size_t i = 0; i < remove_list.size(); i++)
  {
    delete_node(remove_list[i]);
  }
  remove_list.clear();
  
  /*-------------------------------------*/
  /* 4) Set master root children as root */
  /*-------------------------------------*/
  Node* master_root = _node_map[0];
  for (int i = 0; i < master_root->get_number_of_children(); i++)
  {
    master_root->get_child(i)->set_root();
  }
}

/**
 * \brief    Write best lineage statistics
 * \details  --
 * \param    void
 * \return   \e void
 */
void Tree::write_best_lineage_statistics( void )
{
  Node* node = get_best_alive_node();
  std::ofstream file("best_lineage.txt", std::ios::out | std::ios::trunc);
  file << "id" << " ";
  file << "t" << " ";
  file << "dX" << " ";
  file << "dz" << " ";
  file << "WX" << " ";
  file << "Wz" << " ";
  file << "EV" << " ";
  file << "EV_contrib" << " ";
  file << "EV_dot_product" << " ";
  file << "r_X" << " ";
  file << "r_Ve" << " ";
  file << "r_Theta" << "\n";
  while (!node->isMasterRoot())
  {
    file << node->get_identifier() << " ";
    file << node->get_generation() << " ";
    file << node->get_individual()->get_dX() << " ";
    file << node->get_individual()->get_dz() << " ";
    file << node->get_individual()->get_WX() << " ";
    file << node->get_individual()->get_Wz() << " ";
    file << node->get_individual()->get_max_Sigma_eigenvalue() << " ";
    file << node->get_individual()->get_max_Sigma_contribution() << " ";
    file << node->get_individual()->get_max_dot_product() << " ";
    file << node->get_individual()->get_r_X() << " ";
    file << node->get_individual()->get_r_Ve() << " ";
    file << node->get_individual()->get_r_Theta() << "\n";
    node = node->get_parent();
  }
  file.close();
}

/*----------------------------
 * PROTECTED METHODS
 *----------------------------*/

/**
 * \brief    Tag all the offspring of this node
 * \details  --
 * \param    Node* node
 * \param    std::vector<Node*>* tagged_nodes
 * \return   \e void
 */
void Tree::tag_offspring( Node* node, std::vector<Node*>* tagged_nodes )
{
  untag_tree();
  tagged_nodes->clear();
  tagged_nodes->push_back(node);
  bool end = false;
  while (!end)
  {
    end = true;
    for (int i = 0; i < (int)tagged_nodes->size(); i++)
    {
      for (int j = 0; j < tagged_nodes->at(i)->get_number_of_children(); j++)
      {
        if (!tagged_nodes->at(i)->get_child(j)->isTagged())
        {
          end = false;
          tagged_nodes->at(i)->get_child(j)->tag();
          tagged_nodes->push_back(tagged_nodes->at(i)->get_child(j));
        }
      }
    }
  }
}

