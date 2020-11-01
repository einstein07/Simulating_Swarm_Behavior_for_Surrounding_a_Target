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
#include "tests.h"
#include "movement.h"

mkhsin035::tests::tests(std::string filename):filename(filename)
{
    file.open(filename);
}
void mkhsin035::tests::record(double D, playerc_simulation_t *sim_proxy, std::vector<mkhsin035::robot> &robots)
{
    mkhsin035::pos position;
    double sum = 0;  
    int target_aware_robots = 0;
    for(int i=0; i < robots.size(); i++)
    {
        position = robots[i].get_position(sim_proxy);
        if(robots[i].oil_spill_position_x != -1000)
        {
            target_aware_robots += 1;
            double Dt = mkhsin035::movement::dist(position.x, position.y, robots[i].oil_spill_position_x, robots[i].oil_spill_position_y);
            sum += (Dt - (D/2)) * (Dt - (D/2));
        }
    }
    sum = sum / robots.size();
    file << sum<<" "<<target_aware_robots<<"\n";
}
void mkhsin035::tests::close_r()
{
    file.close();
}