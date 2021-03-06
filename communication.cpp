/* 
 * File:   communication.cpp
 * Author: Sindiso Mkhatshwa
 *
 * Created on 10 September 2020, 02:55
 */
#include <vector>

#include "communication.h"
#include "movement.h"
//------------------------------------------------------------------------------
//CODE
//------------------------------------------------------------------------------
      
    mkhsin035::comms::comms(double range):range(range){}
    void mkhsin035::comms::receive(mkhsin035::robot& robo, double& bc_x, double& bc_y, double& oil_spill_position_x, double& oil_spill_position_y)
    {
        mkhsin035::pos robot_position = robo.current_position;

        double Dj = movement::dist(robot_position.x, robot_position.y, bc_x, bc_y);
        if ((robot_position.x < bc_x + 0.15 && robot_position.x > bc_x - 0.15) && (robot_position.y < bc_y + 0.15 && robot_position.y > bc_y - 0.15))
        {
            return;
        }
        else
        {
            if(robo.Df == INFINITY|| robo.Dn == INFINITY)
            {
                robo.farthest_robot_x = bc_x;
                robo.farthest_robot_y = bc_y;
                robo.nearest_robot_x = bc_x;
                robo.nearest_robot_y = bc_y;
            }
            else
            {
                if(Dj > robo.Df)
                {
                    //std::cout<<"changed farthest"<<std::endl;
                    robo.farthest_robot_x = bc_x;
                    robo.farthest_robot_y = bc_y;
                }
                else if(Dj < robo.Dn)
                {
                    //std::cout<<"changed nearest"<<std::endl;
                    robo.nearest_robot_x = bc_x;
                    robo.nearest_robot_y = bc_y;
                }
                robo.oil_spill_position_x = oil_spill_position_x;
                robo.oil_spill_position_y = oil_spill_position_y;
                robo.bc_x = bc_x;
                robo.bc_y = bc_y;
                robo.status = 1;
            }
        }
                
    }
void mkhsin035::comms::broadcast(robot& robo, std::vector<mkhsin035::robot> &robots)
{
    //std::cout<<"broadcast:start"<<std::endl;
    mkhsin035::pos robot_position;
    mkhsin035::pos other_robot_positions[robots.size()];
    double circleX, circleY;
      
    //find the robot...
    robot_position = robo.current_position;
    //Evaluate distance from the farthest known robot
    robo.Df = robo.farthest_robot_x == INFINITY ? INFINITY : movement::dist(robot_position.x, robot_position.y, robo.farthest_robot_x, robo.farthest_robot_y);
    //Evaluate distance from the nearest known robot
    robo.Dn = robo.nearest_robot_x == INFINITY ? INFINITY : movement::dist(robot_position.x, robot_position.y, robo.nearest_robot_x, robo.nearest_robot_y);
    if (robo.bc_x == INFINITY)
    {
        robo.status = 0; //broadcast own coordinates
    }
    
    if(!robo.status)
    {
        robo.bc_x = robot_position.x;
        robo.bc_y = robot_position.y;
    }
    
    //get the poses of other robots in sim
    for(int i=0; i < robots.size(); i++)
    {
        other_robot_positions[i] = robots[i].current_position;
    }
    
    //find actual center relative to simulation.
    circleX = robot_position.x;
    circleY = robot_position.y;
           
    for(int i=0; i<robots.size(); i++)
        {
            double dist; 
            dist = movement::dist(circleX, circleY, other_robot_positions[i].x, other_robot_positions[i].y);
                        
            // 
            if(dist > 0 && dist < range && !robo.is_self(robots[i]))
            {
                comms::receive(robots[i], robo.bc_x, robo.bc_y, robo.oil_spill_position_x, robo.oil_spill_position_y);
                robo.status = 0;
            }
        }
 
}
