/* 
 * File:   robot.cpp
 * Author: Sindiso Mkhatshwa
 *
 * Created on 10 September 2020, 02:58
 */
#include "robot.h"
//------------------------------------------------------------------------------
//CODE
//------------------------------------------------------------------------------
    /*
    * Default constructor 
    */
    mkhsin035::robot::robot():host(""), port(0), status(0),
            oil_spill_position_x(-1000), oil_spill_position_y(-1000),
            nearest_robot_x(-1000), nearest_robot_y(-1000),
    farthest_robot_x(0), farthest_robot_y(0){}
    
    /*
     * Constructor
     */
    mkhsin035::robot::robot(char* host, int port, std::string name):
            oil_spill_position_x(-1000), oil_spill_position_y(-1000),
            nearest_robot_x(INFINITY), nearest_robot_y(INFINITY),
    farthest_robot_x(INFINITY), farthest_robot_y(INFINITY), Dn(INFINITY), Df(INFINITY),
            bc_x(INFINITY), bc_y(INFINITY)
    {
        int n = name.length(); 
  
        
  
        // copying the contents of the 
        // string to char array 
        strcpy(cfg_file_name, name.c_str());
        this->host = host;
        this->port = port;
        this->status = 0;
    }
    
    bool mkhsin035::robot::is_self(robot& other)
    {
        for (int i = 0; i < 7; i++)
        {
            if(this->cfg_file_name[i] != other.cfg_file_name[i])
                return false;
        }
        return true;
    }

    int mkhsin035::robot::connect_to_server()
    {
        this->rob = playerc_client_create(NULL, this->host, this->port);
        if (playerc_client_connect(rob) != 0)
        {
            std::cout<<"could not connect to player"<<std::endl;
            return -1;
        }
        else
        {
            return 0;
        }
    }
    /*Create and subscribe to devices, in that order*/
    int mkhsin035::robot::subscribe_to_devices()
    {
        /*
         * create devices first
         */
        this->sonar_proxy = playerc_ranger_create(this->rob, 0);
        if (playerc_ranger_subscribe(this->sonar_proxy, PLAYER_OPEN_MODE))
            return -1;
        this->p2d_proxy = playerc_position2d_create(this->rob, 0);
        if (playerc_position2d_subscribe(this->p2d_proxy, PLAYER_OPEN_MODE))
            return -1;
        this->blob_proxy = playerc_blobfinder_create(this->rob, 0);
        if (playerc_blobfinder_subscribe(this->blob_proxy, PLAYER_OPEN_MODE))
            return -1;
        return 0;
    }
    /*Enable motors*/
    void mkhsin035::robot::enable_motors()
    {
        playerc_position2d_enable(this->p2d_proxy, 1);
    }
    /*Request device geometries*/
    void mkhsin035::robot::request_geometries()
    {
        playerc_position2d_get_geom(this->p2d_proxy);
	playerc_ranger_get_geom(this->sonar_proxy);
    }
    
    /*read from proxies*/
    void mkhsin035::robot::read_from_proxies()
    {
        playerc_client_read(this->rob);
    }
            
    mkhsin035::pos mkhsin035::robot::get_position(playerc_simulation_t *sim_proxy)
    {
        mkhsin035::pos position;
        playerc_simulation_get_pose2d(sim_proxy, cfg_file_name, &position.x, &position.y, &position.yaw);
        return position;
    }

    void mkhsin035::robot::set_motors(double& forward_speed, double& turning_speed)
    {
        playerc_position2d_set_cmd_vel(this->p2d_proxy, forward_speed, 0.00, DTOR(turning_speed), 1);
    }
    void mkhsin035::robot::refresh()
    {
        nearest_robot_x     = INFINITY;
        nearest_robot_y     = INFINITY;
        farthest_robot_x    = INFINITY;
        farthest_robot_y    = INFINITY;
        Dn                  = INFINITY;
        Df                  = INFINITY;
        bc_x                = INFINITY;
        bc_y                = INFINITY;
    }
    
    /* Shutdown */
    void mkhsin035::robot::shutdown()
    {
	playerc_position2d_unsubscribe(this->p2d_proxy);
	playerc_ranger_unsubscribe(this->sonar_proxy);
	playerc_blobfinder_unsubscribe(this->blob_proxy);

	playerc_position2d_destroy(this->p2d_proxy); 
	playerc_ranger_destroy(this->sonar_proxy);
	playerc_blobfinder_destroy(this->blob_proxy);

	playerc_client_disconnect(this->rob);
        playerc_client_destroy(this->rob);
    }