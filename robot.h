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
#include <libplayerc/playerc.h>
namespace mkhsin035{
    class robot{
    private:
        std_string cfg_file_name;
        std::string host; //address of the host computer goes here
        int port; //the port this robot uses to connect to Player
        int status; //1 if this robot is connected to player. 0 if this robot is offline
        //Comms
        double bc_x; double bc_y; //broadcast coordinates
        double oil_spill_position_x; double oil_spill_position_y;
        double nearest_robot_x; double nearest_robot_y;
        double farthest_robot_x; double farthest_robot_y;
        
        //Player proxies
        playerc_client_t *robot;
        playerc_ranger_t *sonar_proxy;
        playerc_position2d_t *p2d_proxy;
        playerc_blobfinder_t *blob_proxy;
        playerc_simulation_t *sim_proxy;
    public:
        //Comms
        double bc_x; double bc_y; //broadcast coordinates
        double oil_spill_position_x; double oil_spill_position_y;
        double nearest_robot_x; double nearest_robot_y;
        double farthest_robot_x; double farthest_robot_y;
        double Df; double Dn; //distance to farthest and nearest robots
        
        robot();
        robot(std::string host, int port, int status, std::string cfg_file_name);
        int connect_to_server();
        int subscribe_to_devices();
        void enable_motors();
        void request_geometries();
        pos get_position();
        void shutdown();
    };
    struct Position
    {
      double yaw;
      double x;
      double y;
    }typedef pos;
          
};


#endif /* ROBOT_H */

