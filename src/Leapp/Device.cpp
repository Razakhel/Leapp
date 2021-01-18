#include "Leapp/Connection.hpp"
#include "Leapp/Device.hpp"
#include "Leapp/Leapp.hpp"
#include "Leapp/Result.hpp"

#include <iostream>

namespace Leapp {

Device::Device(const Connection& connection) {
  const std::vector<DeviceInfo> devices = recoverDevices(connection);

  if (devices.empty()) {
    std::cerr << "[Leapp] Error: No device found with the given connection\n";
    return;
  }

  open(devices.front());
}

void Device::open(const DeviceInfo& info) {
  const auto deviceOpenResult = static_cast<Result>(LeapOpenDevice(*reinterpret_cast<const LEAP_DEVICE_REF*>(&info), &m_device));

  if (deviceOpenResult != Result::SUCCESS)
    std::cerr << "[Leapp] Error: Failed to open device (" << recoverResultStr(deviceOpenResult) << ")\n";
}

std::vector<DeviceInfo> Device::recoverDevices(const Connection& connection) {
  uint32_t deviceCount {};
  const auto deviceCountResult = static_cast<Result>(LeapGetDeviceList(connection.getConnection(), nullptr, &deviceCount));

  if (deviceCountResult != Result::SUCCESS)
    std::cerr << "[Leapp] Error: Failed to recover the device count (" << recoverResultStr(deviceCountResult) << ")\n";

  if (deviceCount == 0)
    return {};

  std::vector<DeviceInfo> deviceRefs;
  deviceRefs.resize(deviceCount);

  const auto deviceListResult = static_cast<Result>(LeapGetDeviceList(connection.getConnection(),
                                                                      reinterpret_cast<LEAP_DEVICE_REF*>(deviceRefs.data()),
                                                                      &deviceCount));

  if (deviceListResult != Result::SUCCESS)
    std::cerr << "[Leapp] Error: Failed to recover devices (" << recoverResultStr(deviceListResult) << ")\n";

  return deviceRefs;
}

Device::~Device() {
  LeapCloseDevice(m_device);
}

} // namespace Leapp
