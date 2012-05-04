
(cl:in-package :asdf)

(defsystem "beta_nodes-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "estopMsg" :depends-on ("_package_estopMsg"))
    (:file "_package_estopMsg" :depends-on ("_package"))
    (:file "freeSpace" :depends-on ("_package_freeSpace"))
    (:file "_package_freeSpace" :depends-on ("_package"))
    (:file "velocityMsg" :depends-on ("_package_velocityMsg"))
    (:file "_package_velocityMsg" :depends-on ("_package"))
    (:file "vPassBack" :depends-on ("_package_vPassBack"))
    (:file "_package_vPassBack" :depends-on ("_package"))
    (:file "steeringMsg" :depends-on ("_package_steeringMsg"))
    (:file "_package_steeringMsg" :depends-on ("_package"))
    (:file "PathSegment" :depends-on ("_package_PathSegment"))
    (:file "_package_PathSegment" :depends-on ("_package"))
    (:file "obstacle" :depends-on ("_package_obstacle"))
    (:file "_package_obstacle" :depends-on ("_package"))
    (:file "orangeGoal" :depends-on ("_package_orangeGoal"))
    (:file "_package_orangeGoal" :depends-on ("_package"))
  ))