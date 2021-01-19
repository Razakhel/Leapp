#pragma once

#ifndef LEAPP_DEVICE_HPP
#define LEAPP_DEVICE_HPP

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

struct _LEAP_DEVICE;
using LEAP_DEVICE = _LEAP_DEVICE*;

namespace Leapp {

class Connection;

/// Leap structure holding a device reference.
struct DeviceRef {
  void* handle; ///< Opaque device handle.
  uint32_t id; ///< Device index.
};

enum class DeviceStatus : uint32_t {
  STREAMING       = 1  /* eLeapDeviceStatus_Streaming      */, ///< Device currently streaming.
  PAUSED          = 2  /* eLeapDeviceStatus_Paused         */, ///< Device has been paused.
  ROBUST          = 4  /* eLeapDeviceStatus_Robust         */, ///< Device on robust mode in response to infrared interferences.
  SMUDGED         = 8  /* eLeapDeviceStatus_Smudged        */, ///< Device's window is smudged (dirty); tracking may be degraded.
  LOW_RESOURCE    = 16 /* eLeapDeviceStatus_LowResource    */, ///< Device on low-resource mode.

  UNKNOWN_FAILURE = 3'892'379'648 /* eLeapDeviceStatus_UnknownFailure */, ///< Unknown failure.
  BAD_CALIBRATION = 3'892'379'649 /* eLeapDeviceStatus_BadCalibration */, ///< Bad calibration.
  BAD_FIRMWARE    = 3'892'379'650 /* eLeapDeviceStatus_BadFirmware    */, ///< Corrupt firmware or missing required firmware update.
  BAD_TRANSPORT   = 3'892'379'651 /* eLeapDeviceStatus_BadTransport   */, ///< Falty USB connection.
  BAD_CONTROL     = 3'892'379'652 /* eLeapDeviceStatus_BadControl     */  ///< USB control interfaces failed to initialize.
};

/// Structure holding information on a device.
struct DeviceInfo {
  DeviceStatus status; ///< Device status.
  uint32_t baseline;   ///< Device baseline (distance between each camera lens) in micrometers.
  std::string serial;  ///< Serial number string.
  float horizontalFov; ///< Horizontal field of view in radians.
  float verticalFov;   ///< Vertical field of view in radians.
  uint32_t range;      ///< Maximum device range in micrometers.
};

class Device {
public:
  /// Opens a specific device based on the given reference structure.
  /// \see recoverDevices()
  /// \param ref Reference to open the device from.
  explicit Device(const DeviceRef& deviceRef) noexcept { open(deviceRef); }
  /// Opens the first detected device. To open a specific one, use the constructor taking a DeviceRef.
  /// \see Device(const DeviceRef&)
  /// \param connection Current opened connection.
  explicit Device(const Connection& connection);
  Device(const Device&) = delete;
  Device(Device&& device) noexcept : m_device{ std::exchange(device.m_device, nullptr) } {}

  LEAP_DEVICE getDevice() const noexcept { return m_device; }

  void open(const DeviceRef& deviceRef) noexcept;
  DeviceInfo recoverInfo() const;
  bool isStreaming() const { return (static_cast<uint32_t>(recoverInfo().status) & static_cast<uint32_t>(DeviceStatus::STREAMING)); }
  bool isPaused() const { return (static_cast<uint32_t>(recoverInfo().status) & static_cast<uint32_t>(DeviceStatus::PAUSED)); }
  bool hasError() const { return (static_cast<uint32_t>(recoverInfo().status) >= static_cast<uint32_t>(DeviceStatus::UNKNOWN_FAILURE)); }
  void close() noexcept;

  /// Recovers all connected devices.
  /// \param connection Current opened connection.
  /// \return List of device references.
  static std::vector<DeviceRef> recoverDevices(const Connection& connection);

  Device& operator=(const Device&) = delete;
  Device& operator=(Device&& device) noexcept { std::swap(m_device, device.m_device); return *this; }

  ~Device() { close(); }

private:
  LEAP_DEVICE m_device {};
};

} // namespace Leapp

#endif // LEAPP_DEVICE_HPP
