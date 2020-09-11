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
    
//    //enable motors
    robot1.enable_motors();
    robot2.enable_motors();
    robot3.enable_motors();
    robot4.enable_motors();
//    //request geometries
    robot1.request_geometries();
    robot2.request_geometries();
    robot3.request_geometries();
    robot4.request_geometries();
    
    return 0;
}

