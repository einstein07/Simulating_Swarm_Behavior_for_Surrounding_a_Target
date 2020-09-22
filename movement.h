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
      movement(/*CONSTRUCTOR*/
                double circle_diameter,
                double Dmin
            );
      void move( /*move to target*/
                robot& robo,                    //robot executing function 
                playerc_simulation_t *sim_proxy,//simulation proxy 
                double& forward_speed,          //translational speed
                double& turning_speed           //rotational speed
            );
      void wander(/*target coordinates unknown*/
                robot& robo,                    //robot executing function
                playerc_simulation_t *sim_proxy,//simulation proxy
                double& forward_speed,          //translational speed
                double& turning_speed           //rotational speed
            );
      void avoid_collisions(/*colision avoidance*/
                robot& robo,                    //robot executing function
                playerc_simulation_t *sim_proxy,//simulation proxy
                double& forward_speed,          //translational speed
                double& turning_speed           //rotational speed
            );  
      static double dist(   //returns distance between 2 points
                double x,   //initial x position
                double y,   //initial y position
                double xf,  //final x position
                double yf   //final y position
            );
  };  
};
#endif /* MOVEMENT_H */

