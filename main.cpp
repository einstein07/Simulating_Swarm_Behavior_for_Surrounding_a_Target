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
                cout<<"could not be done"<<endl;
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
    
    //useful variables 
    double forward_speed, turning_speed, forward_speed2, turning_speed2,
            forward_speed3, turning_speed3, forward_speed4, turning_speed4;
    srand(time(NULL));
    
    //Prepare comms
    comms c;
    movement moves(2, 0.5);
    c.add(robot1); c.add(robot2); c.add(robot3); c.add(robot4);
    while (true){
        //read from proxies
        robot1.read_from_proxies();robot2.read_from_proxies();robot3.read_from_proxies();robot4.read_from_proxies();
        //robot 1
        c.broadcast(robot1, sim_proxy);
        if (robot1.blob_proxy->blobs_count == 0 && ((robot1.farthest_robot_x == -1000 || robot1.nearest_robot_x == -1000) && robot1.oil_spill_position_x == -1000))
        {
            moves.wander(robot1, forward_speed, turning_speed);
            cout<<"robot 1: wandering"<<endl;
        }
        else
        {
            moves.move(robot1, sim_proxy, forward_speed, turning_speed);
            c.broadcast(robot1, sim_proxy);
            cout<<"robot 1: target spotted!"<<endl;
        }
        moves.avoid_collisions(robot1, forward_speed, turning_speed);
        robot1.set_motors(forward_speed, turning_speed);
        
        //robot 2
        c.broadcast(robot2, sim_proxy);
        if (robot2.blob_proxy->blobs_count == 0 && ((robot2.farthest_robot_x == -1000 || robot2.nearest_robot_x == -1000) && robot2.oil_spill_position_x == -1000))
        {
            moves.wander(robot2, forward_speed2, turning_speed2);
            cout<<"robot 2: wandering"<<endl;
        }
        else
        {
            moves.move(robot2, sim_proxy, forward_speed2, turning_speed2);
            c.broadcast(robot2, sim_proxy);
            cout<<"robot 2: target spotted!"<<endl;
        }
        moves.avoid_collisions(robot2, forward_speed2, turning_speed2);
        robot2.set_motors(forward_speed2, turning_speed2);
        
        //robot 3
        c.broadcast(robot3, sim_proxy);
        if(robot3.blob_proxy->blobs_count == 0 && ((robot3.farthest_robot_x == -1000 || robot3.nearest_robot_x == -1000) && robot3.oil_spill_position_x == -1000))
        {
            moves.wander(robot3, forward_speed3, turning_speed3);
            cout<<"robot 3: wandering"<<endl;
        }
        else
        {
            moves.move(robot3, sim_proxy, forward_speed3, turning_speed3);
            c.broadcast(robot3, sim_proxy);
            cout<<"robot 3: target spotted!"<<endl;
        }
        moves.avoid_collisions(robot3, forward_speed3, turning_speed3);
        robot3.set_motors(forward_speed3, turning_speed3);
        
        //robot 4
        c.broadcast(robot4, sim_proxy);
        if(robot4.blob_proxy->blobs_count == 0 && ((robot4.farthest_robot_x == -1000 || robot4.nearest_robot_x == -1000) && robot4.oil_spill_position_x == -1000))
        {
            moves.wander(robot4, forward_speed4, turning_speed4);
        }
        else
        {
            moves.move(robot4, sim_proxy, forward_speed4, turning_speed4);
            c.broadcast(robot4, sim_proxy);
        }
        moves.avoid_collisions(robot4, forward_speed4, turning_speed4);
        robot4.set_motors(forward_speed4, turning_speed4);
        
        usleep(1000000);
    }
    
    
    return 0;
}

