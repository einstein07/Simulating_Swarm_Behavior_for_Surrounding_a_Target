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
namespace mkhsin035{
  class comms{
  private:
      std::vector<mkhsin035::robot> robots;
  public:
      comms(std::vector<mkhsin035::robot> robots);
      void broadcast(item_t *itemList, int listLength, playerc_simulation_t *sim, char *robot_name);
      void receive();
  };  
  struct Item
{
      char name[16];
      double x;
      double y;
}typedef item_t;
};


#endif /* COMMUNICATION_H */

