# robot.inc
# model for the robot "Robot"
# Author: Sindiso Mkhatshwa
# Date: 10 - 09 - 2020
#--------------------------------------------------------------------------
#code
#--------------------------------------------------------------------------
define robot_sonar sensor
(
    # transducer size [xsize ysize zsize] in meters
    size [0.01 0.05 0.01 ] 
    # range bounds [min max]
    range [0.3 2.0]
    # angular field of view in degrees
    fov 10
    # color that ranges are drawn in the gui
    color_rgba [ 1 0 0 1] 
    # how many rays in a beam
    samples 180
)

define robot_sonars ranger
( 
  # one line for each sonar [xpos ypos zpos heading]
  robot_sonar( pose [ 0.25 0.125 0 0]) #sonar infront,left
  robot_sonar( pose [ 0.25 -0.125 0 0]) #sonar infront,right
  robot_sonar( pose [ 0.125 0.25 0 30]) #sonar on left corner
  robot_sonar( pose [ 0.125 -0.25 0 -30]) #sonar on right corner
)

define robot_blobfinder blobfinder
(
	colors_count 1
	colors ["black"]	 # color of an oil spill
	image [160 120] 	 # resolution
	range 5.00 		 # meters
	fov 60 			 # field of view
)


#put everything together 
define robot position 
(
		  # actual size of the robot
		  size [0.5 0.5 0.5]
		  # centre of rotation offset
		  origin [0 0 0 0]

		  # specify the shape of the robot
		  block
		  (
			 points 6
			 point[5] [0 0]
			 point[4] [0 0.5]
			 point[3] [0.375 0.5]
			 point[2] [0.5 0.375]
			 point[1] [0.5 0.125]
			 point[0] [0.375 0]
			 z [0 0.5]

		  )
		#how is the robot driven
	  	drive "diff"

		#attach sensors to robot
		robot_sonars( ) 
          	robot_blobfinder( )

)
