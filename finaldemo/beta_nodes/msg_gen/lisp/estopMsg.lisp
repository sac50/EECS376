; Auto-generated. Do not edit!


(cl:in-package beta_nodes-msg)


;//! \htmlinclude estopMsg.msg.html

(cl:defclass <estopMsg> (roslisp-msg-protocol:ros-message)
  ((Header
    :reader Header
    :initarg :Header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (isEstopped
    :reader isEstopped
    :initarg :isEstopped
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass estopMsg (<estopMsg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <estopMsg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'estopMsg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name beta_nodes-msg:<estopMsg> is deprecated: use beta_nodes-msg:estopMsg instead.")))

(cl:ensure-generic-function 'Header-val :lambda-list '(m))
(cl:defmethod Header-val ((m <estopMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:Header-val is deprecated.  Use beta_nodes-msg:Header instead.")
  (Header m))

(cl:ensure-generic-function 'isEstopped-val :lambda-list '(m))
(cl:defmethod isEstopped-val ((m <estopMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:isEstopped-val is deprecated.  Use beta_nodes-msg:isEstopped instead.")
  (isEstopped m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <estopMsg>) ostream)
  "Serializes a message object of type '<estopMsg>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'Header) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'isEstopped) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <estopMsg>) istream)
  "Deserializes a message object of type '<estopMsg>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'Header) istream)
    (cl:setf (cl:slot-value msg 'isEstopped) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<estopMsg>)))
  "Returns string type for a message object of type '<estopMsg>"
  "beta_nodes/estopMsg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'estopMsg)))
  "Returns string type for a message object of type 'estopMsg"
  "beta_nodes/estopMsg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<estopMsg>)))
  "Returns md5sum for a message object of type '<estopMsg>"
  "89970523909eb9ebf202b06133757daa")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'estopMsg)))
  "Returns md5sum for a message object of type 'estopMsg"
  "89970523909eb9ebf202b06133757daa")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<estopMsg>)))
  "Returns full string definition for message of type '<estopMsg>"
  (cl:format cl:nil "Header Header~%bool isEstopped~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'estopMsg)))
  "Returns full string definition for message of type 'estopMsg"
  (cl:format cl:nil "Header Header~%bool isEstopped~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <estopMsg>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'Header))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <estopMsg>))
  "Converts a ROS message object to a list"
  (cl:list 'estopMsg
    (cl:cons ':Header (Header msg))
    (cl:cons ':isEstopped (isEstopped msg))
))
