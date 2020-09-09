# robot.inc
# model for the robot "Robot"
# Author: Sindiso Mkhatshwa
# Date: 10 - 09 - 2020

define robot sensor
(
    # transducer size [xsize ysize zsize] in meters
    size [0.01 0.05 0.01 ] 
    # range bounds [min max]
    range [0.3 2.0]
    # angular field of view in degrees
    fov 10
    # color that ranges are drawn in the gui
    color_rgba [ 0 1 0 0.5] 
    # how many rays in a beam
    samples 180
)

define robot_sonars ranger
( 
  # one line for each sonar [xpos ypos zpos heading]
  robot_sonar( pose [ 0.25 0.125 0 0]) #left eye
  robot_sonar( pose [ 0.25 -0.125 0 0]) #right eye
  robot_sonar( pose [ 0.125 0.25 0 30]) #left corner
  robot_sonar( pose [ 0.125 -0.25 0 -30]) #right corner
)

define robot_eyes blobfinder
(
	colors_count 2
	colors ["green" "black"]
	image [160 120] #resolution
	range 5.00 		 # meters
	fov 60 #fov (in unit_angle (degrees by def))
)



define robot position
(
		  # actual size
		  size [0.5 0.5 0.5]
		  # centre of rotation offset
		  origin [0 0 0 0]

		  # the shape of the robot
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
		#positional things
		  drive "diff"

		  #sensors attached to robot
		  robot_sonars( ) 
          	  robot_eyes( )

)
