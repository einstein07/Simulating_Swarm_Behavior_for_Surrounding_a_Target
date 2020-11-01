/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   communication.h
 * Author: Sindiso Mkhatshwa
 * Created on 10 September 2020, 02:55
 */

#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include "robot.h"
namespace mkhsin035{
//------------------------------------------------------------------------------
//COMMUNICATION CLASS
//------------------------------------------------------------------------------
  class comms{
  private:
        double range;      //communication range
  public:
        comms(double range);                       //constructor
        void receive(
                    mkhsin035::robot& robo,         //receiving robot
                    double& bc_x, double& bc_y,     //received coordinates (Rj)
                    double& oil_spill_position_x,   //received target coords 
                    double& oil_spill_position_y
                );
        void broadcast(
                    mkhsin035::robot& robo,                 //broadcasting robot
                    std::vector<mkhsin035::robot> &robots   //all robots in sim
                );
  };   
};
#endif /* COMMUNICATION_H */

