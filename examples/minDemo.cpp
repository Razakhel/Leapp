#include "Leapp/Connection.hpp"

#include <iostream>

int main() {
  Leapp::Connection connection;

  while (true) {
    const Leapp::EventType eventType = connection.poll();
    std::cout << "Status: " << Leapp::recoverEventTypeStr(eventType) << '\n';

    // If the connection has been severed (for example by unplugging the Leap Motion), stop the application
    if (eventType == Leapp::EventType::DEVICE_LOST)
      break;
  }

  return 0;
}
