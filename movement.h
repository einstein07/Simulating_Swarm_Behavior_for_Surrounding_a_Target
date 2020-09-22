/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   movement.h
 * Author: Sindiso Mkhatshwa
 * Created on 12 September 2020, 22:45
 */

#ifndef MOVEMENT_H
#define MOVEMENT_H
#include "robot.h"
namespace mkhsin035{
  class movement{
  private:
      double circle_diameter;   //diameter of circle being formed
      double min_dist_nearest;  //minimum allowable distance between robots 
  public:
      movement(
                double circle_diameter,
                double Dmin
            );
      void move(
                robot& robo,                    //robot executing function 
                playerc_simulation_t *sim_proxy,//simulation proxy 
                double& forward_speed,          //translational speed
                double& turning_speed           //rotational speed
            );
      void wander(
                robot& robo,                    //robot executing function
                playerc_simulation_t *sim_proxy,//simulation proxy
                double& forward_speed,          //translational speed
                double& turning_speed           //rotational speed
            );
      void avoid_collisions(
                robot& robo,
                playerc_simulation_t *sim_proxy,
                double& forward_speed,
                double& turning_speed
            );  
      static double dist(   //returns distance between 2 points
                double x,   //initial x coordinate
                double y,   //initial y coordinate
                double xf,  //final x coordinate
                double yf   //final y coordinate
            );
  };  
};
#endif /* MOVEMENT_H */

