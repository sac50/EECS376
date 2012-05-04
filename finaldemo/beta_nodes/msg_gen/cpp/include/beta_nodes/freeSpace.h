/* Auto-generated by genmsg_cpp for file /home/jinx/ROSCode/beta_nodes/msg/freeSpace.msg */
#ifndef BETA_NODES_MESSAGE_FREESPACE_H
#define BETA_NODES_MESSAGE_FREESPACE_H
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
#include "geometry_msgs/PointStamped.h"

namespace beta_nodes
{
template <class ContainerAllocator>
struct freeSpace_ {
  typedef freeSpace_<ContainerAllocator> Type;

  freeSpace_()
  : header()
  , point()
  , obstacleFound(false)
  {
  }

  freeSpace_(const ContainerAllocator& _alloc)
  : header(_alloc)
  , point(_alloc)
  , obstacleFound(false)
  {
  }

  typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
   ::std_msgs::Header_<ContainerAllocator>  header;

  typedef  ::geometry_msgs::PointStamped_<ContainerAllocator>  _point_type;
   ::geometry_msgs::PointStamped_<ContainerAllocator>  point;

  typedef uint8_t _obstacleFound_type;
  uint8_t obstacleFound;


private:
  static const char* __s_getDataType_() { return "beta_nodes/freeSpace"; }
public:
  ROS_DEPRECATED static const std::string __s_getDataType() { return __s_getDataType_(); }

  ROS_DEPRECATED const std::string __getDataType() const { return __s_getDataType_(); }

private:
  static const char* __s_getMD5Sum_() { return "fc557d704f107471807774c96211022d"; }
public:
  ROS_DEPRECATED static const std::string __s_getMD5Sum() { return __s_getMD5Sum_(); }

  ROS_DEPRECATED const std::string __getMD5Sum() const { return __s_getMD5Sum_(); }

private:
  static const char* __s_getMessageDefinition_() { return "#Message the communicates a point of where to go to dodge obstacles and a flag for if there are any obstacles \n\
Header header\n\
\n\
#Point to navigate around the obstacle\n\
geometry_msgs/PointStamped point\n\
\n\
#Flag for if an obstacle exists\n\
bool obstacleFound\n\
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
MSG: geometry_msgs/PointStamped\n\
# This represents a Point with reference coordinate frame and timestamp\n\
Header header\n\
Point point\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Point\n\
# This contains the position of a point in free space\n\
float64 x\n\
float64 y\n\
float64 z\n\
\n\
"; }
public:
  ROS_DEPRECATED static const std::string __s_getMessageDefinition() { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED const std::string __getMessageDefinition() const { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED virtual uint8_t *serialize(uint8_t *write_ptr, uint32_t seq) const
  {
    ros::serialization::OStream stream(write_ptr, 1000000000);
    ros::serialization::serialize(stream, header);
    ros::serialization::serialize(stream, point);
    ros::serialization::serialize(stream, obstacleFound);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint8_t *deserialize(uint8_t *read_ptr)
  {
    ros::serialization::IStream stream(read_ptr, 1000000000);
    ros::serialization::deserialize(stream, header);
    ros::serialization::deserialize(stream, point);
    ros::serialization::deserialize(stream, obstacleFound);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint32_t serializationLength() const
  {
    uint32_t size = 0;
    size += ros::serialization::serializationLength(header);
    size += ros::serialization::serializationLength(point);
    size += ros::serialization::serializationLength(obstacleFound);
    return size;
  }

  typedef boost::shared_ptr< ::beta_nodes::freeSpace_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::beta_nodes::freeSpace_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct freeSpace
typedef  ::beta_nodes::freeSpace_<std::allocator<void> > freeSpace;

typedef boost::shared_ptr< ::beta_nodes::freeSpace> freeSpacePtr;
typedef boost::shared_ptr< ::beta_nodes::freeSpace const> freeSpaceConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::beta_nodes::freeSpace_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::beta_nodes::freeSpace_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace beta_nodes

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::beta_nodes::freeSpace_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::beta_nodes::freeSpace_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::beta_nodes::freeSpace_<ContainerAllocator> > {
  static const char* value() 
  {
    return "fc557d704f107471807774c96211022d";
  }

  static const char* value(const  ::beta_nodes::freeSpace_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0xfc557d704f107471ULL;
  static const uint64_t static_value2 = 0x807774c96211022dULL;
};

template<class ContainerAllocator>
struct DataType< ::beta_nodes::freeSpace_<ContainerAllocator> > {
  static const char* value() 
  {
    return "beta_nodes/freeSpace";
  }

  static const char* value(const  ::beta_nodes::freeSpace_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::beta_nodes::freeSpace_<ContainerAllocator> > {
  static const char* value() 
  {
    return "#Message the communicates a point of where to go to dodge obstacles and a flag for if there are any obstacles \n\
Header header\n\
\n\
#Point to navigate around the obstacle\n\
geometry_msgs/PointStamped point\n\
\n\
#Flag for if an obstacle exists\n\
bool obstacleFound\n\
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
MSG: geometry_msgs/PointStamped\n\
# This represents a Point with reference coordinate frame and timestamp\n\
Header header\n\
Point point\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Point\n\
# This contains the position of a point in free space\n\
float64 x\n\
float64 y\n\
float64 z\n\
\n\
";
  }

  static const char* value(const  ::beta_nodes::freeSpace_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct HasHeader< ::beta_nodes::freeSpace_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct HasHeader< const ::beta_nodes::freeSpace_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::beta_nodes::freeSpace_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.header);
    stream.next(m.point);
    stream.next(m.obstacleFound);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct freeSpace_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::beta_nodes::freeSpace_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::beta_nodes::freeSpace_<ContainerAllocator> & v) 
  {
    s << indent << "header: ";
s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "point: ";
s << std::endl;
    Printer< ::geometry_msgs::PointStamped_<ContainerAllocator> >::stream(s, indent + "  ", v.point);
    s << indent << "obstacleFound: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.obstacleFound);
  }
};


} // namespace message_operations
} // namespace ros

#endif // BETA_NODES_MESSAGE_FREESPACE_H

