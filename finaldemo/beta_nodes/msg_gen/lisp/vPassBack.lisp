; Auto-generated. Do not edit!


(cl:in-package beta_nodes-msg)


;//! \htmlinclude vPassBack.msg.html

(cl:defclass <vPassBack> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (vPast
    :reader vPast
    :initarg :vPast
    :type cl:float
    :initform 0.0)
   (posX
    :reader posX
    :initarg :posX
    :type cl:float
    :initform 0.0)
   (posY
    :reader posY
    :initarg :posY
    :type cl:float
    :initform 0.0))
)

(cl:defclass vPassBack (<vPassBack>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <vPassBack>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'vPassBack)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name beta_nodes-msg:<vPassBack> is deprecated: use beta_nodes-msg:vPassBack instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <vPassBack>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:header-val is deprecated.  Use beta_nodes-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'vPast-val :lambda-list '(m))
(cl:defmethod vPast-val ((m <vPassBack>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:vPast-val is deprecated.  Use beta_nodes-msg:vPast instead.")
  (vPast m))

(cl:ensure-generic-function 'posX-val :lambda-list '(m))
(cl:defmethod posX-val ((m <vPassBack>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:posX-val is deprecated.  Use beta_nodes-msg:posX instead.")
  (posX m))

(cl:ensure-generic-function 'posY-val :lambda-list '(m))
(cl:defmethod posY-val ((m <vPassBack>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:posY-val is deprecated.  Use beta_nodes-msg:posY instead.")
  (posY m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <vPassBack>) ostream)
  "Serializes a message object of type '<vPassBack>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vPast))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'posX))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'posY))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <vPassBack>) istream)
  "Deserializes a message object of type '<vPassBack>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vPast) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'posX) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'posY) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<vPassBack>)))
  "Returns string type for a message object of type '<vPassBack>"
  "beta_nodes/vPassBack")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'vPassBack)))
  "Returns string type for a message object of type 'vPassBack"
  "beta_nodes/vPassBack")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<vPassBack>)))
  "Returns md5sum for a message object of type '<vPassBack>"
  "1287931b7788a4e822865ae2d3624897")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'vPassBack)))
  "Returns md5sum for a message object of type 'vPassBack"
  "1287931b7788a4e822865ae2d3624897")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<vPassBack>)))
  "Returns full string definition for message of type '<vPassBack>"
  (cl:format cl:nil "Header header~%float32 vPast~%float32 posX~%float32 posY~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'vPassBack)))
  "Returns full string definition for message of type 'vPassBack"
  (cl:format cl:nil "Header header~%float32 vPast~%float32 posX~%float32 posY~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <vPassBack>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <vPassBack>))
  "Converts a ROS message object to a list"
  (cl:list 'vPassBack
    (cl:cons ':header (header msg))
    (cl:cons ':vPast (vPast msg))
    (cl:cons ':posX (posX msg))
    (cl:cons ':posY (posY msg))
))
