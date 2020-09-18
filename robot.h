/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   robot.h
 * Author: Sindiso Mkhatshwa
 *
 * Created on 10 September 2020, 02:58
 */

#ifndef ROBOT_H
#define ROBOT_H
#include <string> 
#include <iostream>
#include <vector>
#include <math.h>
#include <bits/stdc++.h>
#include <libplayerc/playerc.h>
namespace mkhsin035{
    struct Position
    {
      double yaw;
      double x;
      double y;
    }typedef pos;
    
    class robot{
    private:
        char cfg_file_name[7];
        char* host; //address of the host computer goes here
        int port; //the port this robot uses to connect to Player                
               
    public:
         
        //Player proxies
        playerc_ranger_t *sonar_proxy;
        playerc_position2d_t *p2d_proxy;
        playerc_blobfinder_t *blob_proxy;
        playerc_client_t *rob;
        //Comms
        int status; //1 if this robot is supposed to broadcast received coordinates. 0 if this robot is supposed to receive its own coordinates
        double bc_x; double bc_y; //broadcast coordinates
        double oil_spill_position_x; double oil_spill_position_y;
        double nearest_robot_x; double nearest_robot_y;
        double farthest_robot_x; double farthest_robot_y;
        double Df; double Dn; //distance to farthest and nearest robots
        
        robot();
        robot(char* host, int port, std::string name);
        bool is_self(robot& other);
        int connect_to_server();
        int subscribe_to_devices();
        void enable_motors();
        void set_motors(double& forward_speed, double& turning_speed);
        void request_geometries();
        void read_from_proxies();
        pos get_position(playerc_simulation_t *sim_proxy);
        void shutdown();
    };
          
};


#endif /* ROBOT_H */

