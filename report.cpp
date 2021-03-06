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
#include "tests.h"
#include <unistd.h>
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
       
    //connect robots to server
    robot1.connect_to_server();
    robot2.connect_to_server();
    robot3.connect_to_server();
  
    //subscribe to devices
    robot1.subscribe_to_devices();
    robot2.subscribe_to_devices();
    robot3.subscribe_to_devices()

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
    robot5.enable_motors();
    robot6.enable_motors();
//    robot7.enable_motors();
//    robot8.enable_motors();
//    //scaling up_batch 2
//    robot9.enable_motors();
//    robot10.enable_motors();
//    robot11.enable_motors();
//    robot12.enable_motors();
//    //scaling up_batch 3
//    robot13.enable_motors();
//    robot14.enable_motors();
//    robot15.enable_motors();
//    robot16.enable_motors();
//    
    //request geometries
    robot1.request_geometries();
    robot2.request_geometries();
    robot3.request_geometries();
    robot4.request_geometries();
    robot5.request_geometries();
    robot6.request_geometries();
//    robot7.request_geometries();
//    robot8.request_geometries();
//    //scaling up_batch 2
//    robot9.request_geometries();
//    robot10.request_geometries();
//    robot11.request_geometries();
//    robot12.request_geometries();
//    //scaling up_batch 3
//    robot13.request_geometries();
//    robot14.request_geometries();
//    robot15.request_geometries();
//    robot16.request_geometries();
//    
    //push back robots into vector of all swarm robots
    robots.push_back(robot1);
    robots.push_back(robot2);
    robots.push_back(robot3);
    robots.push_back(robot4);
    robots.push_back(robot5);
    robots.push_back(robot6);
//    robots.push_back(robot7);
//    robots.push_back(robot8);
//    //scaling up batch 2
//    robots.push_back(robot9);
//    robots.push_back(robot10);
//    robots.push_back(robot11);
//    robots.push_back(robot12);
//    //scaling up batch 3
//    robots.push_back(robot13);
//    robots.push_back(robot14);
//    robots.push_back(robot15);
//    robots.push_back(robot16);
//    
    //useful variables 
    double forward_speed1, turning_speed1;      //robot 1 
    double forward_speed2, turning_speed2;     //robot 2
    double forward_speed3, turning_speed3;     //robot 3
    double forward_speed4, turning_speed4;     //robot 4
    double forward_speed5, turning_speed5;     //robot 5 
    double forward_speed6, turning_speed6;     //robot 6
//            forward_speed7, turning_speed7,     //robot 7
//            forward_speed8, turning_speed8,     //robot 8
//            //scaling up_batch 2
//            forward_speed9, turning_speed9,     //robot 9 
//            forward_speed10, turning_speed10,   //robot 10
//            forward_speed11, turning_speed11,   //robot 11
//            forward_speed12, turning_speed12,   //robot 12
//            //scaling up_batch 3
//            forward_speed13, turning_speed13,     //robot 13 
//            forward_speed14, turning_speed14,   //robot 14
//            forward_speed15, turning_speed15,   //robot 15
//            forward_speed16, turning_speed16,   //robot 16
    int counter = 0;
    double comms_range = 9;
    double circle_diameter = 15;
    double min_distance = 0.8;
        
    //srand((unsigned)time(0));
    //double target_x = rand()%25 + (-12);
    //double target_y = rand()%25 + (-12);
    //cout<<"x = "<<target_x<<" y = "<<target_y<<endl;
    //robots[0].oil_spill_position_x = target_x;
    //robots[0].oil_spill_position_y = target_y;
    //robots[1].oil_spill_position_x = target_x;
    //robots[1].oil_spill_position_y = target_y;
//    robots[2].oil_spill_position_x = target_x;
//    robots[2].oil_spill_position_y = target_y;
    comms c(comms_range);
    movement moves(circle_diameter, min_distance);
    tests test_performance("results.txt");
    for (int i = 0; i < 1000; i++){
        //read from proxies
        robots[0].read_from_proxies();
	robots[1].read_from_proxies();
	robots[2].read_from_proxies();
	robots[3].read_from_proxies();
        //scaling up_batch 1
        robots[4].read_from_proxies();
	robots[5].read_from_proxies();
	//robots[6].read_from_proxies();robots[7].read_from_proxies();
//        //scaling up_batch 2
//        robots[8].read_from_proxies();robots[9].read_from_proxies();robots[10].read_from_proxies();robots[11].read_from_proxies();
//        //scaling up_batch 3
//        robots[12].read_from_proxies();robots[13].read_from_proxies();robots[14].read_from_proxies();robots[15].read_from_proxies();
//        
        
        //robot 1
        //cout<<"robot 1"<<endl;
        c.broadcast(robots[0], sim_proxy, robots);
        if (robots[0].blob_proxy->blobs_count == 0 && (robots[0].oil_spill_position_x == -1000))
        {
            moves.wander(robots[0], sim_proxy, forward_speed1, turning_speed1);
        }
        else
        {
            moves.move(robots[0], sim_proxy, forward_speed1, turning_speed1);
            c.broadcast(robots[0], sim_proxy, robots);
        }
        moves.avoid_collisions(robots[0], sim_proxy, robots[0].sonar_proxy, forward_speed1, turning_speed1);
        robots[0].set_motors(forward_speed1, turning_speed1);      
        usleep(10);
        forward_speed1 = 0; turning_speed1 = 0;
        robots[0].set_motors(forward_speed1, turning_speed1);
        //robot 2
        //cout<<"robot 2"<<endl;
        c.broadcast(robots[1], sim_proxy, robots);
        if (robots[1].blob_proxy->blobs_count == 0 && (robots[1].oil_spill_position_x == -1000))
        {
            moves.wander(robots[1], sim_proxy, forward_speed2, turning_speed2);
        }
        else
        {
            moves.move(robots[1], sim_proxy, forward_speed2, turning_speed2);
            c.broadcast(robots[1], sim_proxy, robots);
        }
        moves.avoid_collisions(robots[1], sim_proxy, robots[1].sonar_proxy, forward_speed2, turning_speed2);
        robots[1].set_motors(forward_speed2, turning_speed2);        
        usleep(10);
        forward_speed2 = 0; turning_speed2 = 0;
        robots[1].set_motors(forward_speed2, turning_speed2);
        //robot 3
        //cout<<"robot 3"<<endl;
        c.broadcast(robots[2], sim_proxy, robots);
        if (robots[2].blob_proxy->blobs_count == 0 && (robots[2].oil_spill_position_x == -1000))
        {
            moves.wander(robots[2], sim_proxy, forward_speed3, turning_speed3);
        }
        else
        {
            moves.move(robots[2], sim_proxy, forward_speed3, turning_speed3);
            c.broadcast(robots[2], sim_proxy, robots);
        }
        moves.avoid_collisions(robots[2], sim_proxy, robots[2].sonar_proxy, forward_speed3, turning_speed3);
        robots[2].set_motors(forward_speed3, turning_speed3);
        usleep(10);
        forward_speed3 = 0; turning_speed3 = 0;
        robots[2].set_motors(forward_speed3, turning_speed3);
	if (i < 499){
        //robot 4
        
        c.broadcast(robots[3], sim_proxy, robots);
        if (robots[3].blob_proxy->blobs_count == 0 && (robots[3].oil_spill_position_x == -1000))
        {
            moves.wander(robots[3], sim_proxy, forward_speed4, turning_speed4);
        }
        else
        {
            moves.move(robots[3], sim_proxy, forward_speed4, turning_speed4);
            c.broadcast(robots[3], sim_proxy, robots);
        }
        moves.avoid_collisions(robots[3], sim_proxy, robots[3].sonar_proxy, forward_speed4, turning_speed4);
        robots[3].set_motors(forward_speed4, turning_speed4);
        usleep(10);
        forward_speed4 = 0; turning_speed4 = 0;
        robots[3].set_motors(forward_speed4, turning_speed4);
        
        //robot 5
        //cout<<"robot 4"<<endl;
        c.broadcast(robots[4], sim_proxy, robots);
        if (robots[4].blob_proxy->blobs_count == 0 && (robots[4].oil_spill_position_x == -1000))
        {
            moves.wander(robots[4], sim_proxy, forward_speed5, turning_speed5);
        }
        else
        {
            moves.move(robots[4], sim_proxy, forward_speed5, turning_speed5);
            c.broadcast(robots[4], sim_proxy, robots);
        }
        moves.avoid_collisions(robots[4], sim_proxy, robots[4].sonar_proxy, forward_speed5, turning_speed5);
        robots[4].set_motors(forward_speed5, turning_speed5);
        usleep(10);
        forward_speed5 = 0; turning_speed5 = 0;
        robots[4].set_motors(forward_speed5, turning_speed5);       
        //robot 6
        //cout<<"robot 6"<<endl;
        c.broadcast(robots[5], sim_proxy, robots);
        if (robots[5].blob_proxy->blobs_count == 0 && (robots[5].oil_spill_position_x == -1000))
        {
            moves.wander(robots[5], sim_proxy, forward_speed6, turning_speed6);
        }
        else
        {
            moves.move(robots[5], sim_proxy, forward_speed6, turning_speed6);
            c.broadcast(robots[5], sim_proxy, robots);
        }
        moves.avoid_collisions(robots[5], sim_proxy, robots[5].sonar_proxy, forward_speed6, turning_speed6);
        robots[5].set_motors(forward_speed6, turning_speed6);
        usleep(10);
        forward_speed6 = 0; turning_speed6 = 0;
        robots[5].set_motors(forward_speed6, turning_speed6);
        }
	else if (i == 499){
		//robots[3].shutdown();
		//robots[4].shutdown();
		//robots[5].shutdown();
		robots.pop_back();
		robots.pop_back();
		robots.pop_back();
		cout<<"Retiring 3 robots"<<endl;
	}
        //robot 7
//        //cout<<"robot 7"<<endl;
//        c.broadcast(robots[6], sim_proxy, robots);
//        if (robots[6].blob_proxy->blobs_count == 0 && (robots[6].oil_spill_position_x == -1000))
//        {
//            moves.wander(robots[6], sim_proxy, forward_speed7, turning_speed7);
//        }
//        else
//        {
//            moves.move(robots[6], sim_proxy, forward_speed7, turning_speed7);
//            c.broadcast(robots[6], sim_proxy, robots);
//        }
//        moves.avoid_collisions(robots[6], sim_proxy, forward_speed7, turning_speed7);
//        robots[6].set_motors(forward_speed7, turning_speed7);
//        usleep(10);
//        forward_speed7 = 0; turning_speed7 = 0;
//        robots[6].set_motors(forward_speed7, turning_speed7);
//        
//        //robot 8
//        //cout<<"robot 8"<<endl;
//        c.broadcast(robots[7], sim_proxy, robots);
//        if (robots[7].blob_proxy->blobs_count == 0 && (robots[7].oil_spill_position_x == -1000))
//        {
//            moves.wander(robots[7], sim_proxy, forward_speed8, turning_speed8);
//        }
//        else
//        {
//            moves.move(robots[7], sim_proxy, forward_speed8, turning_speed8);
//            c.broadcast(robots[7], sim_proxy, robots);
//        }
//        moves.avoid_collisions(robots[7], sim_proxy, forward_speed8, turning_speed8);
//        robots[7].set_motors(forward_speed8, turning_speed8);
//        usleep(10);
//        forward_speed8 = 0; turning_speed8 = 0;
//        robots[7].set_motors(forward_speed8, turning_speed8);
//        
//        //----------------------------------------------------------------------
//        //scaling up_batch 2
//        //----------------------------------------------------------------------
//        //robot 9
//        cout<<"robot 9"<<endl;
//        c.broadcast(robots[8], sim_proxy, robots);
//        if (robots[8].blob_proxy->blobs_count == 0 && ((robots[8].farthest_robot_x == INFINITY || robots[8].nearest_robot_x == INFINITY) && robots[8].oil_spill_position_x == INFINITY))
//        {
//            moves.wander(robots[8], forward_speed9, turning_speed9);
//        }
//        else
//        {
//            moves.move(robots[8], sim_proxy, forward_speed9, turning_speed9);
//            c.broadcast(robots[8], sim_proxy, robots);
//        }
//        moves.avoid_collisions(robots[8], sim_proxy, forward_speed9, turning_speed9);
//        robots[8].set_motors(forward_speed9, turning_speed9);      
//        
//        //robot10
//        cout<<"robot 10"<<endl;
//        c.broadcast(robots[9], sim_proxy, robots);
//        if (robots[9].blob_proxy->blobs_count == 0 && ((robots[9].farthest_robot_x == INFINITY || robots[9].nearest_robot_x == INFINITY) && robots[9].oil_spill_position_x == INFINITY))
//        {
//            moves.wander(robots[9], forward_speed10, turning_speed10);
//        }
//        else
//        {
//            moves.move(robots[9], sim_proxy, forward_speed10, turning_speed10);
//            c.broadcast(robots[9], sim_proxy, robots);
//        }
//        moves.avoid_collisions(robots[9], sim_proxy, forward_speed10, turning_speed10);
//        robots[9].set_motors(forward_speed10, turning_speed10);        
//        
//        //robot 11
//        cout<<"robot 11"<<endl;
//        c.broadcast(robots[10], sim_proxy, robots);
//        if (robots[10].blob_proxy->blobs_count == 0 && ((robots[10].farthest_robot_x == INFINITY || robots[10].nearest_robot_x == INFINITY) && robots[10].oil_spill_position_x == INFINITY))
//        {
//            moves.wander(robots[10], forward_speed11, turning_speed11);
//        }
//        else
//        {
//            moves.move(robots[10], sim_proxy, forward_speed11, turning_speed11);
//            c.broadcast(robots[10], sim_proxy, robots);
//        }
//        moves.avoid_collisions(robots[10], sim_proxy, forward_speed11, turning_speed11);
//        robots[10].set_motors(forward_speed11, turning_speed11);
//        
//        //robot 12
//        cout<<"robot 12"<<endl;
//        c.broadcast(robots[11], sim_proxy, robots);
//        if (robots[11].blob_proxy->blobs_count == 0 && ((robots[11].farthest_robot_x == INFINITY || robots[11].nearest_robot_x == INFINITY) && robots[11].oil_spill_position_x == INFINITY))
//        {
//            moves.wander(robots[11], forward_speed12, turning_speed12);
//        }
//        else
//        {
//            moves.move(robots[11], sim_proxy, forward_speed12, turning_speed12);
//            c.broadcast(robots[11], sim_proxy, robots);
//        }
//        moves.avoid_collisions(robots[11], sim_proxy, forward_speed12, turning_speed12);
//        robots[11].set_motors(forward_speed12, turning_speed12);
//        
//        //----------------------------------------------------------------------
//        //scaling up_batch 3
//        //----------------------------------------------------------------------
//        //robot 13
//        cout<<"robot 13"<<endl;
//        c.broadcast(robots[12], sim_proxy, robots);
//        if (robots[12].blob_proxy->blobs_count == 0 && ((robots[12].farthest_robot_x == INFINITY || robots[12].nearest_robot_x == INFINITY) && robots[12].oil_spill_position_x == INFINITY))
//        {
//            moves.wander(robots[12], forward_speed13, turning_speed13);
//        }
//        else
//        {
//            moves.move(robots[12], sim_proxy, forward_speed13, turning_speed13);
//            c.broadcast(robots[12], sim_proxy, robots);
//        }
//        moves.avoid_collisions(robots[12], sim_proxy, forward_speed13, turning_speed13);
//        robots[12].set_motors(forward_speed13, turning_speed13);      
//        
//        //robot14
//        cout<<"robot 14"<<endl;
//        c.broadcast(robots[13], sim_proxy, robots);
//        if (robots[13].blob_proxy->blobs_count == 0 && ((robots[13].farthest_robot_x == INFINITY || robots[13].nearest_robot_x == INFINITY) && robots[13].oil_spill_position_x == INFINITY))
//        {
//            moves.wander(robots[13], forward_speed14, turning_speed14);
//        }
//        else
//        {
//            moves.move(robots[13], sim_proxy, forward_speed14, turning_speed14);
//            c.broadcast(robots[13], sim_proxy, robots);
//        }
//        moves.avoid_collisions(robots[13], sim_proxy, forward_speed14, turning_speed14);
//        robots[13].set_motors(forward_speed14, turning_speed14);        
//        
//        //robot 15
//        cout<<"robot 15"<<endl;
//        c.broadcast(robots[14], sim_proxy, robots);
//        if (robots[14].blob_proxy->blobs_count == 0 && ((robots[14].farthest_robot_x == INFINITY || robots[14].nearest_robot_x == INFINITY) && robots[14].oil_spill_position_x == INFINITY))
//        {
//            moves.wander(robots[14], forward_speed15, turning_speed15);
//        }
//        else
//        {
//            moves.move(robots[14], sim_proxy, forward_speed15, turning_speed15);
//            c.broadcast(robots[14], sim_proxy, robots);
//        }
//        moves.avoid_collisions(robots[14], sim_proxy, forward_speed15, turning_speed15);
//        robots[14].set_motors(forward_speed15, turning_speed15);
//        
//        //robot 16
//        cout<<"robot 16"<<endl;
//        c.broadcast(robots[15], sim_proxy, robots);
//        if (robots[15].blob_proxy->blobs_count == 0 && ((robots[15].farthest_robot_x == INFINITY || robots[15].nearest_robot_x == INFINITY) && robots[15].oil_spill_position_x == INFINITY))
//        {
//            moves.wander(robots[15], forward_speed16, turning_speed16);
//        }
//        else
//        {
//            moves.move(robots[15], sim_proxy, forward_speed16, turning_speed16);
//            c.broadcast(robots[15], sim_proxy, robots);
//        }
//        moves.avoid_collisions(robots[15], sim_proxy, forward_speed16, turning_speed16);
//        robots[15].set_motors(forward_speed16, turning_speed16);
//        
        counter++;
        if(counter == 10)
        {
            cout<<"recording..."<<endl;
            test_performance.record(circle_diameter, sim_proxy, robots);
            robots[0].refresh();
            robots[1].refresh();
            robots[2].refresh();
	    if(i < 499){
	    robots[3].refresh();
            robots[4].refresh();
            robots[5].refresh();
	    }
            counter = 0;
        }
        
        //usleep(10000);
    }
    
    test_performance.close_r();
    cout<<"Done"<<endl;
    return 0;
}

