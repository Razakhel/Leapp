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

/// Structure holding information on a device.
struct DeviceInfo {
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
  explicit Device(const DeviceRef& deviceRef) { open(deviceRef); }
  /// Opens the first detected device. To open a specific one, use the constructor taking a DeviceRef.
  /// \see Device(const DeviceRef&)
  /// \param connection Current opened connection.
  explicit Device(const Connection& connection);
  Device(const Device&) = delete;
  Device(Device&& device) noexcept : m_device{ std::exchange(device.m_device, nullptr) } {}

  LEAP_DEVICE getDevice() const noexcept { return m_device; }

  void open(const DeviceRef& deviceRef);
  DeviceInfo recoverInfo() const;
  void close();

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
