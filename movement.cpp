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

void mkhsin035::movement::move(robot& robo, playerc_simulation_t *sim_proxy, double& forward_speed, double& turning_speed)
{
    double tspeed = 5;
    int margin = 5;
    mkhsin035::pos robo_pos = robo.get_position(sim_proxy);
    if(robo.blob_proxy->blobs_count > 0)
    {
        robo.oil_spill_position_x = robo.blob_proxy->blobs[0].x;
        robo.oil_spill_position_y = robo.blob_proxy->blobs[0].y;
    }
    if (robo.oil_spill_position_x != -1000)
    {
        
        double adjacent = robo.oil_spill_position_x - robo_pos.x;
        double opp = robo.oil_spill_position_y - robo_pos.y;
        double desired_yaw = tan(opp/adjacent);
        
        double Dt = dist(robo_pos.x, robo_pos.y, robo.oil_spill_position_x, robo.oil_spill_position_y);
        if (Dt <= this->circle_diameter)
        {
            if(robo_pos.yaw > DTOR(desired_yaw + margin))
            {
                forward_speed = 0;
                turning_speed = (-1) * tspeed;
            }
            else if (robo_pos.yaw < DTOR(desired_yaw - margin))
            {
                forward_speed = 0;
                turning_speed = tspeed;
            }
            else
            {
                forward_speed = -0.1;
                turning_speed = 0;
            }
            
        }
        else 
        {
          if(robo_pos.yaw > DTOR(desired_yaw + margin))
            {
                forward_speed = 0;
                turning_speed = (-1) * tspeed;
            }
            else if (robo_pos.yaw < DTOR(desired_yaw - margin))
            {
                forward_speed = 0;
                turning_speed = tspeed;
            }
            else
            {
                forward_speed = 0.1;
                turning_speed = 0;
            }  
        }
    }
    else
    {
        double x_temp = 0.5 * (robo.nearest_robot_x + robo.farthest_robot_x);
        double y_temp = 0.5 * (robo.nearest_robot_y + robo.farthest_robot_y);
        double D_temp = dist(robo_pos.x, robo_pos.y, x_temp, y_temp);
        
        double adjacent = x_temp - robo_pos.x;
        double opp = y_temp - robo_pos.y;
        double desired_yaw = tan(opp/adjacent);
        
        if(D_temp <= this->circle_diameter)
        {
            if(robo_pos.yaw > DTOR(desired_yaw + margin))
            {
                forward_speed = 0;
                turning_speed = (-1) * tspeed;
            }
            else if (robo_pos.yaw < DTOR(desired_yaw - margin))
            {
                forward_speed = 0;
                turning_speed = tspeed;
            }
            else
            {
                forward_speed = -0.1;
                turning_speed = 0;
            }
        }
        else 
        {
          if(robo_pos.yaw > DTOR(desired_yaw + margin))
            {
                forward_speed = 0;
                turning_speed = (-1) * tspeed;
            }
            else if (robo_pos.yaw < DTOR(desired_yaw - margin))
            {
                forward_speed = 0;
                turning_speed = tspeed;
            }
            else
            {
                forward_speed = 0.1;
                turning_speed = 0;
            }  
        }
    }
    
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

double mkhsin035::movement::dist(double xi, double yi, double xf, double yf)
{
    double x, y, dist; 
            
    //get distance from this robot to robot
    x = xf - xi;
    y = yf - yi;

    //find euclidean distance from circle center to robot
    dist = (x * x) + (y * y);
    dist = sqrt(dist);
    return dist;
}