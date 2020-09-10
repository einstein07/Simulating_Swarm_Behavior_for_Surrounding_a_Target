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
    mkhsin035::robot::robot():host(""), port(0), status(0){}
    
    /*
     * Constructor
     */
    mkhsin035::robot::robot(std::string host, int port, int status)
    {
        this->host = host;
        this->port = port;
        this->status = status;
    }

    int mkhsin035::robot::connect_to_server()
    {
        this->robot = playerc_client_create(NULL, this->host, this->port);
        if (playerc_client_connect(robot) != 0)
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
        this->sonar_proxy = playerc_ranger_create(this->robot, 0);
        this->p2d_proxy = playerc_position2d_create(this->robot, 0);
        this->blob_proxy = playerc_blobfinder_create(this->robot, 0);
        /*
         * subscribe to devices
         */
        if (playerc_ranger_subscribe(this->sonar_proxy, PLAYER_OPEN_MODE))
        {
            std<<"could not subscribe to sonar"<<std::endl;
            return -1;
        }
        else if (playerc_blobfinder_subscribe(this->blob_proxy, PLAYER_OPEN_MODE))
        {
            std<<"could not subscribe to blobfinder"<<std::endl;
            return -1;
        }
        else if (playerc_position2d_subscribe(this->p2d_proxy, PLAYER_OPEN_MODE))
        {
            std<<"could not subscribe to position2d proxy"<<std::endl;
            return -1;
        }
        else
        {
            return 0;
        }
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
    /* Shutdown */
    void mkhsin035::robot::shutdown()
    {
	playerc_position2d_unsubscribe(this->p2d_proxy);
	playerc_ranger_unsubscribe(this->sonar_proxy);
	playerc_blobfinder_unsubscribe(this->blob_proxy);
	playerc_simulation_unsubscribe(this->sim_proxy);

	playerc_position2d_destroy(this->p2d_proxy); 
	playerc_ranger_destroy(this->sonar_proxy);
	playerc_blobfinder_destroy(this->blob_proxy);
	playerc_simulation_destroy(this->sim_proxy);

	playerc_client_disconnect(this->robot);
        playerc_client_destroy(this->robot);
    }