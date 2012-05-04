; Auto-generated. Do not edit!


(cl:in-package beta_nodes-msg)


;//! \htmlinclude PathSegment.msg.html

(cl:defclass <PathSegment> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (seg_type
    :reader seg_type
    :initarg :seg_type
    :type cl:fixnum
    :initform 0)
   (priority
    :reader priority
    :initarg :priority
    :type cl:fixnum
    :initform 0)
   (seg_number
    :reader seg_number
    :initarg :seg_number
    :type cl:integer
    :initform 0)
   (seg_length
    :reader seg_length
    :initarg :seg_length
    :type cl:float
    :initform 0.0)
   (init_point
    :reader init_point
    :initarg :init_point
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point))
   (ref_point
    :reader ref_point
    :initarg :ref_point
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point))
   (init_tan_angle
    :reader init_tan_angle
    :initarg :init_tan_angle
    :type geometry_msgs-msg:Quaternion
    :initform (cl:make-instance 'geometry_msgs-msg:Quaternion))
   (seg_psi
    :reader seg_psi
    :initarg :seg_psi
    :type cl:float
    :initform 0.0)
   (curvature
    :reader curvature
    :initarg :curvature
    :type cl:float
    :initform 0.0)
   (max_speeds
    :reader max_speeds
    :initarg :max_speeds
    :type geometry_msgs-msg:Twist
    :initform (cl:make-instance 'geometry_msgs-msg:Twist))
   (min_speeds
    :reader min_speeds
    :initarg :min_speeds
    :type geometry_msgs-msg:Twist
    :initform (cl:make-instance 'geometry_msgs-msg:Twist))
   (accel_limit
    :reader accel_limit
    :initarg :accel_limit
    :type cl:float
    :initform 0.0)
   (decel_limit
    :reader decel_limit
    :initarg :decel_limit
    :type cl:float
    :initform 0.0))
)

(cl:defclass PathSegment (<PathSegment>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PathSegment>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PathSegment)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name beta_nodes-msg:<PathSegment> is deprecated: use beta_nodes-msg:PathSegment instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <PathSegment>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:header-val is deprecated.  Use beta_nodes-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'seg_type-val :lambda-list '(m))
(cl:defmethod seg_type-val ((m <PathSegment>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:seg_type-val is deprecated.  Use beta_nodes-msg:seg_type instead.")
  (seg_type m))

(cl:ensure-generic-function 'priority-val :lambda-list '(m))
(cl:defmethod priority-val ((m <PathSegment>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:priority-val is deprecated.  Use beta_nodes-msg:priority instead.")
  (priority m))

(cl:ensure-generic-function 'seg_number-val :lambda-list '(m))
(cl:defmethod seg_number-val ((m <PathSegment>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:seg_number-val is deprecated.  Use beta_nodes-msg:seg_number instead.")
  (seg_number m))

(cl:ensure-generic-function 'seg_length-val :lambda-list '(m))
(cl:defmethod seg_length-val ((m <PathSegment>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:seg_length-val is deprecated.  Use beta_nodes-msg:seg_length instead.")
  (seg_length m))

(cl:ensure-generic-function 'init_point-val :lambda-list '(m))
(cl:defmethod init_point-val ((m <PathSegment>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:init_point-val is deprecated.  Use beta_nodes-msg:init_point instead.")
  (init_point m))

(cl:ensure-generic-function 'ref_point-val :lambda-list '(m))
(cl:defmethod ref_point-val ((m <PathSegment>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:ref_point-val is deprecated.  Use beta_nodes-msg:ref_point instead.")
  (ref_point m))

(cl:ensure-generic-function 'init_tan_angle-val :lambda-list '(m))
(cl:defmethod init_tan_angle-val ((m <PathSegment>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:init_tan_angle-val is deprecated.  Use beta_nodes-msg:init_tan_angle instead.")
  (init_tan_angle m))

(cl:ensure-generic-function 'seg_psi-val :lambda-list '(m))
(cl:defmethod seg_psi-val ((m <PathSegment>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:seg_psi-val is deprecated.  Use beta_nodes-msg:seg_psi instead.")
  (seg_psi m))

(cl:ensure-generic-function 'curvature-val :lambda-list '(m))
(cl:defmethod curvature-val ((m <PathSegment>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:curvature-val is deprecated.  Use beta_nodes-msg:curvature instead.")
  (curvature m))

(cl:ensure-generic-function 'max_speeds-val :lambda-list '(m))
(cl:defmethod max_speeds-val ((m <PathSegment>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:max_speeds-val is deprecated.  Use beta_nodes-msg:max_speeds instead.")
  (max_speeds m))

(cl:ensure-generic-function 'min_speeds-val :lambda-list '(m))
(cl:defmethod min_speeds-val ((m <PathSegment>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:min_speeds-val is deprecated.  Use beta_nodes-msg:min_speeds instead.")
  (min_speeds m))

(cl:ensure-generic-function 'accel_limit-val :lambda-list '(m))
(cl:defmethod accel_limit-val ((m <PathSegment>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:accel_limit-val is deprecated.  Use beta_nodes-msg:accel_limit instead.")
  (accel_limit m))

(cl:ensure-generic-function 'decel_limit-val :lambda-list '(m))
(cl:defmethod decel_limit-val ((m <PathSegment>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:decel_limit-val is deprecated.  Use beta_nodes-msg:decel_limit instead.")
  (decel_limit m))
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql '<PathSegment>)))
    "Constants for message type '<PathSegment>"
  '((:LINE . 1)
    (:ARC . 2)
    (:SPIN_IN_PLACE . 3))
)
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql 'PathSegment)))
    "Constants for message type 'PathSegment"
  '((:LINE . 1)
    (:ARC . 2)
    (:SPIN_IN_PLACE . 3))
)
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PathSegment>) ostream)
  "Serializes a message object of type '<PathSegment>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let* ((signed (cl:slot-value msg 'seg_type)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'priority)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'seg_number)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'seg_number)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'seg_number)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'seg_number)) ostream)
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'seg_length))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'init_point) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'ref_point) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'init_tan_angle) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'seg_psi))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'curvature))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'max_speeds) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'min_speeds) ostream)
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'accel_limit))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'decel_limit))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PathSegment>) istream)
  "Deserializes a message object of type '<PathSegment>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'seg_type) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'priority) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'seg_number)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'seg_number)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'seg_number)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'seg_number)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'seg_length) (roslisp-utils:decode-double-float-bits bits)))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'init_point) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'ref_point) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'init_tan_angle) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'seg_psi) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'curvature) (roslisp-utils:decode-double-float-bits bits)))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'max_speeds) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'min_speeds) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'accel_limit) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'decel_limit) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PathSegment>)))
  "Returns string type for a message object of type '<PathSegment>"
  "beta_nodes/PathSegment")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PathSegment)))
  "Returns string type for a message object of type 'PathSegment"
  "beta_nodes/PathSegment")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PathSegment>)))
  "Returns md5sum for a message object of type '<PathSegment>"
  "fc3d47c3da0120062a7ad316a732ef6e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PathSegment)))
  "Returns md5sum for a message object of type 'PathSegment"
  "fc3d47c3da0120062a7ad316a732ef6e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PathSegment>)))
  "Returns full string definition for message of type '<PathSegment>"
  (cl:format cl:nil "#Reference frame that the following coordinates should be interpreted relative to and timestamp to use when transforming~%Header header~%~%#Segment type enums~%int8 LINE = 1~%int8 ARC = 2~%int8 SPIN_IN_PLACE = 3~%~%#Segment type~%int8 seg_type~%~%#priority flag~%int8 priority~%~%#Segment number~%uint32 seg_number~%~%#Segment length~%float64 seg_length~%~%#Reference point~%geometry_msgs/Point init_point~%geometry_msgs/Point ref_point~%geometry_msgs/Quaternion init_tan_angle~%float32 seg_psi~%~%#Curvature~%float64 curvature~%~%#Speed limits for this segment~%geometry_msgs/Twist max_speeds~%geometry_msgs/Twist min_speeds~%~%#Acceleration limit for this segment (m/s^2 for lines/arcs, rads/s^2 for spin-in-place)~%float64 accel_limit~%float64 decel_limit~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: geometry_msgs/Twist~%# This expresses velocity in free space broken into it's linear and angular parts. ~%Vector3  linear~%Vector3  angular~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PathSegment)))
  "Returns full string definition for message of type 'PathSegment"
  (cl:format cl:nil "#Reference frame that the following coordinates should be interpreted relative to and timestamp to use when transforming~%Header header~%~%#Segment type enums~%int8 LINE = 1~%int8 ARC = 2~%int8 SPIN_IN_PLACE = 3~%~%#Segment type~%int8 seg_type~%~%#priority flag~%int8 priority~%~%#Segment number~%uint32 seg_number~%~%#Segment length~%float64 seg_length~%~%#Reference point~%geometry_msgs/Point init_point~%geometry_msgs/Point ref_point~%geometry_msgs/Quaternion init_tan_angle~%float32 seg_psi~%~%#Curvature~%float64 curvature~%~%#Speed limits for this segment~%geometry_msgs/Twist max_speeds~%geometry_msgs/Twist min_speeds~%~%#Acceleration limit for this segment (m/s^2 for lines/arcs, rads/s^2 for spin-in-place)~%float64 accel_limit~%float64 decel_limit~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: geometry_msgs/Twist~%# This expresses velocity in free space broken into it's linear and angular parts. ~%Vector3  linear~%Vector3  angular~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PathSegment>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     1
     1
     4
     8
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'init_point))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'ref_point))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'init_tan_angle))
     4
     8
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'max_speeds))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'min_speeds))
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PathSegment>))
  "Converts a ROS message object to a list"
  (cl:list 'PathSegment
    (cl:cons ':header (header msg))
    (cl:cons ':seg_type (seg_type msg))
    (cl:cons ':priority (priority msg))
    (cl:cons ':seg_number (seg_number msg))
    (cl:cons ':seg_length (seg_length msg))
    (cl:cons ':init_point (init_point msg))
    (cl:cons ':ref_point (ref_point msg))
    (cl:cons ':init_tan_angle (init_tan_angle msg))
    (cl:cons ':seg_psi (seg_psi msg))
    (cl:cons ':curvature (curvature msg))
    (cl:cons ':max_speeds (max_speeds msg))
    (cl:cons ':min_speeds (min_speeds msg))
    (cl:cons ':accel_limit (accel_limit msg))
    (cl:cons ':decel_limit (decel_limit msg))
))
