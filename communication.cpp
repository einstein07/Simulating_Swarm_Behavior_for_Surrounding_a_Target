/* 
 * File:   communication.cpp
 * Author: Sindiso Mkhatshwa
 *
 * Created on 10 September 2020, 02:55
 */
#include "communication.h"
//------------------------------------------------------------------------------
//CODE
//------------------------------------------------------------------------------
void mkhsin035::comms::broadcast(robot& robo, double bc_x, double bc_y, double oil_spill_position_x, double oil_spill_position_y)
{
    mkhsin035::pos robot_position;
    mkhsin035::pos *other_robot_positions;
    //radius of the communication circle
    double radius = 1;
    double circleX, circleY;
      
    //find the robot...
    robot_position = robo.get_position();
    double x_d = robot_position.x - robo.farthest_robot_x;
    double y_d = robot_position.y - robo.farthest_robot_y;
    robo.Df = (x_d*x_d) + (y_d * y_d);
    robo.Df = sqrt(robo.Df);
    
    x = robot_position.x - robo.nearest_robot_x;
    y = robot_position.y - robo.nearest_robot_y;
    robo.Dn = (x*x) + (y * y);
    robo.Dn = sqrt(robo.Dn);
    
    //get the poses of other robots in sim
    for(int i=0; i < 4; i++)
    {
        other_robot_positions[i] = robots[i].get_position();
    }
    
    //find actual center relative to simulation.
    circleX = robot_position.x;
    circleY = robot_position.y;
           
    for(int i=0; i<4; i++)
        {
            double x, y, dist; 
            
            //get distance from this robot to robot
            x = circleX - other_robot_positions[i].x;
            y = circleY - other_robot_positions[i].y;
            
            //find euclidean distance from circle center to robot
            dist = (x*x) + (y*y);
            dist = sqrt(dist);
                        
            if(dist < radius)
            {
                if(other_robot_positions[i].x != robot_position.x && other_robot_positions[i].x != robot_position.y)
                {
                    receive(bc_x, bc_y, oil_spill_position_x, oil_spill_position_y);
                }
            }
        }
 
}
      
    void receive(mkhsin035::robot& robo, double& bc_x, double& bc_y, double& oil_spill_position_x, double& oil_spill_position_y)
    {
        mkhsin035::pos robot_position = robo.get_position();
        double x = robot_position.x - bc_x;
        double y = robot_position.y - bc_y;
        double Dj = (x*x) + (y * y);
        if(Dj > robo.Df)
        {
            robo.farthest_robot_x = bc_x;
            robo.farthest_robot_y = bc_y;
        }
        else if(Dj < robo.Dn)
        {
            robo.nearest_robot_x = bc_x;
            robo.nearest_robot_y = bc_y;
        }
        robo.oil_spill_position_x = oil_spill_position_x;
        robo.oil_spill_position_y = oil_spill_position_y;
        robo.bc_x = bc_x;
        robo.bc_y = bc_y;
    }


    void mkhsin035::comms::add(mkhsin035::robot r)
    {
        robots.add(r);
    }