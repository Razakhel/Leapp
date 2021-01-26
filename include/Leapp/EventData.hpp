#pragma once

#ifndef LEAPP_EVENTDATA_HPP
#define LEAPP_EVENTDATA_HPP

#include "Leapp/Hand.hpp"

#include <cstdint>
#include <vector>

struct _LEAP_CONNECTION_MESSAGE;
using LEAP_CONNECTION_MESSAGE = _LEAP_CONNECTION_MESSAGE;

struct _LEAP_HAND;
using LEAP_HAND = _LEAP_HAND;

struct _LEAP_DIGIT;
using LEAP_DIGIT = _LEAP_DIGIT;

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
class EventData {
public:
  explicit EventData(const LEAP_CONNECTION_MESSAGE& message);

  EventType getType() const noexcept { return m_type; }
  const Hand& getHand(uint32_t handIndex) const noexcept { return m_hands[handIndex]; }
  uint32_t getHandCount() const noexcept { return static_cast<uint32_t>(m_hands.size()); }

private:
  void addHands(const LEAP_HAND* hands, uint32_t handCount);
  void addFingers(Hand& hand, const LEAP_DIGIT (&fingers)[5]);

  EventType m_type {};          ///< Event type.
  std::vector<Hand> m_hands {}; ///< Hands detected.
};

} // namespace Leapp

#endif // LEAPP_EVENTDATA_HPP
