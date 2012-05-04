; Auto-generated. Do not edit!


(cl:in-package beta_nodes-msg)


;//! \htmlinclude orangeGoal.msg.html

(cl:defclass <orangeGoal> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (point
    :reader point
    :initarg :point
    :type geometry_msgs-msg:PointStamped
    :initform (cl:make-instance 'geometry_msgs-msg:PointStamped)))
)

(cl:defclass orangeGoal (<orangeGoal>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <orangeGoal>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'orangeGoal)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name beta_nodes-msg:<orangeGoal> is deprecated: use beta_nodes-msg:orangeGoal instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <orangeGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:header-val is deprecated.  Use beta_nodes-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'point-val :lambda-list '(m))
(cl:defmethod point-val ((m <orangeGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:point-val is deprecated.  Use beta_nodes-msg:point instead.")
  (point m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <orangeGoal>) ostream)
  "Serializes a message object of type '<orangeGoal>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'point) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <orangeGoal>) istream)
  "Deserializes a message object of type '<orangeGoal>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'point) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<orangeGoal>)))
  "Returns string type for a message object of type '<orangeGoal>"
  "beta_nodes/orangeGoal")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'orangeGoal)))
  "Returns string type for a message object of type 'orangeGoal"
  "beta_nodes/orangeGoal")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<orangeGoal>)))
  "Returns md5sum for a message object of type '<orangeGoal>"
  "8cc5562927288add91dffab1b9ff1fba")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'orangeGoal)))
  "Returns md5sum for a message object of type 'orangeGoal"
  "8cc5562927288add91dffab1b9ff1fba")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<orangeGoal>)))
  "Returns full string definition for message of type '<orangeGoal>"
  (cl:format cl:nil "#Message the communicates a point of where to go to dodge obstacles and a flag for if there are any obstacles ~%Header header~% ~%#Point to navigate around the obstacle~%geometry_msgs/PointStamped point~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/PointStamped~%# This represents a Point with reference coordinate frame and timestamp~%Header header~%Point point~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'orangeGoal)))
  "Returns full string definition for message of type 'orangeGoal"
  (cl:format cl:nil "#Message the communicates a point of where to go to dodge obstacles and a flag for if there are any obstacles ~%Header header~% ~%#Point to navigate around the obstacle~%geometry_msgs/PointStamped point~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/PointStamped~%# This represents a Point with reference coordinate frame and timestamp~%Header header~%Point point~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <orangeGoal>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'point))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <orangeGoal>))
  "Converts a ROS message object to a list"
  (cl:list 'orangeGoal
    (cl:cons ':header (header msg))
    (cl:cons ':point (point msg))
))
