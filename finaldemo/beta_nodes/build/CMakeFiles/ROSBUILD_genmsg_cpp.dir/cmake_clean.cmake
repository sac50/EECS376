FILE(REMOVE_RECURSE
  "../src/beta_nodes/msg"
  "../msg_gen"
  "../msg_gen"
  "CMakeFiles/ROSBUILD_genmsg_cpp"
  "../msg_gen/cpp/include/beta_nodes/estopMsg.h"
  "../msg_gen/cpp/include/beta_nodes/freeSpace.h"
  "../msg_gen/cpp/include/beta_nodes/velocityMsg.h"
  "../msg_gen/cpp/include/beta_nodes/vPassBack.h"
  "../msg_gen/cpp/include/beta_nodes/steeringMsg.h"
  "../msg_gen/cpp/include/beta_nodes/PathSegment.h"
  "../msg_gen/cpp/include/beta_nodes/obstacle.h"
  "../msg_gen/cpp/include/beta_nodes/orangeGoal.h"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_cpp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
