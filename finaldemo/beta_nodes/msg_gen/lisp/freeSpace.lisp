; Auto-generated. Do not edit!


(cl:in-package beta_nodes-msg)


;//! \htmlinclude freeSpace.msg.html

(cl:defclass <freeSpace> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (point
    :reader point
    :initarg :point
    :type geometry_msgs-msg:PointStamped
    :initform (cl:make-instance 'geometry_msgs-msg:PointStamped))
   (obstacleFound
    :reader obstacleFound
    :initarg :obstacleFound
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass freeSpace (<freeSpace>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <freeSpace>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'freeSpace)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name beta_nodes-msg:<freeSpace> is deprecated: use beta_nodes-msg:freeSpace instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <freeSpace>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:header-val is deprecated.  Use beta_nodes-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'point-val :lambda-list '(m))
(cl:defmethod point-val ((m <freeSpace>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:point-val is deprecated.  Use beta_nodes-msg:point instead.")
  (point m))

(cl:ensure-generic-function 'obstacleFound-val :lambda-list '(m))
(cl:defmethod obstacleFound-val ((m <freeSpace>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:obstacleFound-val is deprecated.  Use beta_nodes-msg:obstacleFound instead.")
  (obstacleFound m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <freeSpace>) ostream)
  "Serializes a message object of type '<freeSpace>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'point) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'obstacleFound) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <freeSpace>) istream)
  "Deserializes a message object of type '<freeSpace>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'point) istream)
    (cl:setf (cl:slot-value msg 'obstacleFound) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<freeSpace>)))
  "Returns string type for a message object of type '<freeSpace>"
  "beta_nodes/freeSpace")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'freeSpace)))
  "Returns string type for a message object of type 'freeSpace"
  "beta_nodes/freeSpace")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<freeSpace>)))
  "Returns md5sum for a message object of type '<freeSpace>"
  "fc557d704f107471807774c96211022d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'freeSpace)))
  "Returns md5sum for a message object of type 'freeSpace"
  "fc557d704f107471807774c96211022d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<freeSpace>)))
  "Returns full string definition for message of type '<freeSpace>"
  (cl:format cl:nil "#Message the communicates a point of where to go to dodge obstacles and a flag for if there are any obstacles ~%Header header~%~%#Point to navigate around the obstacle~%geometry_msgs/PointStamped point~%~%#Flag for if an obstacle exists~%bool obstacleFound~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/PointStamped~%# This represents a Point with reference coordinate frame and timestamp~%Header header~%Point point~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'freeSpace)))
  "Returns full string definition for message of type 'freeSpace"
  (cl:format cl:nil "#Message the communicates a point of where to go to dodge obstacles and a flag for if there are any obstacles ~%Header header~%~%#Point to navigate around the obstacle~%geometry_msgs/PointStamped point~%~%#Flag for if an obstacle exists~%bool obstacleFound~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/PointStamped~%# This represents a Point with reference coordinate frame and timestamp~%Header header~%Point point~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <freeSpace>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'point))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <freeSpace>))
  "Converts a ROS message object to a list"
  (cl:list 'freeSpace
    (cl:cons ':header (header msg))
    (cl:cons ':point (point msg))
    (cl:cons ':obstacleFound (obstacleFound msg))
))
