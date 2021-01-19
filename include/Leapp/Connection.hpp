#pragma once

#ifndef LEAPP_CONNECTION_HPP
#define LEAPP_CONNECTION_HPP

#include <cstdint>
#include <utility>

struct _LEAP_CONNECTION;
using LEAP_CONNECTION = _LEAP_CONNECTION*;

namespace Leapp {

enum class EventType {
  NONE = 0             /* eLeapEventType_None               */,
  CONNECTION           /* eLeapEventType_Connection         */,
  CONNECTION_LOST      /* eLeapEventType_ConnectionLost     */,
  DEVICE               /* eLeapEventType_Device             */,
  DEVICE_FAILURE       /* eLeapEventType_DeviceFailure      */,
  POLICY               /* eLeapEventType_Policy             */,
  TRACKING = 256       /* eLeapEventType_Tracking           */,
  IMAGE_REQUEST_ERROR  /* eLeapEventType_ImageRequestError  */,
  IMAGE_COMPLETE       /* eLeapEventType_ImageComplete      */,
  LOG_EVENT            /* eLeapEventType_LogEvent           */,
  DEVICE_LOST          /* eLeapEventType_DeviceLost         */,
  CONFIG_RESPONSE      /* eLeapEventType_ConfigResponse     */,
  CONFIG_CHANGE        /* eLeapEventType_ConfigChange       */,
  DEVICE_STATUS_CHANGE /* eLeapEventType_DeviceStatusChange */,
  DROPPED_FRAME        /* eLeapEventType_DroppedFrame       */,
  IMAGE                /* eLeapEventType_Image              */,
  POINT_MAPPING_CHANGE /* eLeapEventType_PointMappingChange */,
  LOG_EVENTS           /* eLeapEventType_LogEvents          */,
  HEAD_POSE            /* eLeapEventType_HeadPose           */
};

constexpr const char* recoverEventTypeStr(EventType type) {
  switch (type) {
    case EventType::NONE: default:        return "None";
    case EventType::CONNECTION:           return "Connection";
    case EventType::CONNECTION_LOST:      return "Connection lost";
    case EventType::DEVICE:               return "Device";
    case EventType::DEVICE_FAILURE:       return "Device failure";
    case EventType::POLICY:               return "Policy";
    case EventType::TRACKING:             return "Tracking";
    case EventType::IMAGE_REQUEST_ERROR:  return "Image request error";
    case EventType::IMAGE_COMPLETE:       return "Image complete";
    case EventType::LOG_EVENT:            return "Log event";
    case EventType::DEVICE_LOST:          return "Device lost";
    case EventType::CONFIG_RESPONSE:      return "Config response";
    case EventType::CONFIG_CHANGE:        return "Config change";
    case EventType::DEVICE_STATUS_CHANGE: return "Device status change";
    case EventType::DROPPED_FRAME:        return "Dropped frame";
    case EventType::IMAGE:                return "Image";
    case EventType::POINT_MAPPING_CHANGE: return "Point mapping change";
    case EventType::LOG_EVENTS:           return "Log events";
    case EventType::HEAD_POSE:            return "Head pose";
  }
}

/// Data resulting of each event.
struct EventData {
  EventType type;     ///< Event type.
  uint32_t handCount; ///< Number of hands detected.
};

class Connection {
public:
  Connection() noexcept;
  Connection(const Connection&) = delete;
  Connection(Connection&& connection) noexcept : m_connection{ std::exchange(connection.m_connection, nullptr) } {}

  LEAP_CONNECTION getConnection() const noexcept { return m_connection; }

  void open() const noexcept;
  EventData poll() const noexcept;
  void close() const noexcept;

  Connection& operator=(const Connection&) = delete;
  Connection& operator=(Connection&& connection) noexcept { std::swap(m_connection, connection.m_connection); return *this; }

  ~Connection();

private:
  LEAP_CONNECTION m_connection {};
};

} // namespace Leapp

#endif // LEAPP_CONNECTION_HPP
