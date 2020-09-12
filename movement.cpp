/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   movement.cpp
 * Author: Sindiso Mkhatshwa
 *
 * Created on 12 September 2020, 22:50
 */

#include "movement.h"

mkhsin035::movement::movement(double circle_diameter, double Dmin):circle_diameter(circle_diameter), min_dist_nearest(Dmin){}

void mkhsin035::movement::move(robot& robo)
{
        
}

      
void mkhsin035::movement::avoid_collisions(robot& robo, double& forward_speed, double& turning_speed)
{
    double *s_p = robo.sonar_proxy->ranges;
    int tspeed = 45;
    //left corner sonar
    if (s_p[2] <= this->min_dist_nearest)
    {
        forward_speed = 0;
        turning_speed = (-1) * tspeed;
    }
    //right corner sonar
    else if(s_p[3] <= this->min_dist_nearest)
    {
        forward_speed = 0;
        turning_speed = tspeed;
    }
    //front sonars
    else if ((s_p[0] <= min_dist_nearest) && (s_p[1] <= min_dist_nearest))
    {
        //we do not want robot to move to far away
        forward_speed = -0.1;
        turning_speed = tspeed;
    }
    else
    {
        return;
    }
}


void mkhsin035::movement::wander(robot& robo, double& forward_speed, double& turning_speed)
{
    int max_speed = 1;
    int max_turning_speed = 90;
    //val between 0-10
    double f_speed = rand()%11;
    f_speed = (f_speed / 10) * max_speed;
    double t_speed = rand()%(2 * max_turning_speed);
    t_speed = t_speed - max_turning_speed;
    forward_speed = f_speed;
    turning_speed = t_speed;
}
