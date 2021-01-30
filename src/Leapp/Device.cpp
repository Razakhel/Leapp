#include "Leapp/Connection.hpp"
#include "Leapp/Device.hpp"
#include "Leapp/Result.hpp"

#include <LeapC.h>

#include <cassert>
#include <iostream>

namespace Leapp {

Device::Device(const Connection& connection) {
  const std::vector<DeviceRef> devices = recoverDevices(connection);

  if (devices.empty()) {
    std::cerr << "[Leapp] Error: No device found with the given connection\n";
    return;
  }

  open(devices.front());
}

void Device::open(const DeviceRef& deviceRef) noexcept {
  const auto deviceOpenResult = static_cast<Result>(LeapOpenDevice(*reinterpret_cast<const LEAP_DEVICE_REF*>(&deviceRef), &m_device));

  if (deviceOpenResult != Result::SUCCESS)
    std::cerr << "[Leapp] Error: Failed to open device (" << recoverResultStr(deviceOpenResult) << ")\n";
}

DeviceInfo Device::recoverInfo() const {
  assert("Error: Device is not opened." && m_device);

  LEAP_DEVICE_INFO deviceInfo {};
  auto deviceInfoResult = static_cast<Result>(LeapGetDeviceInfo(m_device, &deviceInfo));

  if (deviceInfoResult == Result::INSUFFICIENT_BUFFER) { // Should always happen
    deviceInfo.serial = new char[deviceInfo.serial_length];
    deviceInfoResult  = static_cast<Result>(LeapGetDeviceInfo(m_device, &deviceInfo));
  }

  if (deviceInfoResult != Result::SUCCESS)
    std::cerr << "[Leapp] Error: Failed to recover device info (" << recoverResultStr(deviceInfoResult) << ")\n";

  DeviceInfo res {};
  res.status        = static_cast<DeviceStatus>(deviceInfo.status);
  res.baseline      = deviceInfo.baseline;
  res.serial        = deviceInfo.serial;
  res.horizontalFov = deviceInfo.h_fov;
  res.verticalFov   = deviceInfo.v_fov;
  res.range         = deviceInfo.range;

  delete[] deviceInfo.serial;

  return res;
}

void Device::close() noexcept {
  if (m_device == nullptr)
    return;

  LeapCloseDevice(m_device);
  m_device = nullptr;
}

std::vector<DeviceRef> Device::recoverDevices(const Connection& connection) {
  uint32_t deviceCount {};
  const auto deviceCountResult = static_cast<Result>(LeapGetDeviceList(connection.getConnection(), nullptr, &deviceCount));

  if (deviceCountResult != Result::SUCCESS)
    std::cerr << "[Leapp] Error: Failed to recover the device count (" << recoverResultStr(deviceCountResult) << ")\n";

  if (deviceCount == 0)
    return {};

  std::vector<DeviceRef> deviceRefs;
  deviceRefs.resize(deviceCount);

  const auto deviceListResult = static_cast<Result>(LeapGetDeviceList(connection.getConnection(),
                                                                      reinterpret_cast<LEAP_DEVICE_REF*>(deviceRefs.data()),
                                                                      &deviceCount));

  if (deviceListResult != Result::SUCCESS)
    std::cerr << "[Leapp] Error: Failed to recover devices (" << recoverResultStr(deviceListResult) << ")\n";

  return deviceRefs;
}

} // namespace Leapp
