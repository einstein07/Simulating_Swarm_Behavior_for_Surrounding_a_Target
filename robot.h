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
#include <libplayerc/playerc.h>
namespace mkhsin035{
    class{
    private:
        std::string host; //address of the host computer goes here
        int port; //the port this robot uses to connect to Player
        int status; //1 if this robot is connected to player. 0 if this robot is offline
        
        playerc_client_t *robot;
        playerc_position2d_t *p2d_proxy;
        playerc_ranger_t *blob_proxy;
        playerc_simulation_t *sim_proxy;
    public:
        robot();
        robot(std::string host, int port);
        int connect_to_server();
        int subscribe_to_devices();
        void enable_motors();
        void request_geometries();
        void shutdown();
    };
};


#endif /* ROBOT_H */

