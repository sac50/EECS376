FILE(REMOVE_RECURSE
  "../src/beta_nodes/msg"
  "../msg_gen"
  "../msg_gen"
  "CMakeFiles/ROSBUILD_genmsg_py"
  "../src/beta_nodes/msg/__init__.py"
  "../src/beta_nodes/msg/_estopMsg.py"
  "../src/beta_nodes/msg/_freeSpace.py"
  "../src/beta_nodes/msg/_velocityMsg.py"
  "../src/beta_nodes/msg/_vPassBack.py"
  "../src/beta_nodes/msg/_steeringMsg.py"
  "../src/beta_nodes/msg/_PathSegment.py"
  "../src/beta_nodes/msg/_obstacle.py"
  "../src/beta_nodes/msg/_orangeGoal.py"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_py.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
