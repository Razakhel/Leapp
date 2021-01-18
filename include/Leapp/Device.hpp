#pragma once

#ifndef LEAPP_DEVICE_HPP
#define LEAPP_DEVICE_HPP

#include <cstdint>
#include <utility>
#include <vector>

struct _LEAP_DEVICE;
using LEAP_DEVICE = _LEAP_DEVICE*;

namespace Leapp {

class Connection;

/// Leap structure holding device information.
struct DeviceInfo {
  void* handle; ///< Opaque device handle.
  uint32_t id; ///< Device index.
};

class Device {
public:
  /// Opens a specific device based on the given information structure.
  /// \see recoverDevices()
  /// \param deviceInfo Information to open the device from.
  explicit Device(const DeviceInfo& info) { open(info); }
  /// Opens the first detected device. To open a specific one, use the constructor taking a DeviceInfo.
  /// \see Device(const DeviceInfo&)
  /// \param connection Current opened connection.
  explicit Device(const Connection& connection);
  Device(const Device&) = delete;
  Device(Device&& device) noexcept : m_device{ std::exchange(device.m_device, nullptr) } {}

  LEAP_DEVICE getDevice() const noexcept { return m_device; }

  void open(const DeviceInfo& info);

  /// Recovers all devices connected to the computer.
  /// \param connection Current opened connection.
  /// \return List of devices information.
  static std::vector<DeviceInfo> recoverDevices(const Connection& connection);

  Device& operator=(const Device&) = delete;
  Device& operator=(Device&& device) noexcept { std::swap(m_device, device.m_device); return *this; }

  ~Device();

private:
  LEAP_DEVICE m_device {};
};

} // namespace Leapp

#endif // LEAPP_DEVICE_HPP
