#include "Leapp/EventData.hpp"

#include <LeapC.h>

namespace Leapp {

EventData::EventData(const LEAP_CONNECTION_MESSAGE& message) {
  m_type = static_cast<EventType>(message.type);
  addHands(message.tracking_event->pHands, message.tracking_event->nHands);
}

void EventData::addHands(const LEAP_HAND* hands, uint32_t handCount) {
  m_hands.resize(handCount);

  for (uint32_t handIndex = 0; handIndex < handCount; ++handIndex) {
    const LEAP_HAND& leapHand = hands[handIndex];
    Hand& hand = m_hands[handIndex];

    hand.m_type = static_cast<HandType>(leapHand.type);

    const LEAP_PALM& leapPalm    = leapHand.palm;
    hand.m_palm.m_position       = leapPalm.position;
    hand.m_palm.m_stablePosition = leapPalm.stabilized_position;
    hand.m_palm.m_velocity       = leapPalm.velocity;
    hand.m_palm.m_normal         = leapPalm.normal;
    hand.m_palm.m_width          = leapPalm.width;
    hand.m_palm.m_direction      = leapPalm.direction;
    hand.m_palm.m_orientation    = leapPalm.orientation;

    addFingers(hand, leapHand.digits);
  }
}

void EventData::addFingers(Hand& hand, const LEAP_DIGIT (&fingers)[5]) {
  for (uint8_t fingerIndex = 0; fingerIndex < 5; ++fingerIndex) {
    const LEAP_DIGIT& leapFinger = fingers[fingerIndex];
    Finger& finger = hand.m_fingers[fingerIndex];

    for (uint8_t boneIndex = 0; boneIndex < 4; ++boneIndex) {
      const LEAP_BONE& leapFingerBone = leapFinger.bones[boneIndex];
      Bone& fingerBone = finger.m_bones[boneIndex];

      fingerBone.m_nearPosition = leapFingerBone.prev_joint;
      fingerBone.m_farPosition  = leapFingerBone.next_joint;
      fingerBone.m_width        = leapFingerBone.width;
      fingerBone.m_rotation     = leapFingerBone.rotation;
    }

    finger.m_isExtended = static_cast<bool>(leapFinger.is_extended);
  }
}

} // namespace Leapp
