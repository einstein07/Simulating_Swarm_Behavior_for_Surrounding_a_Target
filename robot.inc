# robot.inc
# model for the robot "Robot"
# Author: Sindiso Mkhatshwa
# Date: 10 - 09 - 2020

define robot position
(
		  # actual size
		  size [0.5 0.5 0.5]
		  # centre of rotation offset
		  origin [0.125 0 0 0]

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

)
