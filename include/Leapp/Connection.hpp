#pragma once

#ifndef LEAPP_CONNECTION_HPP
#define LEAPP_CONNECTION_HPP

#include <cstdint>
#include <utility>

struct _LEAP_CONNECTION;
using LEAP_CONNECTION = _LEAP_CONNECTION*;

namespace Leapp {

class EventData;

class Connection {
public:
  Connection() noexcept;
  Connection(const Connection&) = delete;
  Connection(Connection&& connection) noexcept : m_connection{ std::exchange(connection.m_connection, nullptr) } {}

  LEAP_CONNECTION getConnection() const noexcept { return m_connection; }

  void open() const noexcept;
  EventData poll() const noexcept;
  void close() const noexcept;

  Connection& operator=(const Connection&) = delete;
  Connection& operator=(Connection&& connection) noexcept { std::swap(m_connection, connection.m_connection); return *this; }

  ~Connection();

private:
  LEAP_CONNECTION m_connection {};
};

} // namespace Leapp

#endif // LEAPP_CONNECTION_HPP
