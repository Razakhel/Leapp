#include "Leapp/Leapp.hpp"

#include <iostream>

int main() {
  Leapp::Connection connection;

  while (true) {
    const Leapp::EventData eventData = connection.poll();

    // If the connection has been severed (for example by unplugging the Leap Motion), stop the application
    if (eventData.getType() == Leapp::EventType::DEVICE_LOST)
      break;

    const uint32_t handCount = eventData.getHandCount();

    if (handCount > 0) {
      std::cout << handCount << " hand" << (handCount > 1 ? "s " : " ") << "detected:\n";

      for (uint32_t handIndex = 0; handIndex < handCount; ++handIndex) {
        const Leapp::Hand& hand = eventData.getHand(handIndex);

        std::cout << "\t- " << (hand.getType() == Leapp::HandType::RIGHT ? "Right" : "Left") << " hand\n";
        std::cout << "\t  Palm position: " << hand.getPalm().getPosition() << '\n';

        const Leapp::Finger& index = hand.getIndex();

        if (index.isExtended()) {
          std::cout << "\t  Index extended\n";
          std::cout << "\t  Index tip: " << index.getTipPosition() << '\n';
        }
      }
    }
  }

  return 0;
}
