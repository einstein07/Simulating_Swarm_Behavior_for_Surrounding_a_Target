/* 
 * File:   robot.h
 * Author: Sindiso Mkhatshwa
 * Created on 10 September 2020, 02:58
 */

#ifndef ROBOT_H
#define ROBOT_H
#include <string> 
#include <thread>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <functional>
#include <bits/stdc++.h>
#include <libplayerc/playerc.h>
namespace mkhsin035{
//------------------------------------------------------------------------------
//struct used to store robot position
//------------------------------------------------------------------------------
    struct Position
    {
      double yaw;   //yaw of robot in simulation
      double x;     //x position of robot in simulation     
      double y;     //y position of robot in simulation
    }typedef pos;
//------------------------------------------------------------------------------
//ROBOT CLASS
//------------------------------------------------------------------------------    
    class robot{
    private:
        char cfg_file_name[7];//robot model name as it appears in cofig file
        char* host;           //address of the host computer goes here
        int port;             //the port no this robot uses to connect to Player                
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
    public:
        /*Player proxies*/
        playerc_ranger_t *sonar_proxy;      //sonar proxy
        playerc_position2d_t *p2d_proxy;    //position proxy
        playerc_blobfinder_t *blob_proxy;   //blobfinder proxy
        playerc_client_t *rob;              //client proxy
//------------------------------------------------------------------------------
        /*used to handle communications*/
        int status;                                                             //1 if this robot is supposed to broadcast received coordinates. 0 if this robot is supposed to receive its own coordinates
        //broadcast coordinates
        double bc_x, bc_y;
        //oil spill location coordinates
        double oil_spill_position_x; double oil_spill_position_y;
        //nearest robot coordinates
        double nearest_robot_x; double nearest_robot_y;
        //farthest robot coordinates
        double farthest_robot_x; double farthest_robot_y;
        //distances to farthest and nearest robots
        double Df; double Dn;
//------------------------------------------------------------------------------
        pos current_position;
        /*Constructors*/
        robot();             //default constructor
        robot(
            char* host,      //address of the host computer            
            int port,        //the port no. this robot uses to connect to Player
            std::string name //robot model name as it appears on config file
            );
//------------------------------------------------------------------------------
        /*function declarations*/
        int connect_to_server();
        int subscribe_to_devices();
        void enable_motors();
        void set_motors(
                        double& forward_speed,//translational speed
                        double& turning_speed, //rotational speed
                        playerc_simulation_t *sim_proxy //player simulator proxy
                    );
        void request_geometries();
        void read_from_proxies();
        pos get_position(
                        playerc_simulation_t *sim_proxy //sim proxy
                    );
        bool is_self(
                        robot& other                    //robot
                    );
        void refresh();
        void shutdown();
    };
};
#endif /* ROBOT_H */

