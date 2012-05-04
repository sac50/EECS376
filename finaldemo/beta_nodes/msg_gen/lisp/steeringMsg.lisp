; Auto-generated. Do not edit!


(cl:in-package beta_nodes-msg)


;//! \htmlinclude steeringMsg.msg.html

(cl:defclass <steeringMsg> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (omega_cmd
    :reader omega_cmd
    :initarg :omega_cmd
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
    :initform 0.0)
   (heading
    :reader heading
    :initarg :heading
    :type cl:float
    :initform 0.0)
   (priority_approach
    :reader priority_approach
    :initarg :priority_approach
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass steeringMsg (<steeringMsg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <steeringMsg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'steeringMsg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name beta_nodes-msg:<steeringMsg> is deprecated: use beta_nodes-msg:steeringMsg instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <steeringMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:header-val is deprecated.  Use beta_nodes-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'omega_cmd-val :lambda-list '(m))
(cl:defmethod omega_cmd-val ((m <steeringMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:omega_cmd-val is deprecated.  Use beta_nodes-msg:omega_cmd instead.")
  (omega_cmd m))

(cl:ensure-generic-function 'posX-val :lambda-list '(m))
(cl:defmethod posX-val ((m <steeringMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:posX-val is deprecated.  Use beta_nodes-msg:posX instead.")
  (posX m))

(cl:ensure-generic-function 'posY-val :lambda-list '(m))
(cl:defmethod posY-val ((m <steeringMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:posY-val is deprecated.  Use beta_nodes-msg:posY instead.")
  (posY m))

(cl:ensure-generic-function 'heading-val :lambda-list '(m))
(cl:defmethod heading-val ((m <steeringMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:heading-val is deprecated.  Use beta_nodes-msg:heading instead.")
  (heading m))

(cl:ensure-generic-function 'priority_approach-val :lambda-list '(m))
(cl:defmethod priority_approach-val ((m <steeringMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beta_nodes-msg:priority_approach-val is deprecated.  Use beta_nodes-msg:priority_approach instead.")
  (priority_approach m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <steeringMsg>) ostream)
  "Serializes a message object of type '<steeringMsg>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'omega_cmd))))
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
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'heading))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'priority_approach) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <steeringMsg>) istream)
  "Deserializes a message object of type '<steeringMsg>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'omega_cmd) (roslisp-utils:decode-single-float-bits bits)))
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
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'heading) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:slot-value msg 'priority_approach) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<steeringMsg>)))
  "Returns string type for a message object of type '<steeringMsg>"
  "beta_nodes/steeringMsg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'steeringMsg)))
  "Returns string type for a message object of type 'steeringMsg"
  "beta_nodes/steeringMsg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<steeringMsg>)))
  "Returns md5sum for a message object of type '<steeringMsg>"
  "ba43803979c1f32a814a2b178a9b194b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'steeringMsg)))
  "Returns md5sum for a message object of type 'steeringMsg"
  "ba43803979c1f32a814a2b178a9b194b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<steeringMsg>)))
  "Returns full string definition for message of type '<steeringMsg>"
  (cl:format cl:nil "Header header~%float32 omega_cmd~%float32 posX~%float32 posY~%float32 heading~%bool priority_approach # to raise the priority when far enough away to warrant perpindicular approach~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'steeringMsg)))
  "Returns full string definition for message of type 'steeringMsg"
  (cl:format cl:nil "Header header~%float32 omega_cmd~%float32 posX~%float32 posY~%float32 heading~%bool priority_approach # to raise the priority when far enough away to warrant perpindicular approach~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <steeringMsg>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4
     4
     4
     4
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <steeringMsg>))
  "Converts a ROS message object to a list"
  (cl:list 'steeringMsg
    (cl:cons ':header (header msg))
    (cl:cons ':omega_cmd (omega_cmd msg))
    (cl:cons ':posX (posX msg))
    (cl:cons ':posY (posY msg))
    (cl:cons ':heading (heading msg))
    (cl:cons ':priority_approach (priority_approach msg))
))
