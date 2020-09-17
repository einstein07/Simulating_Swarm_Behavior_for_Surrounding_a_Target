/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   communication.h
 * Author: Sindiso Mkhatshwa
 *
 * Created on 10 September 2020, 02:55
 */

#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include "robot.h"
#include <functional>
namespace mkhsin035{

  class comms{
  private:
        //radius of the communication circle
        double radius = 10;
  public:
        comms();
        void receive(mkhsin035::robot& robo, playerc_simulation_t *sim_proxy, double& bc_x, double& bc_y, double& oil_spill_position_x, double& oil_spill_position_y);
        void broadcast(mkhsin035::robot& robo, playerc_simulation_t *sim_proxy, std::vector<mkhsin035::robot> &robots);
  };  
  
};


#endif /* COMMUNICATION_H */

