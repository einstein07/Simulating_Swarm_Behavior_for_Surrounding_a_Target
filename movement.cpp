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
    //std::cout<<"move"<<std::endl;
    //turning speed
    double tspeed = 60;//5;
    //forward speed
    double fspeed = 0.8;
    //allowable error margin for robot yaw
    int yaw_margin = 5;
    //allowable diameter error margin
    int D_margin = 0.1;
    mkhsin035::pos robo_pos = robo.get_position(sim_proxy);
    if(robo.blob_proxy->blobs_count > 0)
    {
        for (int i = 0; i < robo.blob_proxy->blobs_count; i++)
        {
            if(robo.blob_proxy->blobs[i].color != 0)
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
        //std::cout<<"target coordinates known: ("<<robo.oil_spill_position_x<<","<<robo.oil_spill_position_y<<")"<<std::endl;
        
        double adjacent = robo.oil_spill_position_x - robo_pos.x;
        double opp = robo.oil_spill_position_y - robo_pos.y;
        double desired_yaw = atan(opp/adjacent);
        if((opp < 0 && adjacent < 0) || (adjacent < 0))
        {
            desired_yaw = desired_yaw + DTOR(180);
            if(desired_yaw > DTOR(180))
            {
                desired_yaw = desired_yaw - DTOR(360);
            }
        }
        //std::cout<<"desired yaw to reach target: "<<desired_yaw<<std::endl;
        //std::cout<<"current robo yaw: "<<robo_pos.yaw<<std::endl;
        double Dt = dist(robo_pos.x, robo_pos.y, robo.oil_spill_position_x, robo.oil_spill_position_y);
        //robot inside the circle
        if (Dt < ((this->circle_diameter/2) - D_margin))
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
                forward_speed = (-1) * fspeed;//0.8;//-0.1;
                turning_speed = 0;
            }
            
        }
        //Robot outside the circle
        else if(Dt > ((this->circle_diameter/2) + D_margin)) 
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
                forward_speed = fspeed;//0.8;//0.1;
                turning_speed = 0;
            }  
        }
        else//Robot on the circle
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

      
void mkhsin035::movement::avoid_collisions(robot& robo, playerc_simulation_t *sim_proxy, playerc_ranger_t *sonar_proxy, double& forward_speed, double& turning_speed)
{
    double *sp = sonar_proxy->ranges;    
    double margin = 10;
    mkhsin035::pos robo_pos = robo.get_position(sim_proxy);
        
    double adjacent = robo.nearest_robot_x - robo_pos.x;
    double opp = robo.nearest_robot_y - robo_pos.y;
    double neighbor_bearing = atan(opp/adjacent);
    if((opp < 0 && adjacent < 0) || (adjacent < 0))
    {
        neighbor_bearing = neighbor_bearing + DTOR(180);
        
        if(neighbor_bearing > DTOR(180))
            {
                neighbor_bearing = neighbor_bearing - DTOR(360);
            }
    }
    double Dn = dist(robo_pos.x, robo_pos.y, robo.nearest_robot_x, robo.nearest_robot_y);
    //to move away from nearest neighbor we need to turn around and face opp direction to nearest neighbor
    double desired_yaw = 0.0;
    double yaw_margin = 45;
    double tspeed = 90;//10;
    double fspeed = 0.5;
    if (Dn < this->min_dist_nearest)
    {
        std::cout<<"nearest neighbor coordinates: ("<<robo.nearest_robot_x<<","<<robo.nearest_robot_y<<")"<<std::endl;
        std::cout<<"distance to nearest: "<<Dn<<std::endl;
        
        
            if((robo_pos.yaw - neighbor_bearing ) < DTOR(yaw_margin) && (robo_pos.yaw - neighbor_bearing) > (-1* DTOR(yaw_margin)))
            {
                //take a step back
                std::cout<<"step back"<<std::endl;
                forward_speed = (-1) * fspeed;
                turning_speed = 0;
            }
            else if (((robo_pos.yaw - neighbor_bearing) < DTOR(yaw_margin + 180)) && ((robo_pos.yaw - neighbor_bearing) > DTOR(180 - yaw_margin)))
            {
                //take a step forward
                std::cout<<"step forward"<<std::endl;
                forward_speed = fspeed;
                turning_speed = 0;
            }
            else if (((robo_pos.yaw - neighbor_bearing) < DTOR(-180 + yaw_margin)) && ((robo_pos.yaw - neighbor_bearing) > DTOR(-180 - yaw_margin)))
            {
                //take a step forward
                std::cout<<"step forward"<<std::endl;
                forward_speed = fspeed;
                turning_speed = 0;
            }
            else if ( (robo_pos.yaw - neighbor_bearing ) > DTOR(yaw_margin) && ((robo_pos.yaw - neighbor_bearing) < DTOR(180 - yaw_margin)) )
            {
                //turn left
                std::cout<<"turn left!"<<std::endl;
                forward_speed = 0.1;
                turning_speed = tspeed;
            }
            else if ( ((robo_pos.yaw - neighbor_bearing) < (-1* DTOR(yaw_margin))) && ((robo_pos.yaw - neighbor_bearing) > DTOR(-180 + yaw_margin)) )
            {
                //turn left
                std::cout<<"turn right!"<<std::endl;
                forward_speed = 0.1;
                turning_speed = (-1) * tspeed;
            }
            else
            {
                std::cout<<"neeeeed another else statement"<<std::endl;
                forward_speed = 0;
                turning_speed = 0;
            }
        
    }
    else if(sp[2] < min_dist_nearest)
    {
        forward_speed = 0;
        //turn right
        turning_speed = (-1)*tspeed;
        //printf("turning right - wall\n");
        return;
    }
    else if(sp[3] < min_dist_nearest)
    {
        forward_speed = 0;
        //turn left
        turning_speed = tspeed;
        //printf("turning left - wall\n");
        return;
    }
    else if(sp[4] < min_dist_nearest)
    {
        forward_speed = fspeed;
        turning_speed = tspeed;
        printf("moving forward-wall\n");
        return;
    }
    else if( (sp[0] < min_dist_nearest) && \
             (sp[1] < min_dist_nearest))
    {
        //back off a little bit
        forward_speed = (-1) * fspeed;
        turning_speed = tspeed;  
        printf("moving back - wall\n");
        return;
    }
    return;
}


void mkhsin035::movement::wander(robot& robo, playerc_simulation_t *sim_proxy, double& forward_speed, double& turning_speed)
{
    //turning speed
    double tspeed = 60;//5;
    //forward speed
    double fspeed = 0.8;
    //allowable error margin for robot yaw
    int yaw_margin = 5;
    //allowable diameter error margin
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
    if (robo.nearest_robot_x != INFINITY && robo.farthest_robot_x != INFINITY)
    {
        //std::cout<<"target unknown"<<std::endl;
        double x_temp = 0.5 * (robo.nearest_robot_x + robo.farthest_robot_x);
        double y_temp = 0.5 * (robo.nearest_robot_y + robo.farthest_robot_y);
        double D_temp = dist(robo_pos.x, robo_pos.y, x_temp, y_temp);
        
        double adjacent = x_temp - robo_pos.x;
        double opp = y_temp - robo_pos.y;
        double desired_yaw = atan(opp/adjacent);
        if((opp < 0 && adjacent < 0) || (adjacent < 0))
        {
            desired_yaw = desired_yaw + DTOR(180);
            if(desired_yaw > DTOR(180))
            {
                desired_yaw = desired_yaw - DTOR(360);
            }
        }
        
        //std::cout<<"desired yaw to reach target: "<<desired_yaw<<std::endl;
        
        if(D_temp < ((this->circle_diameter/2) - D_margin))
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
                forward_speed = (-1) * fspeed;//0.8;
                turning_speed = 0;
            }
            
        }
        else if(D_temp > ((this->circle_diameter/2) + D_margin)) 
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
                forward_speed = fspeed;//0.1;
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
        srand(time(NULL));
        //std::cout<<"wandering"<<std::endl;
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