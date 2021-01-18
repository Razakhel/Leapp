#pragma once

#ifndef LEAPP_RESULT_HPP
#define LEAPP_RESULT_HPP

namespace Leapp {

enum class Result : uint32_t {
  SUCCESS                     = 0             /* eLeapRS_Success                  */,
  UNKNOWN_ERROR               = 3'791'716'352 /* eLeapRS_UnknownError             */,
  INVALID_ARGUMENT            = 3'791'716'353 /* eLeapRS_InvalidArgument          */,
  INSUFFICIENT_RESOURCES      = 3'791'716'354 /* eLeapRS_InsufficientResources    */,
  INSUFFICIENT_BUFFER         = 3'791'716'355 /* eLeapRS_InsufficientBuffer       */,
  TIMEOUT                     = 3'791'716'356 /* eLeapRS_Timeout                  */,
  NOT_CONNECTED               = 3'791'716'357 /* eLeapRS_NotConnected             */,
  HANDSHAKE_INCOMPLETE        = 3'791'716'358 /* eLeapRS_HandshakeIncomplete      */,
  BUFFER_SIZE_OVERFLOW        = 3'791'716'359 /* eLeapRS_BufferSizeOverflow       */,
  PROTOCOL_ERROR              = 3'791'716'360 /* eLeapRS_ProtocolError            */,
  INVALID_CLIENT_ID           = 3'791'716'361 /* eLeapRS_InvalidClientID          */,
  UNEXPECTED_CLOSED           = 3'791'716'362 /* eLeapRS_UnexpectedClosed         */,
  UNKNOWN_IMAGE_FRAME_REQUEST = 3'791'716'363 /* eLeapRS_UnknownImageFrameRequest */,
  UNKNOWN_TRACKING_FRAME_ID   = 3'791'716'364 /* eLeapRS_UnknownTrackingFrameID   */,
  ROUTINE_IS_NOT_SEER         = 3'791'716'365 /* eLeapRS_RoutineIsNotSeer         */,
  TIMESTAMP_TOO_EARLY         = 3'791'716'366 /* eLeapRS_TimestampTooEarly        */,
  CONCURRENT_POLL             = 3'791'716'367 /* eLeapRS_ConcurrentPoll           */,
  NOT_AVAILABLE               = 3'875'602'434 /* eLeapRS_NotAvailable             */,
  NOT_STREAMING               = 3'875'602'436 /* eLeapRS_NotStreaming             */,
  CANNOT_OPEN_DEVICE          = 3'875'602'437 /* eLeapRS_CannotOpenDevice         */
};

static constexpr const char* recoverResultStr(Result resultCode) {
  switch (resultCode) {
    case Result::SUCCESS:                     return "Success";
    case Result::UNKNOWN_ERROR: default:      return "Unknown error";
    case Result::INVALID_ARGUMENT:            return "Invalid argument";
    case Result::INSUFFICIENT_RESOURCES:      return "Insufficient resources";
    case Result::INSUFFICIENT_BUFFER:         return "Insufficient buffer";
    case Result::TIMEOUT:                     return "Timeout";
    case Result::NOT_CONNECTED:               return "Not connected";
    case Result::HANDSHAKE_INCOMPLETE:        return "Handshake incomplete";
    case Result::BUFFER_SIZE_OVERFLOW:        return "Buffer size overflow";
    case Result::PROTOCOL_ERROR:              return "Protocol error";
    case Result::INVALID_CLIENT_ID:           return "Invalid client ID";
    case Result::UNEXPECTED_CLOSED:           return "Unexpected closed";
    case Result::UNKNOWN_IMAGE_FRAME_REQUEST: return "Unknown image frame request";
    case Result::UNKNOWN_TRACKING_FRAME_ID:   return "Unknown tracking frame ID";
    case Result::ROUTINE_IS_NOT_SEER:         return "Routine is not seer";
    case Result::TIMESTAMP_TOO_EARLY:         return "Timestamp too early";
    case Result::CONCURRENT_POLL:             return "Concurrent poll";
    case Result::NOT_AVAILABLE:               return "Not available";
    case Result::NOT_STREAMING:               return "Not streaming";
    case Result::CANNOT_OPEN_DEVICE:          return "Cannot open device";
  }
}

} // namespace Leapp

#endif // LEAPP_RESULT_HPP
