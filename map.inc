# map.inc
# defines floorplan for model
# Author: Sindiso Mkhatshwa
# Date: 10 - 09 - 2020
#--------------------------------------------------------------------------
#code
#--------------------------------------------------------------------------
define floorplan model
(
  color "gray30"
  # define a bounding box
  #size [1 1 1]
  boundary 1
  gui_nose 0
  gui_grid 0
  gui_move 0
  gui_outline 0
  gripper_return 0
  fiducial_return 0
  ranger_return 1
  obstacle_return 1
)
define zone model
(
  color	"orange"
  size [ 2 2 0.02 ]

  gui_nose 0
  gui_grid 0
  gui_move 0
  gui_outline 0

  # insensible to collision and range sensors
  obstacle_return 0
  ranger_return 0  
)

define oil model
(
    block (points 4
      point[0] [1 0]
      point[1] [1 1]
      point[2] [0 1]
      point[3] [0 0]
      z [0 1]
      )
    #just a small cube 
    size [0.1 0.1 0.1]
	color "amber"
)

