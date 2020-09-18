/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: root07
 *
 * Created on 11 September 2020, 21:48
 */

#include <cstdlib>
#include "robot.h"
#include "communication.h"
#include "movement.h"
#include <unistd.h>
#include <vector>
using namespace std;
using namespace mkhsin035;
/*
 * 
 */
int main(int argc, char** argv) {
    //declare robots
    robot robot1("localhost", 6665, "robot1");
    robot robot2("localhost", 6666, "robot2");
    robot robot3("localhost", 6667, "robot3");
    robot robot4("localhost", 6668, "robot4");
    vector<robot> robots;
    
    //connect robots to server
    robot1.connect_to_server();
    robot2.connect_to_server();
    robot3.connect_to_server();
    robot4.connect_to_server();
    
    //subscribe to devices
    robot1.subscribe_to_devices();
    robot2.subscribe_to_devices();
    robot3.subscribe_to_devices();
    robot4.subscribe_to_devices();
    cout<<"subscribing"<<endl;
    playerc_simulation_t *sim_proxy;
    sim_proxy = playerc_simulation_create(robot1.rob, 0);
	  if (playerc_simulation_subscribe(sim_proxy, PLAYER_OPEN_MODE))
                cout<<"could not subscribe to simulator proxy"<<endl;
    //enable motors
    robot1.enable_motors();
    robot2.enable_motors();
    robot3.enable_motors();
    robot4.enable_motors();
    //request geometries
    robot1.request_geometries();
    robot2.request_geometries();
    robot3.request_geometries();
    robot4.request_geometries();
    
    robots.push_back(robot1);
    robots.push_back(robot2);
    robots.push_back(robot3);
    robots.push_back(robot4);
    
    //useful variables 
    double forward_speed1, turning_speed1,      //robot 1 
            forward_speed2, turning_speed2,     //robot 2
            forward_speed3, turning_speed3,     //robot 3
            forward_speed4, turning_speed4;     //robot 4
    srand(time(NULL));
    
    //Prepare comms
    comms c;
    movement moves(3, 0.5);
    while (true){
        //read from proxies
        robots[0].read_from_proxies();robots[1].read_from_proxies();robots[2].read_from_proxies();robots[3].read_from_proxies();
     
        //robot 1
        cout<<"robot 1"<<endl;
        c.broadcast(robots[0], sim_proxy, robots);
        if (robots[0].blob_proxy->blobs_count == 0 && ((robots[0].farthest_robot_x == INFINITY || robots[0].nearest_robot_x == INFINITY) && robots[0].oil_spill_position_x == INFINITY))
        {
            moves.wander(robots[0], forward_speed1, turning_speed1);
        }
        else
        {
            moves.move(robots[0], sim_proxy, forward_speed1, turning_speed1);
            c.broadcast(robots[0], sim_proxy, robots);
        }
        moves.avoid_collisions(robots[0], sim_proxy, forward_speed1, turning_speed1);
        robots[0].set_motors(forward_speed1, turning_speed1);      
        
        //robot 2
        cout<<"robot 2"<<endl;
        c.broadcast(robots[1], sim_proxy, robots);
        if (robots[1].blob_proxy->blobs_count == 0 && ((robots[1].farthest_robot_x == INFINITY || robots[1].nearest_robot_x == INFINITY) && robots[1].oil_spill_position_x == INFINITY))
        {
            moves.wander(robots[1], forward_speed2, turning_speed2);
        }
        else
        {
            moves.move(robots[1], sim_proxy, forward_speed2, turning_speed2);
            c.broadcast(robots[1], sim_proxy, robots);
        }
        moves.avoid_collisions(robots[1], sim_proxy, forward_speed2, turning_speed2);
        robots[1].set_motors(forward_speed2, turning_speed2);        
        
//        //robot 3
        cout<<"robot 3"<<endl;
        c.broadcast(robots[2], sim_proxy, robots);
        if (robots[2].blob_proxy->blobs_count == 0 && ((robots[2].farthest_robot_x == INFINITY || robots[2].nearest_robot_x == INFINITY) && robots[2].oil_spill_position_x == INFINITY))
        {
            moves.wander(robots[2], forward_speed3, turning_speed3);
        }
        else
        {
            moves.move(robots[2], sim_proxy, forward_speed3, turning_speed3);
            c.broadcast(robots[2], sim_proxy, robots);
        }
        moves.avoid_collisions(robots[2], sim_proxy, forward_speed3, turning_speed3);
        robots[2].set_motors(forward_speed3, turning_speed3);
        
//        //robot 4
        cout<<"robot 4"<<endl;
        c.broadcast(robots[3], sim_proxy, robots);
        if (robots[3].blob_proxy->blobs_count == 0 && ((robots[3].farthest_robot_x == INFINITY || robots[3].nearest_robot_x == INFINITY) && robots[3].oil_spill_position_x == INFINITY))
        {
            moves.wander(robots[3], forward_speed4, turning_speed4);
        }
        else
        {
            moves.move(robots[3], sim_proxy, forward_speed4, turning_speed4);
            c.broadcast(robots[3], sim_proxy, robots);
        }
        moves.avoid_collisions(robots[3], sim_proxy, forward_speed4, turning_speed4);
        robots[3].set_motors(forward_speed4, turning_speed4);

        
        usleep(100000);
    }
    
    
    return 0;
}

