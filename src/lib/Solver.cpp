
/**
 * \file      Solver.cpp
 * \authors   Charles Rocabert, Samuel Bernard
 * \date      07-06-2016
 * \copyright Copyright (C) 2016 Charles Rocabert, Samuel Bernard. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     Solver class definition
 */

/***********************************************************************
 * Copyright (C) 2016 Charles Rocabert, Samuel Bernard
 * E-mail: charles.rocabert@gmail.com
 * Web:
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

#include "Solver.h"


/*----------------------------
 * CONSTRUCTORS
 *----------------------------*/

Solver::Solver( Parameters* parameters )
{
  /*----------------------------------------------- PARAMETERS */
  
  _parameters = parameters;
  
  /*----------------------------------------------- LIST OF PARTICLES */
  
  _particles_list.clear();
  _iterator = _particles_list.begin();
  _current_identifier = 0;
  
  /*----------------------------------------------- DYNAMIC VARIABLES */
  
  _z_opt_stab = gsl_vector_alloc(parameters->get_number_of_dimensions());
  if (parameters->get_one_axis())
  {
    gsl_vector_set(_z_opt_stab, 0, parameters->get_initial_mu());
  }
  else
  {
    gsl_vector_set_all(_z_opt_stab, parameters->get_initial_mu());
  }
  _z_opt = gsl_vector_alloc(parameters->get_number_of_dimensions());
  gsl_vector_set_zero(_z_opt);
  _step = 0;
  _t    = 0.0;
  
  /*----------------------------------------------- STATISTICS */
  
  _statistics = NULL;
  if (_parameters->get_statistics())
  {
    _statistics = new Statistics(_parameters);
    _statistics->reset();
  }
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
Solver::~Solver( void )
{
  /*----------------------------------------------- LIST OF PARTICLES */
  
  _iterator = _particles_list.begin();
  while (_iterator != _particles_list.end())
  {
    delete _iterator->second;
    _iterator->second = NULL;
    _iterator++;
  }
  _particles_list.clear();
  
  /*----------------------------------------------- STATISTICS */
  
  delete _statistics;
  _statistics = NULL;
}


/*----------------------------
 * PUBLIC METHODS
 *----------------------------*/

/**
 * \brief    Initialize the solver
 * \details  --
 * \param    void
 * \return   \e void
 */
void Solver::initialize( void )
{
  bool stabilize = (_parameters->get_stabilizing_time() > 0 ? true : false);
  initialize_particles_list();
  initialize_solver_state(stabilize);
  if (_parameters->get_statistics())
  {
    _statistics->write_headers();
  }
}

/**
 * \brief    Stabilize the initial solver state
 * \details  --
 * \param    void
 * \return   \e void
 */
void Solver::stabilize( void )
{
  std::cout << "> stabilizing initial state ...\n";
  while (_step < _parameters->get_stabilizing_time())
  {
    update(true);
  }
  _step = 0;
  _t    = 0.0;
}

/**
 * \brief    Update the solver state with adaptive time
 * \details  --
 * \param    bool stabilize
 * \return   \e void
 */
void Solver::update( bool stabilize )
{
  gsl_vector* z_opt = NULL;
  if (stabilize)
  {
    z_opt = _z_opt_stab;
  }
  else
  {
    z_opt = _z_opt;
  }
  std::vector<Particle*> to_duplicate;
  std::vector<size_t> to_delete;
  to_duplicate.reserve(_parameters->get_number_of_particles());
  to_delete.reserve(_parameters->get_number_of_particles());
  
  /*******************************************/
  /* 1) Get best fitness and compute dt      */
  /*******************************************/
  
  double best_w = 0.0;
  for (_iterator = _particles_list.begin(); _iterator != _particles_list.end(); ++_iterator)
  {
    if (best_w < _iterator->second->get_wp())
    {
      best_w = _iterator->second->get_wp();
    }
  }
  double dt = 0.1/best_w;
  _t       += dt;
  _step    += 1;
  
  /*******************************************/
  /* 2) Apply particle proliferation         */
  /*******************************************/
  
  for (_iterator = _particles_list.begin(); _iterator != _particles_list.end(); ++_iterator)
  {
    if (_parameters->get_prng()->uniform() < _iterator->second->get_wp()*0.1/best_w)
    {
      to_duplicate.push_back(_iterator->second);
    }
  }
  for (size_t i = 0; i < to_duplicate.size(); i++)
  {
    _particles_list[_current_identifier] = new Particle(*to_duplicate[i]);
    _current_identifier++;
  }
  
  /*******************************************/
  /* 3) Compute new phenotypes and fitnesses */
  /*******************************************/
  
  tbb::task_group tasks;
  for (size_t i = 0; i < to_duplicate.size(); i++)
  {
    tasks.run([=]{update_particle(to_duplicate[i], z_opt);});
  }
  tasks.wait();
  to_duplicate.clear();
  
  /*******************************************/
  /* 4) Apply particle death                 */
  /*******************************************/
  
  double pdeath = (double)(_particles_list.size()-_parameters->get_number_of_particles())/(double)(_particles_list.size());
  if (pdeath > 0.0)
  {
    for (_iterator = _particles_list.begin(); _iterator != _particles_list.end(); ++_iterator)
    {
      if (_parameters->get_prng()->uniform() < pdeath)
      {
        to_delete.push_back(_iterator->first);
      }
    }
  }
  for (size_t i = 0; i < to_delete.size(); i++)
  {
    delete _particles_list[to_delete[i]];
    _particles_list[to_delete[i]] = NULL;
    _particles_list.erase(_particles_list.find(to_delete[i]));
  }
  to_delete.clear();
}

/**
 * \brief    Compute statistics
 * \details  --
 * \param    void
 * \return   \e void
 */
void Solver::compute_statistics( void )
{
  _statistics->reset();
  for (_iterator = _particles_list.begin(); _iterator != _particles_list.end(); ++_iterator)
  {
    _statistics->add_particle(_iterator->second);
  }
  _statistics->compute_statistics();
}

/**
 * \brief    Write statistics
 * \details  --
 * \param    void
 * \return   \e void
 */
void Solver::write_statistics( void )
{
  _statistics->write_statistics(_step, _t);
  _statistics->flush();
}

/**
 * \brief    Close statistics
 * \details  --
 * \param    void
 * \return   \e void
 */
void Solver::close_statistics( void )
{
  _statistics->close();
}

/*----------------------------
 * PROTECTED METHODS
 *----------------------------*/

/**
 * \brief    Initialize the particle list
 * \details  --
 * \param    void
 * \return   \e void
 */
void Solver::initialize_particles_list( void )
{
  size_t n = _parameters->get_number_of_dimensions();
  for (size_t i = 0; i < _parameters->get_number_of_particles(); i++)
  {
    Particle* particle = new Particle(_parameters->get_prng(), n, _parameters->get_delta_mu(), _parameters->get_delta_sigma(), _parameters->get_delta_theta(), _parameters->get_initial_mu(), _parameters->get_initial_sigma(), _parameters->get_initial_theta(), _parameters->get_one_axis(), _parameters->get_weight_fitness(), _parameters->get_no_noise(), _parameters->get_no_rotation());
    _particles_list[_current_identifier] = particle;
    _current_identifier++;
  }
}

/**
 * \brief    Initialize the solver state
 * \details  --
 * \param    bool stabilize
 * \return   \e void
 */
void Solver::initialize_solver_state( bool stabilize )
{
  gsl_vector* z_opt = NULL;
  if (stabilize)
  {
    z_opt = _z_opt_stab;
  }
  else
  {
    z_opt = _z_opt;
  }
  _step = 0;
  _t    = 0.0;
  for (_iterator = _particles_list.begin(); _iterator != _particles_list.end(); ++_iterator)
  {
    _iterator->second->build_phenotype();
    _iterator->second->compute_fitness(z_opt);
    if (_statistics != NULL)
    {
      _statistics->add_particle(_iterator->second);
    }
  }
}

/**
 * \brief    Update the particle state
 * \details  --
 * \param    bool stabilize
 * \return   \e void
 */
void Solver::update_particle( Particle* particle, gsl_vector* z_opt )
{
  particle->jump();
  particle->build_phenotype();
  particle->compute_fitness(z_opt);
}

