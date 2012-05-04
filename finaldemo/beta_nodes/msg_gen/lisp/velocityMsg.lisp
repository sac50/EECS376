; Auto-generated. Do not edit!


(cl:in-package beta_nodes-msg)


;//! \htmlinclude velocityMsg.msg.html

(cl:defclass <velocityMsg> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (velocity
    :reader velocity
    :initarg :velocity
    :type cl:float
    :initform 0.0))
)

(cl:defclass velocityMsg (<velocityMsg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <velocityMsg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'velocityMsg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name beta_nodes-msg:<velocityMsg> is deprecated: use beta_nodes-msg:velocityMsg instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <velocityMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:header-val is deprecated.  Use beta_nodes-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'velocity-val :lambda-list '(m))
(cl:defmethod velocity-val ((m <velocityMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:velocity-val is deprecated.  Use beta_nodes-msg:velocity instead.")
  (velocity m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <velocityMsg>) ostream)
  "Serializes a message object of type '<velocityMsg>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'velocity))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <velocityMsg>) istream)
  "Deserializes a message object of type '<velocityMsg>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'velocity) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<velocityMsg>)))
  "Returns string type for a message object of type '<velocityMsg>"
  "beta_nodes/velocityMsg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'velocityMsg)))
  "Returns string type for a message object of type 'velocityMsg"
  "beta_nodes/velocityMsg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<velocityMsg>)))
  "Returns md5sum for a message object of type '<velocityMsg>"
  "f829323f183fabb3f889a576f21902c2")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'velocityMsg)))
  "Returns md5sum for a message object of type 'velocityMsg"
  "f829323f183fabb3f889a576f21902c2")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<velocityMsg>)))
  "Returns full string definition for message of type '<velocityMsg>"
  (cl:format cl:nil "Header header~%float32 velocity # linear or angular, dependent on segment type~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'velocityMsg)))
  "Returns full string definition for message of type 'velocityMsg"
  (cl:format cl:nil "Header header~%float32 velocity # linear or angular, dependent on segment type~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <velocityMsg>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <velocityMsg>))
  "Converts a ROS message object to a list"
  (cl:list 'velocityMsg
    (cl:cons ':header (header msg))
    (cl:cons ':velocity (velocity msg))
))
