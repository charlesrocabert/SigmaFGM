
/**
 * \file      Statistics.cpp
 * \authors   Charles Rocabert, Samuel Bernard
 * \date      07-06-2016
 * \copyright Copyright (C) 2016-2017 Charles Rocabert, Samuel Bernard. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     Statistics class definition
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

#include "Statistics.h"


/*----------------------------
 * CONSTRUCTORS
 *----------------------------*/

/**
 * \brief    Constructor
 * \details  --
 * \param    Parameters* parameters
 * \return   \e void
 */
Statistics::Statistics( Parameters* parameters )
{
  /*----------------------------------------------- PARAMETERS */
  
  _parameters   = parameters;
  _nb_particles = 0;
  
  /*----------------------------------------------- BEST VALUES */
  
  _dmu_best             = 0.0;
  _dp_best              = 0.0;
  _wmu_best             = 0.0;
  _wp_best              = 0.0;
  _EV_best              = 0.0;
  _EV_contribution_best = 0.0;
  _EV_dot_product_best  = 0.0;
  
  /*----------------------------------------------- MEAN VALUES */
  
  _dmu_mean             = 0.0;
  _dp_mean              = 0.0;
  _wmu_mean             = 0.0;
  _wp_mean              = 0.0;
  _EV_mean              = 0.0;
  _EV_contribution_mean = 0.0;
  _EV_dot_product_mean  = 0.0;
  
  /*----------------------------------------------- STANDARD DEVIATION VALUES */
  
  _dmu_sd             = 0.0;
  _dp_sd              = 0.0;
  _wmu_sd             = 0.0;
  _wp_sd              = 0.0;
  _EV_sd              = 0.0;
  _EV_contribution_sd = 0.0;
  _EV_dot_product_sd  = 0.0;
  
  /*----------------------------------------------- STATISTIC FILES */
  
  if (_parameters->get_statistics())
  {
    _best_file.open("best.txt", std::ios::out | std::ios::trunc);
    _mean_file.open("mean.txt", std::ios::out | std::ios::trunc);
    _var_file.open("sd.txt", std::ios::out | std::ios::trunc);
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
Statistics::~Statistics( void )
{
  /* NOTHING TO DO */
}

/*----------------------------
 * PUBLIC METHODS
 *----------------------------*/

/**
 * \brief    Write file headers
 * \details  --
 * \param    void
 * \return   \e void
 */
void Statistics::write_headers( void )
{
  /*----------------------------------------------- BEST VALUES */
  
  _best_file << "step" << " ";
  _best_file << "t" << " ";
  _best_file << "dmu" << " ";
  _best_file << "dp" << " ";
  _best_file << "wmu" << " ";
  _best_file << "wp" << " ";
  _best_file << "EV" << " ";
  _best_file << "EV_contrib" << " ";
  _best_file << "EV_dot_product" << "\n";
  
  /*----------------------------------------------- MEAN VALUES */
  
  _mean_file << "step" << " ";
  _mean_file << "t" << " ";
  _mean_file << "dmu" << " ";
  _mean_file << "dp" << " ";
  _mean_file << "wmu" << " ";
  _mean_file << "wp" << " ";
  _mean_file << "EV" << " ";
  _mean_file << "EV_contrib" << " ";
  _mean_file << "EV_dot_product" << "\n";
  
  /*----------------------------------------------- STANDARD DEVIATION VALUES */
  
  _var_file << "step" << " ";
  _var_file << "t" << " ";
  _var_file << "dmu" << " ";
  _var_file << "dp" << " ";
  _var_file << "wmu" << " ";
  _var_file << "wp" << " ";
  _var_file << "EV" << " ";
  _var_file << "EV_contrib" << " ";
  _var_file << "EV_dot_product" << "\n";
}

/**
 * \brief    Add a particle to the statistics
 * \details  --
 * \param    Particle* particle
 * \return   \e void
 */
void Statistics::add_particle( Particle* particle )
{
  _nb_particles++;
  
  /*----------------------------------------------- BEST VALUES */
  
  if (particle->get_wp() > _wp_best)
  {
    _dmu_best             = particle->get_dmu();
    _dp_best              = particle->get_dp();
    _wmu_best             = particle->get_wmu();
    _wp_best              = particle->get_wp();
    _EV_best              = particle->get_max_Sigma_eigenvalue();
    _EV_contribution_best = particle->get_max_Sigma_contribution();
    _EV_dot_product_best  = particle->get_max_dot_product();
  }
  _dmu_mean             += particle->get_dmu();
  _dp_mean              += particle->get_dp();
  _wmu_mean             += particle->get_wmu();
  _wp_mean              += particle->get_wp();
  _EV_mean              += particle->get_max_Sigma_eigenvalue();
  _EV_contribution_mean += particle->get_max_Sigma_contribution();
  _EV_dot_product_mean  += particle->get_max_dot_product();
  _wmu_sd               += particle->get_wmu()*particle->get_wmu();
  _wp_sd                += particle->get_wp()*particle->get_wp();
  _dmu_sd               += particle->get_dmu()*particle->get_dmu();
  _dp_sd                += particle->get_dmu()*particle->get_dp();
  _EV_sd                += particle->get_max_Sigma_eigenvalue()*particle->get_max_Sigma_eigenvalue();
  _EV_contribution_sd   += particle->get_max_Sigma_contribution()*particle->get_max_Sigma_contribution();
  _EV_dot_product_sd    += particle->get_max_dot_product()*particle->get_max_dot_product();
}

/**
 * \brief    Compute statistics
 * \details  --
 * \param    void
 * \return   \e void
 */
void Statistics::compute_statistics( void )
{
  _dmu_mean             /= (double)_nb_particles;
  _dp_mean              /= (double)_nb_particles;
  _wmu_mean             /= (double)_nb_particles;
  _wp_mean              /= (double)_nb_particles;
  _EV_mean              /= (double)_nb_particles;
  _EV_contribution_mean /= (double)_nb_particles;
  _EV_dot_product_mean  /= (double)_nb_particles;
  _dmu_sd               /= (double)_nb_particles;
  _dp_sd                /= (double)_nb_particles;
  _wmu_sd               /= (double)_nb_particles;
  _wp_sd                /= (double)_nb_particles;
  _EV_sd                /= (double)_nb_particles;
  _EV_contribution_sd   /= (double)_nb_particles;
  _EV_dot_product_sd    /= (double)_nb_particles;
  _dmu_sd               -= _dmu_mean*_dmu_mean;
  _dp_sd                -= _dp_mean*_dp_mean;
  _wmu_sd               -= _wmu_mean*_wmu_mean;
  _wp_sd                -= _wp_mean*_wp_mean;
  _EV_sd                -= _EV_mean*_EV_mean;
  _EV_contribution_sd   -= _EV_contribution_mean*_EV_contribution_mean;
  _EV_dot_product_sd    -= _EV_dot_product_mean*_EV_dot_product_mean;
  if (_dmu_sd < 1e-15)
  {
    _dmu_sd = 0.0;
  }
  else
  {
    _dmu_sd = sqrt(_dmu_sd);
  }
  if (_dp_sd < 1e-15)
  {
    _dp_sd = 0.0;
  }
  else
  {
    _dp_sd = sqrt(_dp_sd);
  }
  if (_wmu_sd < 1e-15)
  {
    _wmu_sd = 0.0;
  }
  else
  {
    _wmu_sd = sqrt(_wmu_sd);
  }
  if (_wp_sd < 1e-15)
  {
    _wp_sd = 0.0;
  }
  else
  {
    _wp_sd = sqrt(_wp_sd);
  }
  if (_EV_sd < 1e-15)
  {
    _EV_sd = 0.0;
  }
  else
  {
    _EV_sd = sqrt(_EV_sd);
  }
  if (_EV_contribution_sd < 1e-15)
  {
    _EV_contribution_sd = 0.0;
  }
  else
  {
    _EV_contribution_sd = sqrt(_EV_contribution_sd);
  }
  if (_EV_dot_product_sd < 1e-15)
  {
    _EV_dot_product_sd = 0.0;
  }
  else
  {
    _EV_dot_product_sd = sqrt(_EV_dot_product_sd);
  }
}

/**
 * \brief    Write statistics
 * \details  --
 * \param    size_t step
 * \param    double time
 * \return   \e void
 */
void Statistics::write_statistics( size_t step, double time )
{
  /*----------------------------------------------- BEST VALUES */
  
  _best_file << step << " ";
  _best_file << time << " ";
  _best_file << _dmu_best << " ";
  _best_file << _dp_best << " ";
  _best_file << _wmu_best << " ";
  _best_file << _wp_best << " ";
  _best_file << _EV_best << " ";
  _best_file << _EV_contribution_best << " ";
  _best_file << _EV_dot_product_best << "\n";
  
  /*----------------------------------------------- MEAN VALUES */
  
  _mean_file << step << " ";
  _mean_file << time << " ";
  _mean_file << _dmu_mean << " ";
  _mean_file << _dp_mean << " ";
  _mean_file << _wmu_mean << " ";
  _mean_file << _wp_mean << " ";
  _mean_file << _EV_mean << " ";
  _mean_file << _EV_contribution_mean << " ";
  _mean_file << _EV_dot_product_mean << "\n";
  
  /*----------------------------------------------- STANDARD DEVIATION VALUES */
  
  _var_file << step << " ";
  _var_file << time << " ";
  _var_file << _dmu_sd << " ";
  _var_file << _dp_sd << " ";
  _var_file << _wmu_sd << " ";
  _var_file << _wp_sd << " ";
  _var_file << _EV_sd << " ";
  _var_file << _EV_contribution_sd << " ";
  _var_file << _EV_dot_product_sd << "\n";
}

/**
 * \brief    Reset statistics
 * \details  --
 * \param    void
 * \return   \e void
 */
void Statistics::reset( void )
{
  /*----------------------------------------------- PARAMETERS */
  
  _nb_particles = 0;
  
  /*----------------------------------------------- BEST VALUES */
  
  _dmu_best             = 0.0;
  _dp_best              = 0.0;
  _wmu_best             = 0.0;
  _wp_best              = 0.0;
  _EV_best              = 0.0;
  _EV_contribution_best = 0.0;
  _EV_dot_product_best  = 0.0;
  
  /*----------------------------------------------- MEAN VALUES */
  
  _dmu_mean             = 0.0;
  _dp_mean              = 0.0;
  _wmu_mean             = 0.0;
  _wp_mean              = 0.0;
  _EV_mean              = 0.0;
  _EV_contribution_mean = 0.0;
  _EV_dot_product_mean  = 0.0;
  
  /*----------------------------------------------- STANDARD DEVIATION VALUES */
  
  _dmu_sd             = 0.0;
  _dp_sd              = 0.0;
  _wmu_sd             = 0.0;
  _wp_sd              = 0.0;
  _EV_sd              = 0.0;
  _EV_contribution_sd = 0.0;
  _EV_dot_product_sd  = 0.0;
}

/**
 * \brief    Flush statistics files
 * \details  --
 * \param    void
 * \return   \e void
 */
void Statistics::flush( void )
{
  _best_file.flush();
  _mean_file.flush();
  _var_file.flush();
}

/**
 * \brief    Close statistics files
 * \details  --
 * \param    void
 * \return   \e void
 */
void Statistics::close( void )
{
  _best_file.close();
  _mean_file.close();
  _var_file.close();
}

/*----------------------------
 * PROTECTED METHODS
 *----------------------------*/
