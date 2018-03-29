
/**
 * \file      Statistics.cpp
 * \authors   Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon
 * \date      07-06-2016
 * \copyright Copyright (C) 2016-2018 Charles Rocabert, Samuel Bernard, Carole Knibbe, Guillaume Beslon. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     Statistics class definition
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

#include "Statistics.h"


/*----------------------------
 * CONSTRUCTORS
 *----------------------------*/

/**
 * \brief    Default constructor
 * \details  --
 * \param    void
 * \return   \e void
 */
Statistics::Statistics( void )
{
  
  /*----------------------------------------------- MEAN VALUES */
  
  _dg_mean              = 0.0;
  _dp_mean              = 0.0;
  _wg_mean              = 0.0;
  _wp_mean              = 0.0;
  _EV_mean              = 0.0;
  _EV_contribution_mean = 0.0;
  _EV_dot_product_mean  = 0.0;
  _r_mu_mean            = 0.0;
  _r_sigma_mean         = 0.0;
  _r_theta_mean         = 0.0;
  
  /*----------------------------------------------- STANDARD DEVIATION VALUES */
  
  _dg_sd              = 0.0;
  _dp_sd              = 0.0;
  _wg_sd              = 0.0;
  _wp_sd              = 0.0;
  _EV_sd              = 0.0;
  _EV_contribution_sd = 0.0;
  _EV_dot_product_sd  = 0.0;
  _r_mu_sd            = 0.0;
  _r_sigma_sd         = 0.0;
  _r_theta_sd         = 0.0;
  
  /*----------------------------------------------- STATISTIC FILES */
  
  _mean_file.open("mean.txt", std::ios::out | std::ios::trunc);
  _sd_file.open("sd.txt", std::ios::out | std::ios::trunc);
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
  
  /*----------------------------------------------- MEAN VALUES */
  
  _mean_file << "t" << " ";
  _mean_file << "dg" << " ";
  _mean_file << "dp" << " ";
  _mean_file << "wg" << " ";
  _mean_file << "wp" << " ";
  _mean_file << "EV" << " ";
  _mean_file << "EV_contrib" << " ";
  _mean_file << "EV_dot_product" << " ";
  _mean_file << "r_mu" << " ";
  _mean_file << "r_sigma" << " ";
  _mean_file << "r_theta" << "\n";
  
  /*----------------------------------------------- STANDARD DEVIATION VALUES */
  
  _sd_file << "t" << " ";
  _sd_file << "dg" << " ";
  _sd_file << "dp" << " ";
  _sd_file << "wg" << " ";
  _sd_file << "wp" << " ";
  _sd_file << "EV" << " ";
  _sd_file << "EV_contrib" << " ";
  _sd_file << "EV_dot_product" << " ";
  _sd_file << "r_mu" << " ";
  _sd_file << "r_sigma" << " ";
  _sd_file << "r_theta" << "\n";
}

/**
 * \brief    Compute statistics from the population
 * \details  --
 * \param    Population* population
 * \return   \e void
 */
void Statistics::compute_statistics( Population* population )
{
  for (int i = 0; i < population->get_population_size(); i++)
  {
    Individual* ind = population->get_individual(i);
    
    /*----------------------------------------------- MEAN VALUES */
    
    _dg_mean              += ind->get_dg();
    _dp_mean              += ind->get_dp();
    _wg_mean              += ind->get_wg();
    _wp_mean              += ind->get_wp();
    _EV_mean              += ind->get_max_Sigma_eigenvalue();
    _EV_contribution_mean += ind->get_max_Sigma_contribution();
    _EV_dot_product_mean  += ind->get_max_dot_product();
    _r_mu_mean            += ind->get_r_mu();
    _r_sigma_mean         += ind->get_r_sigma();
    _r_theta_mean         += ind->get_r_theta();
    
    /*----------------------------------------------- STANDARD DEVIATION VALUES */
    
    _dg_sd              += ind->get_dg()*ind->get_dg();
    _dp_sd              += ind->get_dp()*ind->get_dp();
    _wg_sd              += ind->get_wg()*ind->get_wg();
    _wp_sd              += ind->get_wp()*ind->get_wp();
    _EV_sd              += ind->get_max_Sigma_eigenvalue()*ind->get_max_Sigma_eigenvalue();
    _EV_contribution_sd += ind->get_max_Sigma_contribution()*ind->get_max_Sigma_contribution();
    _EV_dot_product_sd  += ind->get_max_dot_product()*ind->get_max_dot_product();
    _r_mu_sd            += ind->get_r_mu()*ind->get_r_mu();
    _r_sigma_sd         += ind->get_r_sigma()*ind->get_r_sigma();
    _r_theta_sd         += ind->get_r_theta()*ind->get_r_theta();
  }
  
  double N = (double)population->get_population_size();
  
  /*----------------------------------------------- MEAN VALUES */
  
  _dg_mean              /= N;
  _dp_mean              /= N;
  _wg_mean              /= N;
  _wp_mean              /= N;
  _EV_mean              /= N;
  _EV_contribution_mean /= N;
  _EV_dot_product_mean  /= N;
  _r_mu_mean            /= N;
  _r_sigma_mean         /= N;
  _r_theta_mean         /= N;
  
  /*----------------------------------------------- STANDARD DEVIATION VALUES */
  
  _dg_sd              /= N;
  _dp_sd              /= N;
  _wg_sd              /= N;
  _wp_sd              /= N;
  _EV_sd              /= N;
  _EV_contribution_sd /= N;
  _EV_dot_product_sd  /= N;
  _r_mu_sd            /= N;
  _r_sigma_sd         /= N;
  _r_theta_sd         -= N;
  _dg_sd              -= _dg_mean*_dg_mean;
  _dp_sd              -= _dp_mean*_dp_mean;
  _wg_sd              -= _wg_mean*_wg_mean;
  _wp_sd              -= _wp_mean*_wp_mean;
  _EV_sd              -= _EV_mean*_EV_mean;
  _EV_contribution_sd -= _EV_contribution_mean*_EV_contribution_mean;
  _EV_dot_product_sd  -= _EV_dot_product_mean*_EV_dot_product_mean;
  _r_mu_sd            -= _r_mu_mean*_r_mu_mean;
  _r_sigma_sd         -= _r_sigma_mean*_r_sigma_mean;
  _r_theta_sd         -= _r_theta_mean*_r_theta_mean;
  if (_dg_sd < 1e-15)
  {
    _dg_sd = 0.0;
  }
  else
  {
    _dg_sd = sqrt(_dg_sd);
  }
  if (_dp_sd < 1e-15)
  {
    _dp_sd = 0.0;
  }
  else
  {
    _dp_sd = sqrt(_dp_sd);
  }
  if (_wp_sd < 1e-15)
  {
    _wp_sd = 0.0;
  }
  else
  {
    _wp_sd = sqrt(_wp_sd);
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
  if (_r_mu_sd < 1e-15)
  {
    _r_mu_sd = 0.0;
  }
  else
  {
    _r_mu_sd = sqrt(_r_mu_sd);
  }
  if (_r_sigma_sd < 1e-15)
  {
    _r_sigma_sd = 0.0;
  }
  else
  {
    _r_sigma_sd = sqrt(_r_sigma_sd);
  }
  if (_r_theta_sd < 1e-15)
  {
    _r_theta_sd = 0.0;
  }
  else
  {
    _r_theta_sd = sqrt(_r_theta_sd);
  }
}

/**
 * \brief    Write statistics
 * \details  --
 * \param    int simulation_time
 * \return   \e void
 */
void Statistics::write_statistics( int simulation_time )
{
  /*----------------------------------------------- MEAN VALUES */
  
  _mean_file << simulation_time << " ";
  _mean_file << _dg_mean << " ";
  _mean_file << _dp_mean << " ";
  _mean_file << _wg_mean << " ";
  _mean_file << _wp_mean << " ";
  _mean_file << _EV_mean << " ";
  _mean_file << _EV_contribution_mean << " ";
  _mean_file << _EV_dot_product_mean << " ";
  _mean_file << _r_mu_mean << " ";
  _mean_file << _r_sigma_mean << " ";
  _mean_file << _r_theta_mean << "\n";
  
  /*----------------------------------------------- STANDARD DEVIATION VALUES */
  
  _sd_file << simulation_time << " ";
  _sd_file << _dg_sd << " ";
  _sd_file << _dp_sd << " ";
  _sd_file << _wg_sd << " ";
  _sd_file << _wp_sd << " ";
  _sd_file << _EV_sd << " ";
  _sd_file << _EV_contribution_sd << " ";
  _sd_file << _EV_dot_product_sd << " ";
  _sd_file << _r_mu_sd << " ";
  _sd_file << _r_sigma_sd << " ";
  _sd_file << _r_theta_sd << "\n";
}

/**
 * \brief    Reset statistics
 * \details  --
 * \param    void
 * \return   \e void
 */
void Statistics::reset( void )
{
  /*----------------------------------------------- MEAN VALUES */
  
  _dg_mean              = 0.0;
  _dp_mean              = 0.0;
  _wg_mean              = 0.0;
  _wp_mean              = 0.0;
  _EV_mean              = 0.0;
  _EV_contribution_mean = 0.0;
  _EV_dot_product_mean  = 0.0;
  _r_mu_mean            = 0.0;
  _r_sigma_mean         = 0.0;
  _r_theta_mean         = 0.0;
  
  /*----------------------------------------------- STANDARD DEVIATION VALUES */
  
  _dg_sd              = 0.0;
  _dp_sd              = 0.0;
  _wg_sd              = 0.0;
  _wp_sd              = 0.0;
  _EV_sd              = 0.0;
  _EV_contribution_sd = 0.0;
  _EV_dot_product_sd  = 0.0;
  _r_mu_sd            = 0.0;
  _r_sigma_sd         = 0.0;
  _r_theta_sd         = 0.0;
}

/**
 * \brief    Flush statistics files
 * \details  --
 * \param    void
 * \return   \e void
 */
void Statistics::flush( void )
{
  _mean_file.flush();
  _sd_file.flush();
}

/**
 * \brief    Close statistics files
 * \details  --
 * \param    void
 * \return   \e void
 */
void Statistics::close( void )
{
  _mean_file.close();
  _sd_file.close();
}

/*----------------------------
 * PROTECTED METHODS
 *----------------------------*/
