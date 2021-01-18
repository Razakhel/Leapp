#include "Leapp/Connection.hpp"
#include "Leapp/Device.hpp"

#include <iostream>

int main() {
  Leapp::Connection connection;

  auto devices = Leapp::Device::recoverDevices(connection);

  if (devices.empty()) {
    std::cout << "No device detected\n";
  } else {
    std::cout << "Devices:\n";
    for (auto&& device : devices)
      std::cout << '\t' << device.id << '\n';
  }

  bool isTracking = false;

  while (true) {
    const Leapp::EventType eventType = connection.poll();

    // Print a message only when starting and stopping tracking, to avoid cluttering the console output
    if (!isTracking && eventType == Leapp::EventType::TRACKING) {
      std::cout << "Started tracking...\n";
      isTracking = true;
    } else if (isTracking && eventType != Leapp::EventType::TRACKING) {
      std::cout << "Stopped tracking\n";
      isTracking = false;
    }

    if (!isTracking)
      std::cout << "Status: " << Leapp::recoverEventTypeStr(eventType) << '\n';

    // If the connection has been severed (for example by unplugging the Leap Motion), stop the application
    if (eventType == Leapp::EventType::DEVICE_LOST)
      break;
  }

  return 0;
}
