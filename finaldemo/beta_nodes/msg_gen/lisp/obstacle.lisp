; Auto-generated. Do not edit!


(cl:in-package beta_nodes-msg)


;//! \htmlinclude obstacle.msg.html

(cl:defclass <obstacle> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (leftClearance
    :reader leftClearance
    :initarg :leftClearance
    :type cl:float
    :initform 0.0)
   (rightClearance
    :reader rightClearance
    :initarg :rightClearance
    :type cl:float
    :initform 0.0)
   (nearestObstacle
    :reader nearestObstacle
    :initarg :nearestObstacle
    :type cl:float
    :initform 0.0)
   (nearestTheta
    :reader nearestTheta
    :initarg :nearestTheta
    :type cl:fixnum
    :initform 0)
   (edgeDistance
    :reader edgeDistance
    :initarg :edgeDistance
    :type cl:float
    :initform 0.0)
   (edgeTheta
    :reader edgeTheta
    :initarg :edgeTheta
    :type cl:fixnum
    :initform 0)
   (firstObstacleTheta
    :reader firstObstacleTheta
    :initarg :firstObstacleTheta
    :type cl:fixnum
    :initform 0)
   (lastObstacleTheta
    :reader lastObstacleTheta
    :initarg :lastObstacleTheta
    :type cl:fixnum
    :initform 0)
   (obstacle
    :reader obstacle
    :initarg :obstacle
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass obstacle (<obstacle>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <obstacle>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'obstacle)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name beta_nodes-msg:<obstacle> is deprecated: use beta_nodes-msg:obstacle instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <obstacle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:header-val is deprecated.  Use beta_nodes-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'leftClearance-val :lambda-list '(m))
(cl:defmethod leftClearance-val ((m <obstacle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:leftClearance-val is deprecated.  Use beta_nodes-msg:leftClearance instead.")
  (leftClearance m))

(cl:ensure-generic-function 'rightClearance-val :lambda-list '(m))
(cl:defmethod rightClearance-val ((m <obstacle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:rightClearance-val is deprecated.  Use beta_nodes-msg:rightClearance instead.")
  (rightClearance m))

(cl:ensure-generic-function 'nearestObstacle-val :lambda-list '(m))
(cl:defmethod nearestObstacle-val ((m <obstacle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:nearestObstacle-val is deprecated.  Use beta_nodes-msg:nearestObstacle instead.")
  (nearestObstacle m))

(cl:ensure-generic-function 'nearestTheta-val :lambda-list '(m))
(cl:defmethod nearestTheta-val ((m <obstacle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:nearestTheta-val is deprecated.  Use beta_nodes-msg:nearestTheta instead.")
  (nearestTheta m))

(cl:ensure-generic-function 'edgeDistance-val :lambda-list '(m))
(cl:defmethod edgeDistance-val ((m <obstacle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:edgeDistance-val is deprecated.  Use beta_nodes-msg:edgeDistance instead.")
  (edgeDistance m))

(cl:ensure-generic-function 'edgeTheta-val :lambda-list '(m))
(cl:defmethod edgeTheta-val ((m <obstacle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:edgeTheta-val is deprecated.  Use beta_nodes-msg:edgeTheta instead.")
  (edgeTheta m))

(cl:ensure-generic-function 'firstObstacleTheta-val :lambda-list '(m))
(cl:defmethod firstObstacleTheta-val ((m <obstacle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:firstObstacleTheta-val is deprecated.  Use beta_nodes-msg:firstObstacleTheta instead.")
  (firstObstacleTheta m))

(cl:ensure-generic-function 'lastObstacleTheta-val :lambda-list '(m))
(cl:defmethod lastObstacleTheta-val ((m <obstacle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:lastObstacleTheta-val is deprecated.  Use beta_nodes-msg:lastObstacleTheta instead.")
  (lastObstacleTheta m))

(cl:ensure-generic-function 'obstacle-val :lambda-list '(m))
(cl:defmethod obstacle-val ((m <obstacle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:obstacle-val is deprecated.  Use beta_nodes-msg:obstacle instead.")
  (obstacle m))
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql '<obstacle>)))
    "Constants for message type '<obstacle>"
  '((:BOXWIDTH . 0.3)
    (:BOXLENGTH . 1.6)
    (:THREATRANGE . 1.0))
)
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql 'obstacle)))
    "Constants for message type 'obstacle"
  '((:BOXWIDTH . 0.3)
    (:BOXLENGTH . 1.6)
    (:THREATRANGE . 1.0))
)
(cl:defmethod roslisp-msg-protocol:serialize ((msg <obstacle>) ostream)
  "Serializes a message object of type '<obstacle>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'leftClearance))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'rightClearance))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'nearestObstacle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'nearestTheta)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'edgeDistance))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'edgeTheta)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'firstObstacleTheta)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'lastObstacleTheta)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'obstacle) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <obstacle>) istream)
  "Deserializes a message object of type '<obstacle>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'leftClearance) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'rightClearance) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'nearestObstacle) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'nearestTheta)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'edgeDistance) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'edgeTheta)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'firstObstacleTheta)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'lastObstacleTheta)) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'obstacle) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<obstacle>)))
  "Returns string type for a message object of type '<obstacle>"
  "beta_nodes/obstacle")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'obstacle)))
  "Returns string type for a message object of type 'obstacle"
  "beta_nodes/obstacle")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<obstacle>)))
  "Returns md5sum for a message object of type '<obstacle>"
  "2b6640e54f0c0b7b92e8fbb9f966bfe0")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'obstacle)))
  "Returns md5sum for a message object of type 'obstacle"
  "2b6640e54f0c0b7b92e8fbb9f966bfe0")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<obstacle>)))
  "Returns full string definition for message of type '<obstacle>"
  (cl:format cl:nil "Header header~%~%# laswer sweeps from the right(0) to left (180)~%~%float32 boxWidth = 0.3 # HALVED. remember, robot teack is ~.56, so make this a little over half of that~%float32 boxLength = 1.6~%~%float32 leftClearance  # distance to ping furthest on our right (would be 180 if we checked all of them)~%float32 rightClearance # distance to ping furthest on our right (would be 180 if we checked all of them)~%float32 threatRange = 1.0 # Range inwhich if we've hit an object we need to consider replanning~%~%float32 nearestObstacle~%uint8 nearestTheta~%~%float32 edgeDistance~%uint8 edgeTheta~%~%uint8 firstObstacleTheta ##should be rightmost obstacle ping~%uint8 lastObstacleTheta~%~%bool obstacle~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'obstacle)))
  "Returns full string definition for message of type 'obstacle"
  (cl:format cl:nil "Header header~%~%# laswer sweeps from the right(0) to left (180)~%~%float32 boxWidth = 0.3 # HALVED. remember, robot teack is ~.56, so make this a little over half of that~%float32 boxLength = 1.6~%~%float32 leftClearance  # distance to ping furthest on our right (would be 180 if we checked all of them)~%float32 rightClearance # distance to ping furthest on our right (would be 180 if we checked all of them)~%float32 threatRange = 1.0 # Range inwhich if we've hit an object we need to consider replanning~%~%float32 nearestObstacle~%uint8 nearestTheta~%~%float32 edgeDistance~%uint8 edgeTheta~%~%uint8 firstObstacleTheta ##should be rightmost obstacle ping~%uint8 lastObstacleTheta~%~%bool obstacle~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <obstacle>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4
     4
     4
     1
     4
     1
     1
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <obstacle>))
  "Converts a ROS message object to a list"
  (cl:list 'obstacle
    (cl:cons ':header (header msg))
    (cl:cons ':leftClearance (leftClearance msg))
    (cl:cons ':rightClearance (rightClearance msg))
    (cl:cons ':nearestObstacle (nearestObstacle msg))
    (cl:cons ':nearestTheta (nearestTheta msg))
    (cl:cons ':edgeDistance (edgeDistance msg))
    (cl:cons ':edgeTheta (edgeTheta msg))
    (cl:cons ':firstObstacleTheta (firstObstacleTheta msg))
    (cl:cons ':lastObstacleTheta (lastObstacleTheta msg))
    (cl:cons ':obstacle (obstacle msg))
))
