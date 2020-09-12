/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   movement.h
 * Author: Sindiso Mkhatshwa
 *
 * Created on 12 September 2020, 22:45
 */

#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "robot.h"

namespace mkhsin035{
  class movement{
  private:
      double circle_diameter;
      double min_dist_nearest;
  public:
      movement(double circle_diameter, double Dmin);
      void move(robot& robo);
      void wander(robot& robo, double& forward_speed, double& turning_speed);
      void avoid_collisions(robot& robo, double& forward_speed, double& turning_speed);
  };  
};


#endif /* MOVEMENT_H */
