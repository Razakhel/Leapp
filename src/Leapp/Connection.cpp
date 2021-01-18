#include "Leapp/Connection.hpp"
#include "Leapp/Leapp.hpp"

#include <iostream>

namespace Leapp {

namespace {

inline constexpr const char* recoverLeapErrorStr(eLeapRS errorCode) {
  switch (errorCode) {
    case eLeapRS_Success:                  return "Success";
    case eLeapRS_UnknownError: default:    return "Unknown error";
    case eLeapRS_InvalidArgument:          return "Invalid argument";
    case eLeapRS_InsufficientResources:    return "Insufficient resources";
    case eLeapRS_InsufficientBuffer:       return "Insufficient buffer";
    case eLeapRS_Timeout:                  return "Timeout";
    case eLeapRS_NotConnected:             return "Not connected";
    case eLeapRS_HandshakeIncomplete:      return "Handshake incomplete";
    case eLeapRS_BufferSizeOverflow:       return "Buffer size overflow";
    case eLeapRS_ProtocolError:            return "Protocol error";
    case eLeapRS_InvalidClientID:          return "Invalid client ID";
    case eLeapRS_UnexpectedClosed:         return "Unexpected closed";
    case eLeapRS_UnknownImageFrameRequest: return "Unknown image frame request";
    case eLeapRS_UnknownTrackingFrameID:   return "Unknown tracking frame ID";
    case eLeapRS_RoutineIsNotSeer:         return "Routine is not seer";
    case eLeapRS_TimestampTooEarly:        return "Timestamp too early";
    case eLeapRS_ConcurrentPoll:           return "Concurrent poll";
    case eLeapRS_NotAvailable:             return "Not available";
    case eLeapRS_NotStreaming:             return "Not streaming";
    case eLeapRS_CannotOpenDevice:         return "Cannot open device";
  }
}

} // namespace

Connection::Connection() {
  const eLeapRS connectionStatus = LeapCreateConnection(nullptr, &m_connection);

  if (connectionStatus != eLeapRS_Success)
    std::cerr << "[Leapp] Error: Failed to create connection (" << recoverLeapErrorStr(connectionStatus) << ')';

  open();
  poll(); // Polling once to complete connection
}

void Connection::open() const {
  const eLeapRS connectionStatus = LeapOpenConnection(m_connection);

  if (connectionStatus != eLeapRS_Success)
    std::cerr << "[Leapp] Error: Failed to open connection (" << recoverLeapErrorStr(connectionStatus) << ')';
}

EventType Connection::poll() const {
  LEAP_CONNECTION_MESSAGE message {};
  const eLeapRS pollStatus = LeapPollConnection(m_connection, 250, &message);

  if (pollStatus != eLeapRS_Success)
    std::cerr << "[Leapp] Error: Failed to poll connection (" << recoverLeapErrorStr(pollStatus) << ')';

  return static_cast<EventType>(message.type);
}

void Connection::close() const {
  LeapCloseConnection(m_connection);
}

Connection::~Connection() {
  close();
  LeapDestroyConnection(m_connection);
}

} // namespace Leap
