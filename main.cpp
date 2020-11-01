/*
 * Driver file for swarm robotics system.
 * Declares robot instances and coordinates the various behaviors of the 
 * individual robots
 */

/* 
 * File:   main.cpp
 * Author: Sindiso Mkhatshwa
 * Created on 11 September 2020, 21:48
 */


#include "robot.h"
#include "tests.h"
#include "movement.h"
#include "communication.h"

using namespace std;
using namespace mkhsin035;

int main(int argc, char** argv) {
    //--------------------------------------------------------------------------
    //declare robots
    //--------------------------------------------------------------------------
    robot robot1("localhost", 6665, "robot1");
    robot robot2("localhost", 6666, "robot2");
    robot robot3("localhost", 6667, "robot3");
    robot robot4("localhost", 6668, "robot4");
    robot robot5("localhost", 6669, "robot5");
    robot robot6("localhost", 6670, "robot6");

    //declare vector to hold all robots
    vector<robot> robots;
    //--------------------------------------------------------------------------
    //connect robots to server
    //--------------------------------------------------------------------------
    robot1.connect_to_server();
    robot2.connect_to_server();
    robot3.connect_to_server();
    robot4.connect_to_server();
    robot5.connect_to_server();
    robot6.connect_to_server();
    //--------------------------------------------------------------------------
    //subscribe to devices
    //--------------------------------------------------------------------------
    robot1.subscribe_to_devices();
    robot2.subscribe_to_devices();
    robot3.subscribe_to_devices();
    robot4.subscribe_to_devices();
    robot5.subscribe_to_devices();
    robot6.subscribe_to_devices();
    cout<<"subscribing"<<endl;
    playerc_simulation_t *sim_proxy;
    sim_proxy = playerc_simulation_create(robot1.rob, 0);
	  if (playerc_simulation_subscribe(sim_proxy, PLAYER_OPEN_MODE))
                cout<<"could not subscribe to simulator proxy"<<endl;
    //--------------------------------------------------------------------------
    //enable motors
    //--------------------------------------------------------------------------
    robot1.enable_motors();
    robot2.enable_motors();
    robot3.enable_motors();
    robot4.enable_motors();
    robot5.enable_motors();
    robot6.enable_motors();
    //--------------------------------------------------------------------------
    //request geometries
    //--------------------------------------------------------------------------
    robot1.request_geometries();
    robot2.request_geometries();
    robot3.request_geometries();
    robot4.request_geometries();
    robot5.request_geometries();
    robot6.request_geometries();
    //--------------------------------------------------------------------------
    //push back robots into vector of all swarm robots
    //--------------------------------------------------------------------------
    robots.push_back(robot1);
    robots.push_back(robot2);
    robots.push_back(robot3);
    robots.push_back(robot4);
    robots.push_back(robot5);
    robots.push_back(robot6);
    //--------------------------------------------------------------------------
    //useful variables 
    //--------------------------------------------------------------------------
    double forward_speed = 0.0;
    double turning_speed = 0.0;
    double forward_speed1, turning_speed1;     //robot 1 
    double forward_speed2, turning_speed2;     //robot 2
    double forward_speed3, turning_speed3;     //robot 3
    double forward_speed4, turning_speed4;     //robot 4
    double forward_speed5, turning_speed5;     //robot 5 
    double forward_speed6, turning_speed6;     //robot 6

    int counter = 0;
    double comms_range = 9;
    double circle_diameter = 15;
    double min_distance = 0.8;

    comms c(comms_range);
    movement moves(circle_diameter, min_distance);
    tests test_performance("results.txt");

    for (int i = 0; i < 1000; i++){
    //--------------------------------------------------------------------------
    //read from proxies
    //--------------------------------------------------------------------------
        robots[0].read_from_proxies();
	robots[1].read_from_proxies();
	robots[2].read_from_proxies();
	robots[3].read_from_proxies();
        robots[4].read_from_proxies();
	robots[5].read_from_proxies();
    //--------------------------------------------------------------------------
                                    //robot 1
    //--------------------------------------------------------------------------
        robots[0].get_position(sim_proxy);
	thread r1_thread1(&movement::avoid_collisions, moves, std::ref(robots[0]), robots[0].sonar_proxy, std::ref(forward_speed), std::ref(turning_speed));
	thread r1_thread2(&comms::broadcast, c, std::ref(robots[0]), std::ref(robots));
        //----------------------------------------------------------------------
        //run one of these behaviors in the main thread        
        //----------------------------------------------------------------------
	if (robots[0].blob_proxy->blobs_count == 0 && (robots[0].oil_spill_position_x == -1000))
        {
            moves.wander(robots[0], sim_proxy, forward_speed1, turning_speed1);
        }
        else
        {
            moves.move(robots[0], sim_proxy, forward_speed1, turning_speed1);
        }
	//----------------------------------------------------------------------
        //wait for the two threads to finish
        //----------------------------------------------------------------------
	if (r1_thread1.joinable()) { r1_thread1.join(); }
	if (r1_thread2.joinable()) { r1_thread2.join(); }	
        //----------------------------------------------------------------------
        //Choose action to be performed by the robot
        //----------------------------------------------------------------------
	forward_speed == 0?(turning_speed == 0? robots[0].set_motors(forward_speed1, turning_speed1, sim_proxy):robots[0].set_motors(forward_speed, turning_speed, sim_proxy)):robots[0].set_motors(forward_speed, turning_speed, sim_proxy);      
        //----------------------------------------------------------------------
        //Broadcast current position
        //----------------------------------------------------------------------
        c.broadcast(robots[0], robots);
    //--------------------------------------------------------------------------
                                    //robot 2
    //--------------------------------------------------------------------------
        robots[1].get_position(sim_proxy);
	thread r2_thread1(&movement::avoid_collisions, moves, std::ref(robots[1]), robots[1].sonar_proxy, std::ref(forward_speed), std::ref(turning_speed));
        thread r2_thread2(&comms::broadcast, c, std::ref(robots[1]), std::ref(robots));
        //----------------------------------------------------------------------
        //run one of these behaviors in the main thread
        //----------------------------------------------------------------------
        if (robots[1].blob_proxy->blobs_count == 0 && (robots[1].oil_spill_position_x == -1000))
        {
            moves.wander(robots[1], sim_proxy, forward_speed2, turning_speed2);
        }
        else
        {
            moves.move(robots[1], sim_proxy, forward_speed2, turning_speed2);
        }
        //----------------------------------------------------------------------
        //wait for the two threads to finish
        //----------------------------------------------------------------------
        if (r2_thread1.joinable()) { r2_thread1.join(); }
        if (r2_thread2.joinable()) { r2_thread2.join(); }
        //----------------------------------------------------------------------
        //Choose action to be performed by the robot
        //----------------------------------------------------------------------
	forward_speed == 0?(turning_speed == 0? robots[1].set_motors(forward_speed2, turning_speed2, sim_proxy):robots[1].set_motors(forward_speed, turning_speed, sim_proxy)):robots[1].set_motors(forward_speed, turning_speed, sim_proxy);      
        //----------------------------------------------------------------------
        //Broadcast current position
        //----------------------------------------------------------------------
        c.broadcast(robots[1], robots);
    //--------------------------------------------------------------------------
                                    //robot 3
    //--------------------------------------------------------------------------
        robots[2].get_position(sim_proxy);
	thread r3_thread1(&movement::avoid_collisions, moves, std::ref(robots[2]), robots[2].sonar_proxy, std::ref(forward_speed), std::ref(turning_speed));
        thread r3_thread2(&comms::broadcast, c, std::ref(robots[2]), std::ref(robots));
        //----------------------------------------------------------------------
        //run one of these behaviors in the main thread
        //----------------------------------------------------------------------
        if (robots[2].blob_proxy->blobs_count == 0 && (robots[2].oil_spill_position_x == -1000))
        {
            moves.wander(robots[2], sim_proxy, forward_speed3, turning_speed3);
        }
        else
        {
            moves.move(robots[2], sim_proxy, forward_speed3, turning_speed3);
        }
        //----------------------------------------------------------------------
        //wait for the two threads to finish
        //----------------------------------------------------------------------
        if (r3_thread1.joinable()) { r3_thread1.join(); }
        if (r3_thread2.joinable()) { r3_thread2.join(); }
        //----------------------------------------------------------------------
        //Choose action to be performed by the robot
        //----------------------------------------------------------------------
	forward_speed == 0?(turning_speed == 0? robots[2].set_motors(forward_speed3, turning_speed3, sim_proxy):robots[2].set_motors(forward_speed, turning_speed, sim_proxy)):robots[2].set_motors(forward_speed, turning_speed, sim_proxy);      
        //----------------------------------------------------------------------
        //Broadcast current position
        //----------------------------------------------------------------------
        c.broadcast(robots[2], robots);
        
    //--------------------------------------------------------------------------
                                    //robot 4
    //--------------------------------------------------------------------------
        robots[3].get_position(sim_proxy);
	thread r4_thread1(&movement::avoid_collisions, moves, std::ref(robots[3]), robots[3].sonar_proxy, std::ref(forward_speed), std::ref(turning_speed));
        thread r4_thread2(&comms::broadcast, c, std::ref(robots[3]), std::ref(robots));
        //----------------------------------------------------------------------
        //run one of these behaviors in the main thread
        //----------------------------------------------------------------------
        if (robots[3].blob_proxy->blobs_count == 0 && (robots[3].oil_spill_position_x == -1000))
        {
            moves.wander(robots[3], sim_proxy, forward_speed4, turning_speed4);
        }
        else
        {
            moves.move(robots[3], sim_proxy, forward_speed4, turning_speed4);
        }
        //----------------------------------------------------------------------
        //wait for the two threads to finish
        //----------------------------------------------------------------------
        if (r4_thread1.joinable()) { r4_thread1.join(); }
        if (r4_thread2.joinable()) { r4_thread2.join(); }
        //----------------------------------------------------------------------
        //Choose action to be performed by the robot
        //----------------------------------------------------------------------
	forward_speed == 0?(turning_speed == 0? robots[3].set_motors(forward_speed4, turning_speed4, sim_proxy):robots[3].set_motors(forward_speed, turning_speed, sim_proxy)):robots[3].set_motors(forward_speed, turning_speed, sim_proxy);      
        //----------------------------------------------------------------------
        //Broadcast current position
        //----------------------------------------------------------------------
        c.broadcast(robots[3], robots);
        
    //--------------------------------------------------------------------------
                                    //robot 5
    //--------------------------------------------------------------------------
        robots[4].get_position(sim_proxy);
	thread r5_thread1(&movement::avoid_collisions, moves, std::ref(robots[4]), robots[4].sonar_proxy, std::ref(forward_speed), std::ref(turning_speed));
        thread r5_thread2(&comms::broadcast, c, std::ref(robots[4]), std::ref(robots));
        //----------------------------------------------------------------------
        //run one of these behaviors in the main thread
        //----------------------------------------------------------------------
        if (robots[4].blob_proxy->blobs_count == 0 && (robots[4].oil_spill_position_x == -1000))
        {
            moves.wander(robots[4], sim_proxy, forward_speed5, turning_speed5);
        }
        else
        {
            moves.move(robots[4], sim_proxy, forward_speed5, turning_speed5);
        }
        //----------------------------------------------------------------------
        //wait for the two threads to finish
        //----------------------------------------------------------------------
        if (r5_thread1.joinable()) { r5_thread1.join(); }
        if (r5_thread2.joinable()) { r5_thread2.join(); }
        //----------------------------------------------------------------------
        //Choose action to be performed by the robot
        //----------------------------------------------------------------------
	forward_speed == 0?(turning_speed == 0? robots[4].set_motors(forward_speed5, turning_speed5, sim_proxy):robots[4].set_motors(forward_speed, turning_speed, sim_proxy)):robots[4].set_motors(forward_speed, turning_speed, sim_proxy);      
        //----------------------------------------------------------------------
        //Broadcast current position
        //----------------------------------------------------------------------
        c.broadcast(robots[4], robots);
    //--------------------------------------------------------------------------
                                    //robot 6
    //--------------------------------------------------------------------------
        robots[5].get_position(sim_proxy);
	thread r6_thread1(&movement::avoid_collisions, moves, std::ref(robots[5]), robots[5].sonar_proxy, std::ref(forward_speed), std::ref(turning_speed));
        thread r6_thread2(&comms::broadcast, c, std::ref(robots[5]), std::ref(robots));
        //----------------------------------------------------------------------
        //run one of these behaviors in the main thread
        //----------------------------------------------------------------------
        if (robots[5].blob_proxy->blobs_count == 0 && (robots[5].oil_spill_position_x == -1000))
        {
            moves.wander(robots[5], sim_proxy, forward_speed6, turning_speed6);
        }
        else
        {
            moves.move(robots[5], sim_proxy, forward_speed6, turning_speed6);
        }
        //----------------------------------------------------------------------
        //wait for the two threads to finish
        //----------------------------------------------------------------------
        if (r6_thread1.joinable()) { r6_thread1.join(); }
        if (r6_thread2.joinable()) { r6_thread2.join(); }
        //----------------------------------------------------------------------
        //Choose action to be performed by the robot
        //----------------------------------------------------------------------
	forward_speed == 0?(turning_speed == 0? robots[5].set_motors(forward_speed6, turning_speed6, sim_proxy):robots[5].set_motors(forward_speed, turning_speed, sim_proxy)):robots[5].set_motors(forward_speed, turning_speed, sim_proxy);      
        //----------------------------------------------------------------------
        //Broadcast current position
        //----------------------------------------------------------------------
        c.broadcast(robots[5], robots);

        counter++;
        if(counter == 10)
        {
            cout<<"recording..."<<endl;
            test_performance.record(circle_diameter, sim_proxy, robots);
            robots[0].refresh();
            robots[1].refresh();
            robots[2].refresh();
	    robots[3].refresh();
            robots[4].refresh();
            robots[5].refresh();
            counter = 0;
        }
        
    }
    
    test_performance.close_r();
    cout<<"Done"<<endl;
    return 0;
}

