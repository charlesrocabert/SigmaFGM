
/**
 * \file      Statistics.cpp
 * \authors   Charles Rocabert, Guillaume Beslon, Carole Knibbe, Samuel Bernard
 * \date      07-06-2016
 * \copyright Copyright (C) 2016-2020 Charles Rocabert, Guillaume Beslon, Carole Knibbe, Samuel Bernard. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     Statistics class definition
 */

/***********************************************************************
 * Copyright (C) 2016-2020
 * Charles Rocabert, Guillaume Beslon, Carole Knibbe, Samuel Bernard
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
  
  _dmu_mean             = 0.0;
  _dz_mean              = 0.0;
  _Wmu_mean             = 0.0;
  _Wz_mean              = 0.0;
  _EV_mean              = 0.0;
  _EV_contribution_mean = 0.0;
  _EV_dot_product_mean  = 0.0;
  _r_mu_mean            = 0.0;
  _r_sigma_mean         = 0.0;
  _r_theta_mean         = 0.0;
  
  /*----------------------------------------------- STANDARD DEVIATION VALUES */
  
  _dmu_sd             = 0.0;
  _dz_sd              = 0.0;
  _Wmu_sd             = 0.0;
  _Wz_sd              = 0.0;
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
  
  _mean_file << "g" << " ";
  _mean_file << "dmu" << " ";
  _mean_file << "dz" << " ";
  _mean_file << "Wmu" << " ";
  _mean_file << "Wz" << " ";
  _mean_file << "EV" << " ";
  _mean_file << "EV_contrib" << " ";
  _mean_file << "EV_dot_product" << " ";
  _mean_file << "r_mu" << " ";
  _mean_file << "r_sigma" << " ";
  _mean_file << "r_theta" << "\n";
  
  /*----------------------------------------------- STANDARD DEVIATION VALUES */
  
  _sd_file << "g" << " ";
  _sd_file << "dmu" << " ";
  _sd_file << "dz" << " ";
  _sd_file << "Wmu" << " ";
  _sd_file << "Wz" << " ";
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
    
    _dmu_mean             += ind->get_dmu();
    _dz_mean              += ind->get_dz();
    _Wmu_mean             += ind->get_Wmu();
    _Wz_mean              += ind->get_Wz();
    _EV_mean              += ind->get_max_Sigma_eigenvalue();
    _EV_contribution_mean += ind->get_max_Sigma_contribution();
    _EV_dot_product_mean  += ind->get_max_dot_product();
    _r_mu_mean            += ind->get_r_mu();
    _r_sigma_mean         += ind->get_r_sigma();
    _r_theta_mean         += ind->get_r_theta();
    
    /*----------------------------------------------- STANDARD DEVIATION VALUES */
    
    _dmu_sd             += ind->get_dmu()*ind->get_dmu();
    _dz_sd              += ind->get_dz()*ind->get_dz();
    _Wmu_sd             += ind->get_Wmu()*ind->get_Wmu();
    _Wz_sd              += ind->get_Wz()*ind->get_Wz();
    _EV_sd              += ind->get_max_Sigma_eigenvalue()*ind->get_max_Sigma_eigenvalue();
    _EV_contribution_sd += ind->get_max_Sigma_contribution()*ind->get_max_Sigma_contribution();
    _EV_dot_product_sd  += ind->get_max_dot_product()*ind->get_max_dot_product();
    _r_mu_sd            += ind->get_r_mu()*ind->get_r_mu();
    _r_sigma_sd         += ind->get_r_sigma()*ind->get_r_sigma();
    _r_theta_sd         += ind->get_r_theta()*ind->get_r_theta();
  }
  
  double N = (double)population->get_population_size();
  
  /*----------------------------------------------- MEAN VALUES */
  
  _dmu_mean             /= N;
  _dz_mean              /= N;
  _Wmu_mean             /= N;
  _Wz_mean              /= N;
  _EV_mean              /= N;
  _EV_contribution_mean /= N;
  _EV_dot_product_mean  /= N;
  _r_mu_mean            /= N;
  _r_sigma_mean         /= N;
  _r_theta_mean         /= N;
  
  /*----------------------------------------------- STANDARD DEVIATION VALUES */
  
  _dmu_sd             /= N;
  _dz_sd              /= N;
  _Wmu_sd             /= N;
  _Wz_sd              /= N;
  _EV_sd              /= N;
  _EV_contribution_sd /= N;
  _EV_dot_product_sd  /= N;
  _r_mu_sd            /= N;
  _r_sigma_sd         /= N;
  _r_theta_sd         -= N;
  _dmu_sd             -= _dmu_mean*_dmu_mean;
  _dz_sd              -= _dz_mean*_dz_mean;
  _Wmu_sd             -= _Wmu_mean*_Wmu_mean;
  _Wz_sd              -= _Wz_mean*_Wz_mean;
  _EV_sd              -= _EV_mean*_EV_mean;
  _EV_contribution_sd -= _EV_contribution_mean*_EV_contribution_mean;
  _EV_dot_product_sd  -= _EV_dot_product_mean*_EV_dot_product_mean;
  _r_mu_sd            -= _r_mu_mean*_r_mu_mean;
  _r_sigma_sd         -= _r_sigma_mean*_r_sigma_mean;
  _r_theta_sd         -= _r_theta_mean*_r_theta_mean;
  if (_dmu_sd < 1e-15)
  {
    _dmu_sd = 0.0;
  }
  else
  {
    _dmu_sd = sqrt(_dmu_sd);
  }
  if (_dz_sd < 1e-15)
  {
    _dz_sd = 0.0;
  }
  else
  {
    _dz_sd = sqrt(_dz_sd);
  }
  if (_Wmu_sd < 1e-15)
  {
    _Wmu_sd = 0.0;
  }
  else
  {
    _Wmu_sd = sqrt(_Wmu_sd);
  }
  if (_Wz_sd < 1e-15)
  {
    _Wz_sd = 0.0;
  }
  else
  {
    _Wz_sd = sqrt(_Wz_sd);
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
 * \param    int generation
 * \return   \e void
 */
void Statistics::write_statistics( int generation )
{
  /*----------------------------------------------- MEAN VALUES */
  
  _mean_file << generation << " ";
  _mean_file << _dmu_mean << " ";
  _mean_file << _dz_mean << " ";
  _mean_file << _Wmu_mean << " ";
  _mean_file << _Wz_mean << " ";
  _mean_file << _EV_mean << " ";
  _mean_file << _EV_contribution_mean << " ";
  _mean_file << _EV_dot_product_mean << " ";
  _mean_file << _r_mu_mean << " ";
  _mean_file << _r_sigma_mean << " ";
  _mean_file << _r_theta_mean << "\n";
  
  /*----------------------------------------------- STANDARD DEVIATION VALUES */
  
  _sd_file << generation << " ";
  _sd_file << _dmu_sd << " ";
  _sd_file << _dz_sd << " ";
  _sd_file << _Wmu_sd << " ";
  _sd_file << _Wz_sd << " ";
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
  
  _dmu_mean             = 0.0;
  _dz_mean              = 0.0;
  _Wmu_mean             = 0.0;
  _Wz_mean              = 0.0;
  _EV_mean              = 0.0;
  _EV_contribution_mean = 0.0;
  _EV_dot_product_mean  = 0.0;
  _r_mu_mean            = 0.0;
  _r_sigma_mean         = 0.0;
  _r_theta_mean         = 0.0;
  
  /*----------------------------------------------- STANDARD DEVIATION VALUES */
  
  _dmu_sd             = 0.0;
  _dz_sd              = 0.0;
  _Wmu_sd             = 0.0;
  _Wz_sd              = 0.0;
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
