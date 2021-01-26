#pragma once

#ifndef LEAPP_HAND_HPP
#define LEAPP_HAND_HPP

#include "Leapp/Math.hpp"

#include <array>

namespace Leapp {

class Palm {
  friend class EventData;

public:
  constexpr Palm() = default;

  constexpr const Vector& getPosition() const noexcept { return m_position; }
  constexpr const Vector& getStablePosition() const noexcept { return m_stablePosition; }
  constexpr const Vector& getVelocity() const noexcept { return m_velocity; }
  constexpr const Vector& getNormal() const noexcept { return m_normal; }
  constexpr float getWidth() const noexcept { return m_width; }
  constexpr const Vector& getDirection() const noexcept { return m_direction; }
  constexpr const Quaternion& getOrientation() const noexcept { return m_orientation; }

private:
  Vector m_position {};
  Vector m_stablePosition {};
  Vector m_velocity {};
  Vector m_normal {};
  float m_width {};
  Vector m_direction {};
  Quaternion m_orientation {};
};

class Finger {
  friend class EventData;

public:
  constexpr bool isExtended() const noexcept { return m_isExtended; }

private:
  bool m_isExtended {};
};

enum class HandType {
  LEFT  /* eLeapHandType_Left  */,
  RIGHT /* eLeapHandType_Right */
};

class Hand {
  friend class EventData;

public:
  constexpr Hand() = default;

  constexpr HandType getType() const noexcept { return m_type; }
  constexpr const Palm& getPalm() const noexcept { return m_palm; }
  constexpr const Finger& getThumb() const noexcept { return m_fingers[0]; }
  constexpr const Finger& getIndex() const noexcept { return m_fingers[1]; }
  constexpr const Finger& getMiddle() const noexcept { return m_fingers[2]; }
  constexpr const Finger& getRing() const noexcept { return m_fingers[3]; }
  constexpr const Finger& getPinky() const noexcept { return m_fingers[4]; }

private:
  HandType m_type {};
  Palm m_palm {};
  std::array<Finger, 5> m_fingers {};
};

} // namespace Leapp

#endif // LEAPP_HAND_HPP
