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
    std::cout<<"move"<<std::endl;
    double tspeed = 5;
    int yaw_margin = 5;
    int D_margin = 0.5;
    mkhsin035::pos robo_pos = robo.get_position(sim_proxy);
    if(robo.blob_proxy->blobs_count > 0)
    {
        for (int i = 0; i < robo.blob_proxy->blobs_count; i++)
        {
            if(robo.blob_proxy->blobs[i].color == 0)
            {
                char name[5];
                std::string oil = "oil1";
                strcpy(name, oil.c_str());
                pos oil_pos;
                playerc_simulation_get_pose2d(sim_proxy, name, &oil_pos.x, &oil_pos.y, &oil_pos.yaw);
                robo.oil_spill_position_x = oil_pos.x;
                robo.oil_spill_position_y = oil_pos.y; 
            }
        }
        
    }
    if (robo.oil_spill_position_x != -1000)
    {
        std::cout<<"target coordinates known: ("<<robo.oil_spill_position_x<<","<<robo.oil_spill_position_y<<")"<<std::endl;
        
        double adjacent = robo.oil_spill_position_x - robo_pos.x;
        double opp = robo.oil_spill_position_y - robo_pos.y;
        double desired_yaw = atan(opp/adjacent);
        if((opp < 0 && adjacent < 0) || (adjacent < 0))
        {
            desired_yaw = desired_yaw + DTOR(180);
        }
        std::cout<<"desired yaw to reach target: "<<desired_yaw<<std::endl;
        //std::cout<<"current robo yaw: "<<robo_pos.yaw<<std::endl;
        double Dt = dist(robo_pos.x, robo_pos.y, robo.oil_spill_position_x, robo.oil_spill_position_y);
        if (Dt < (this->circle_diameter - D_margin))
        {
            if(robo_pos.yaw > (desired_yaw + DTOR(yaw_margin)))
            {
                forward_speed = 0;
                turning_speed = (-1) * tspeed;
            }
            else if (robo_pos.yaw < (desired_yaw - DTOR(yaw_margin)))
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
        else if(Dt > (this->circle_diameter + D_margin)) 
        {
          if(robo_pos.yaw > (desired_yaw + DTOR(yaw_margin)))
            {
                forward_speed = 0;
                turning_speed = (-1) * tspeed;
            }
            else if (robo_pos.yaw < (desired_yaw - DTOR(yaw_margin)))
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
        else
        {
         if(robo_pos.yaw > (desired_yaw + DTOR(yaw_margin)))
            {
                forward_speed = 0;
                turning_speed = (-1) * tspeed;
            }
            else if (robo_pos.yaw < (desired_yaw - DTOR(yaw_margin)))
            {
                forward_speed = 0;
                turning_speed = tspeed;
            }
            else
            {
                forward_speed = 0;
                turning_speed = 0;
            }   
        }
    }
    else
    {
        std::cout<<"target unknown"<<std::endl;
        double x_temp = 0.5 * (robo.nearest_robot_x + robo.farthest_robot_x);
        double y_temp = 0.5 * (robo.nearest_robot_y + robo.farthest_robot_y);
        double D_temp = dist(robo_pos.x, robo_pos.y, x_temp, y_temp);
        
        double adjacent = x_temp - robo_pos.x;
        double opp = y_temp - robo_pos.y;
        double desired_yaw = atan(opp/adjacent);
        if((opp < 0 && adjacent < 0) || (adjacent < 0))
        {
            desired_yaw = desired_yaw + DTOR(180);
        }
        
        std::cout<<"desired yaw to reach target: "<<desired_yaw<<std::endl;
        
        if(D_temp < (this->circle_diameter - D_margin))
        {
            if(robo_pos.yaw > (desired_yaw + DTOR(yaw_margin)))
            {
                forward_speed = 0;
                turning_speed = (-1) * tspeed;
            }
            else if (robo_pos.yaw < (desired_yaw - DTOR(yaw_margin)))
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
        else if(D_temp > (this->circle_diameter + D_margin)) 
        {
          if(robo_pos.yaw > (desired_yaw + DTOR(yaw_margin)))
            {
                forward_speed = 0;
                turning_speed = (-1) * tspeed;
            }
            else if (robo_pos.yaw < (desired_yaw - DTOR(yaw_margin)))
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
        else
        {
         if(robo_pos.yaw > (desired_yaw + DTOR(yaw_margin)))
            {
                forward_speed = 0;
                turning_speed = (-1) * tspeed;
            }
            else if (robo_pos.yaw < (desired_yaw - DTOR(yaw_margin)))
            {
                forward_speed = 0;
                turning_speed = tspeed;
            }
            else
            {
                forward_speed = 0;
                turning_speed = 0;
            }   
        }
    }
    
}

      
void mkhsin035::movement::avoid_collisions(robot& robo, playerc_simulation_t *sim_proxy, double& forward_speed, double& turning_speed)
{
        
    double margin = 10;
    mkhsin035::pos robo_pos = robo.get_position(sim_proxy);
        
    double adjacent = robo.nearest_robot_x - robo_pos.x;
    double opp = robo.nearest_robot_y - robo_pos.y;
    double neighbor_bearing = atan(opp/adjacent);
    if((opp < 0 && adjacent < 0) || (adjacent < 0))
    {
        neighbor_bearing = neighbor_bearing + DTOR(180);
    }
    double Dn = dist(robo_pos.x, robo_pos.y, robo.nearest_robot_x, robo.nearest_robot_y);
    //to move away from nearest neighbor we need to turn around and face opp direction to nearest neighbor
    double desired_yaw = (-1) * neighbor_bearing;
    double yaw_margin = 10;
    double tspeed = 60;
    double fspeed = 0.01;
    if (Dn < this->min_dist_nearest)
    {
        std::cout<<"nearest neighbor coordinates: ("<<robo.nearest_robot_x<<","<<robo.nearest_robot_y<<")"<<std::endl;
        std::cout<<"distance to nearest: "<<Dn<<std::endl;
        
        
            if(robo_pos.yaw > (desired_yaw + DTOR(yaw_margin)))
            {
                forward_speed = fspeed;
                turning_speed = (-1) * tspeed;
            }
            else if (robo_pos.yaw < (desired_yaw - DTOR(yaw_margin)))
            {
                forward_speed = fspeed;
                turning_speed = tspeed;
            }
            else
            {
                forward_speed = fspeed;
                turning_speed = 0;
            }
        
    }
    return;
}


void mkhsin035::movement::wander(robot& robo, double& forward_speed, double& turning_speed)
{
    srand(time(NULL));
    std::cout<<"wandering"<<std::endl;
    int max_speed = 1;
    int max_turning_speed = 90;
    //val between 1-10
    double f_speed = rand()%10+1;
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