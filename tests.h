/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   tests.h
 * Author: Sindiso Mkhatshwa
 * Created on 24 September 2020, 01:55
 */

#ifndef TESTS_H
#define TESTS_H
#include "robot.h"
#include <fstream>
namespace mkhsin035{
//------------------------------------------------------------------------------
//TESTS CLASS
//------------------------------------------------------------------------------
  class tests{
  private:
    std::ofstream file;
    std::string filename;
  public:
    tests(std::string filename);
    void record(double D, playerc_simulation_t *sim_proxy, std::vector<mkhsin035::robot> &robots);
    void close_r();
  };   
};
#endif /* TESTS_H */

