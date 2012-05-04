/* Auto-generated by genmsg_cpp for file /home/jinx/ROSCode/beta_nodes/msg/PathSegment.msg */
#ifndef BETA_NODES_MESSAGE_PATHSEGMENT_H
#define BETA_NODES_MESSAGE_PATHSEGMENT_H
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/time.h"

#include "ros/macros.h"

#include "ros/assert.h"

#include "std_msgs/Header.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Quaternion.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Twist.h"

namespace beta_nodes
{
template <class ContainerAllocator>
struct PathSegment_ {
  typedef PathSegment_<ContainerAllocator> Type;

  PathSegment_()
  : header()
  , seg_type(0)
  , priority(0)
  , seg_number(0)
  , seg_length(0.0)
  , init_point()
  , ref_point()
  , init_tan_angle()
  , seg_psi(0.0)
  , curvature(0.0)
  , max_speeds()
  , min_speeds()
  , accel_limit(0.0)
  , decel_limit(0.0)
  {
  }

  PathSegment_(const ContainerAllocator& _alloc)
  : header(_alloc)
  , seg_type(0)
  , priority(0)
  , seg_number(0)
  , seg_length(0.0)
  , init_point(_alloc)
  , ref_point(_alloc)
  , init_tan_angle(_alloc)
  , seg_psi(0.0)
  , curvature(0.0)
  , max_speeds(_alloc)
  , min_speeds(_alloc)
  , accel_limit(0.0)
  , decel_limit(0.0)
  {
  }

  typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
   ::std_msgs::Header_<ContainerAllocator>  header;

  typedef int8_t _seg_type_type;
  int8_t seg_type;

  typedef int8_t _priority_type;
  int8_t priority;

  typedef uint32_t _seg_number_type;
  uint32_t seg_number;

  typedef double _seg_length_type;
  double seg_length;

  typedef  ::geometry_msgs::Point_<ContainerAllocator>  _init_point_type;
   ::geometry_msgs::Point_<ContainerAllocator>  init_point;

  typedef  ::geometry_msgs::Point_<ContainerAllocator>  _ref_point_type;
   ::geometry_msgs::Point_<ContainerAllocator>  ref_point;

  typedef  ::geometry_msgs::Quaternion_<ContainerAllocator>  _init_tan_angle_type;
   ::geometry_msgs::Quaternion_<ContainerAllocator>  init_tan_angle;

  typedef float _seg_psi_type;
  float seg_psi;

  typedef double _curvature_type;
  double curvature;

  typedef  ::geometry_msgs::Twist_<ContainerAllocator>  _max_speeds_type;
   ::geometry_msgs::Twist_<ContainerAllocator>  max_speeds;

  typedef  ::geometry_msgs::Twist_<ContainerAllocator>  _min_speeds_type;
   ::geometry_msgs::Twist_<ContainerAllocator>  min_speeds;

  typedef double _accel_limit_type;
  double accel_limit;

  typedef double _decel_limit_type;
  double decel_limit;

  enum { LINE = 1 };
  enum { ARC = 2 };
  enum { SPIN_IN_PLACE = 3 };

private:
  static const char* __s_getDataType_() { return "beta_nodes/PathSegment"; }
public:
  ROS_DEPRECATED static const std::string __s_getDataType() { return __s_getDataType_(); }

  ROS_DEPRECATED const std::string __getDataType() const { return __s_getDataType_(); }

private:
  static const char* __s_getMD5Sum_() { return "fc3d47c3da0120062a7ad316a732ef6e"; }
public:
  ROS_DEPRECATED static const std::string __s_getMD5Sum() { return __s_getMD5Sum_(); }

  ROS_DEPRECATED const std::string __getMD5Sum() const { return __s_getMD5Sum_(); }

private:
  static const char* __s_getMessageDefinition_() { return "#Reference frame that the following coordinates should be interpreted relative to and timestamp to use when transforming\n\
Header header\n\
\n\
#Segment type enums\n\
int8 LINE = 1\n\
int8 ARC = 2\n\
int8 SPIN_IN_PLACE = 3\n\
\n\
#Segment type\n\
int8 seg_type\n\
\n\
#priority flag\n\
int8 priority\n\
\n\
#Segment number\n\
uint32 seg_number\n\
\n\
#Segment length\n\
float64 seg_length\n\
\n\
#Reference point\n\
geometry_msgs/Point init_point\n\
geometry_msgs/Point ref_point\n\
geometry_msgs/Quaternion init_tan_angle\n\
float32 seg_psi\n\
\n\
#Curvature\n\
float64 curvature\n\
\n\
#Speed limits for this segment\n\
geometry_msgs/Twist max_speeds\n\
geometry_msgs/Twist min_speeds\n\
\n\
#Acceleration limit for this segment (m/s^2 for lines/arcs, rads/s^2 for spin-in-place)\n\
float64 accel_limit\n\
float64 decel_limit\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.secs: seconds (stamp_secs) since epoch\n\
# * stamp.nsecs: nanoseconds since stamp_secs\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Point\n\
# This contains the position of a point in free space\n\
float64 x\n\
float64 y\n\
float64 z\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Quaternion\n\
# This represents an orientation in free space in quaternion form.\n\
\n\
float64 x\n\
float64 y\n\
float64 z\n\
float64 w\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Twist\n\
# This expresses velocity in free space broken into it's linear and angular parts. \n\
Vector3  linear\n\
Vector3  angular\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Vector3\n\
# This represents a vector in free space. \n\
\n\
float64 x\n\
float64 y\n\
float64 z\n\
"; }
public:
  ROS_DEPRECATED static const std::string __s_getMessageDefinition() { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED const std::string __getMessageDefinition() const { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED virtual uint8_t *serialize(uint8_t *write_ptr, uint32_t seq) const
  {
    ros::serialization::OStream stream(write_ptr, 1000000000);
    ros::serialization::serialize(stream, header);
    ros::serialization::serialize(stream, seg_type);
    ros::serialization::serialize(stream, priority);
    ros::serialization::serialize(stream, seg_number);
    ros::serialization::serialize(stream, seg_length);
    ros::serialization::serialize(stream, init_point);
    ros::serialization::serialize(stream, ref_point);
    ros::serialization::serialize(stream, init_tan_angle);
    ros::serialization::serialize(stream, seg_psi);
    ros::serialization::serialize(stream, curvature);
    ros::serialization::serialize(stream, max_speeds);
    ros::serialization::serialize(stream, min_speeds);
    ros::serialization::serialize(stream, accel_limit);
    ros::serialization::serialize(stream, decel_limit);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint8_t *deserialize(uint8_t *read_ptr)
  {
    ros::serialization::IStream stream(read_ptr, 1000000000);
    ros::serialization::deserialize(stream, header);
    ros::serialization::deserialize(stream, seg_type);
    ros::serialization::deserialize(stream, priority);
    ros::serialization::deserialize(stream, seg_number);
    ros::serialization::deserialize(stream, seg_length);
    ros::serialization::deserialize(stream, init_point);
    ros::serialization::deserialize(stream, ref_point);
    ros::serialization::deserialize(stream, init_tan_angle);
    ros::serialization::deserialize(stream, seg_psi);
    ros::serialization::deserialize(stream, curvature);
    ros::serialization::deserialize(stream, max_speeds);
    ros::serialization::deserialize(stream, min_speeds);
    ros::serialization::deserialize(stream, accel_limit);
    ros::serialization::deserialize(stream, decel_limit);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint32_t serializationLength() const
  {
    uint32_t size = 0;
    size += ros::serialization::serializationLength(header);
    size += ros::serialization::serializationLength(seg_type);
    size += ros::serialization::serializationLength(priority);
    size += ros::serialization::serializationLength(seg_number);
    size += ros::serialization::serializationLength(seg_length);
    size += ros::serialization::serializationLength(init_point);
    size += ros::serialization::serializationLength(ref_point);
    size += ros::serialization::serializationLength(init_tan_angle);
    size += ros::serialization::serializationLength(seg_psi);
    size += ros::serialization::serializationLength(curvature);
    size += ros::serialization::serializationLength(max_speeds);
    size += ros::serialization::serializationLength(min_speeds);
    size += ros::serialization::serializationLength(accel_limit);
    size += ros::serialization::serializationLength(decel_limit);
    return size;
  }

  typedef boost::shared_ptr< ::beta_nodes::PathSegment_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::beta_nodes::PathSegment_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct PathSegment
typedef  ::beta_nodes::PathSegment_<std::allocator<void> > PathSegment;

typedef boost::shared_ptr< ::beta_nodes::PathSegment> PathSegmentPtr;
typedef boost::shared_ptr< ::beta_nodes::PathSegment const> PathSegmentConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::beta_nodes::PathSegment_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::beta_nodes::PathSegment_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace beta_nodes

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::beta_nodes::PathSegment_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::beta_nodes::PathSegment_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::beta_nodes::PathSegment_<ContainerAllocator> > {
  static const char* value() 
  {
    return "fc3d47c3da0120062a7ad316a732ef6e";
  }

  static const char* value(const  ::beta_nodes::PathSegment_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0xfc3d47c3da012006ULL;
  static const uint64_t static_value2 = 0x2a7ad316a732ef6eULL;
};

template<class ContainerAllocator>
struct DataType< ::beta_nodes::PathSegment_<ContainerAllocator> > {
  static const char* value() 
  {
    return "beta_nodes/PathSegment";
  }

  static const char* value(const  ::beta_nodes::PathSegment_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::beta_nodes::PathSegment_<ContainerAllocator> > {
  static const char* value() 
  {
    return "#Reference frame that the following coordinates should be interpreted relative to and timestamp to use when transforming\n\
Header header\n\
\n\
#Segment type enums\n\
int8 LINE = 1\n\
int8 ARC = 2\n\
int8 SPIN_IN_PLACE = 3\n\
\n\
#Segment type\n\
int8 seg_type\n\
\n\
#priority flag\n\
int8 priority\n\
\n\
#Segment number\n\
uint32 seg_number\n\
\n\
#Segment length\n\
float64 seg_length\n\
\n\
#Reference point\n\
geometry_msgs/Point init_point\n\
geometry_msgs/Point ref_point\n\
geometry_msgs/Quaternion init_tan_angle\n\
float32 seg_psi\n\
\n\
#Curvature\n\
float64 curvature\n\
\n\
#Speed limits for this segment\n\
geometry_msgs/Twist max_speeds\n\
geometry_msgs/Twist min_speeds\n\
\n\
#Acceleration limit for this segment (m/s^2 for lines/arcs, rads/s^2 for spin-in-place)\n\
float64 accel_limit\n\
float64 decel_limit\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.secs: seconds (stamp_secs) since epoch\n\
# * stamp.nsecs: nanoseconds since stamp_secs\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Point\n\
# This contains the position of a point in free space\n\
float64 x\n\
float64 y\n\
float64 z\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Quaternion\n\
# This represents an orientation in free space in quaternion form.\n\
\n\
float64 x\n\
float64 y\n\
float64 z\n\
float64 w\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Twist\n\
# This expresses velocity in free space broken into it's linear and angular parts. \n\
Vector3  linear\n\
Vector3  angular\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Vector3\n\
# This represents a vector in free space. \n\
\n\
float64 x\n\
float64 y\n\
float64 z\n\
";
  }

  static const char* value(const  ::beta_nodes::PathSegment_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct HasHeader< ::beta_nodes::PathSegment_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct HasHeader< const ::beta_nodes::PathSegment_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::beta_nodes::PathSegment_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.header);
    stream.next(m.seg_type);
    stream.next(m.priority);
    stream.next(m.seg_number);
    stream.next(m.seg_length);
    stream.next(m.init_point);
    stream.next(m.ref_point);
    stream.next(m.init_tan_angle);
    stream.next(m.seg_psi);
    stream.next(m.curvature);
    stream.next(m.max_speeds);
    stream.next(m.min_speeds);
    stream.next(m.accel_limit);
    stream.next(m.decel_limit);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct PathSegment_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::beta_nodes::PathSegment_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::beta_nodes::PathSegment_<ContainerAllocator> & v) 
  {
    s << indent << "header: ";
s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "seg_type: ";
    Printer<int8_t>::stream(s, indent + "  ", v.seg_type);
    s << indent << "priority: ";
    Printer<int8_t>::stream(s, indent + "  ", v.priority);
    s << indent << "seg_number: ";
    Printer<uint32_t>::stream(s, indent + "  ", v.seg_number);
    s << indent << "seg_length: ";
    Printer<double>::stream(s, indent + "  ", v.seg_length);
    s << indent << "init_point: ";
s << std::endl;
    Printer< ::geometry_msgs::Point_<ContainerAllocator> >::stream(s, indent + "  ", v.init_point);
    s << indent << "ref_point: ";
s << std::endl;
    Printer< ::geometry_msgs::Point_<ContainerAllocator> >::stream(s, indent + "  ", v.ref_point);
    s << indent << "init_tan_angle: ";
s << std::endl;
    Printer< ::geometry_msgs::Quaternion_<ContainerAllocator> >::stream(s, indent + "  ", v.init_tan_angle);
    s << indent << "seg_psi: ";
    Printer<float>::stream(s, indent + "  ", v.seg_psi);
    s << indent << "curvature: ";
    Printer<double>::stream(s, indent + "  ", v.curvature);
    s << indent << "max_speeds: ";
s << std::endl;
    Printer< ::geometry_msgs::Twist_<ContainerAllocator> >::stream(s, indent + "  ", v.max_speeds);
    s << indent << "min_speeds: ";
s << std::endl;
    Printer< ::geometry_msgs::Twist_<ContainerAllocator> >::stream(s, indent + "  ", v.min_speeds);
    s << indent << "accel_limit: ";
    Printer<double>::stream(s, indent + "  ", v.accel_limit);
    s << indent << "decel_limit: ";
    Printer<double>::stream(s, indent + "  ", v.decel_limit);
  }
};


} // namespace message_operations
} // namespace ros

#endif // BETA_NODES_MESSAGE_PATHSEGMENT_H

