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
void mkhsin035::comms::broadcast(item_t *itemList, int listLength, playerc_simulation_t *sim, char *robot_name)
{
    /*
    This function works by creating a search area just
    in front of the robot's teeth. The search circle is a
    fixed distance in front of the robot, and has a 
    fixed radius.
    This function finds objects within this search circle
    and then deletes the closest one.
    */
	
    //radius of the communication circle
    double radius = 1;
      
    //The distance from the centre of the robot to 
    //the centre of the search circle
      double distBotToCircle = 0;
      double robotX, robotY, robotYaw;
      double circleX, circleY;
      
    //find the robot...
    playerc_simulation_get_pose2d(sim,robot_name, &robotX, &robotY, &robotYaw);
    
    //get the poses of other robots in sim
    for(int i=0; i < 4; i++)
    {
          char robot_str[] = "robot%d";
          sprintf(this->robots[i].name, robots_str, i+1);
          double dummy;  //dummy variable, don't need yaws.
          playerc_simulation_get_pose2d(simProxy,itemList[i].name, \
                &(itemList[i].x), &(itemList[i].y), &dummy);
    }
    
    //find actual centre relative to simulation.
    circleX = robotX;
    circleY = robotY;
           
      /* to find which items are within this circle we
      find their Euclidian distance to the circle centre.
      Find the closest one and if it's distance is smaller than
      the circle radius then return its index */
      
      double smallestDist = 1000000;
      int closestItem = 0; 
      int i;
      
      for(i=0; i<listLength; i++)
      {
            double x, y, dist; 
            
            // get manhattan distance from circle centre to item
            x = circleX - itemList[i].x;
            y = circleY - itemList[i].y;
            
            //find euclidian distance from circle centre to item
            dist = (x*x) + (y*y);
            dist = sqrt(dist);
                        
            if(dist < smallestDist)
            {
                  smallestDist = dist;
                  closestItem = i;
            }
      }
 
      if(smallestDist > (radius + distBotToCircle))
      {
      	printf("no objects were close enough, false alarm!\n");
      	return -1;
      }   
        
      return closestItem;
}