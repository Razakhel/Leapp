#include "Leapp/Connection.hpp"
#include "Leapp/Device.hpp"
#include "Leapp/EventData.hpp"

#include <iostream>

int main() {
  Leapp::Connection connection;

  auto deviceRefs = Leapp::Device::recoverDevices(connection);

  if (deviceRefs.empty()) {
    std::cout << "No device detected\n";
  } else {
    std::cout << "Devices:\n";

    for (auto&& deviceRef : deviceRefs) {
      const Leapp::Device device(deviceRef);
      const Leapp::DeviceInfo deviceInfo = device.recoverInfo();

      std::cout << "- Device " << deviceRef.id << ":\n";
      std::cout << "\tBaseline:   " << deviceInfo.baseline << '\n';
      std::cout << "\tSerial:     " << deviceInfo.serial << '\n';
      std::cout << "\tHoriz. FoV: " << deviceInfo.horizontalFov << '\n';
      std::cout << "\tVert. FoV:  " << deviceInfo.verticalFov << '\n';
      std::cout << "\tRange:      " << deviceInfo.range << "\n\n";
    }
  }

  bool isTracking    = false;
  uint32_t handCount = 0;

  while (true) {
    const Leapp::EventData eventData = connection.poll();
    const Leapp::EventType eventType = eventData.getType();

    // Print a message only when starting and stopping tracking, to avoid cluttering the console output
    if (!isTracking && eventType == Leapp::EventType::TRACKING) {
      std::cout << "Started tracking...\n";
      isTracking = true;
    } else if (isTracking && eventType != Leapp::EventType::TRACKING) {
      std::cout << "Stopped tracking\n";
      isTracking = false;
    }

    if (handCount != eventData.getHandCount()) {
      handCount = eventData.getHandCount();
      std::cout << "Detected " << handCount << " hand(s)\n";
    }

    if (!isTracking)
      std::cout << "Status: " << Leapp::recoverEventTypeStr(eventType) << '\n';

    // If the connection has been severed (for example by unplugging the Leap Motion), stop the application
    if (eventType == Leapp::EventType::DEVICE_LOST)
      break;
  }

  return 0;
}
