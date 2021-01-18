#include "Leapp/Connection.hpp"
#include "Leapp/Leapp.hpp"
#include "Leapp/Result.hpp"

#include <iostream>

namespace Leapp {

Connection::Connection() {
  const auto connectionStatus = static_cast<Result>(LeapCreateConnection(nullptr, &m_connection));

  if (connectionStatus != Result::SUCCESS)
    std::cerr << "[Leapp] Error: Failed to create connection (" << recoverResultStr(connectionStatus) << ")\n";

  open();
  poll(); // Polling once to complete connection
}

void Connection::open() const {
  const auto connectionStatus = static_cast<Result>(LeapOpenConnection(m_connection));

  if (connectionStatus != Result::SUCCESS)
    std::cerr << "[Leapp] Error: Failed to open connection (" << recoverResultStr(connectionStatus) << ")\n";
}

EventType Connection::poll() const {
  LEAP_CONNECTION_MESSAGE message {};
  const auto pollStatus = static_cast<Result>(LeapPollConnection(m_connection, 250, &message));

  if (pollStatus != Result::SUCCESS)
    std::cerr << "[Leapp] Error: Failed to poll connection (" << recoverResultStr(pollStatus) << ")\n";

  return static_cast<EventType>(message.type);
}

void Connection::close() const {
  LeapCloseConnection(m_connection);
}

Connection::~Connection() {
  close();
  LeapDestroyConnection(m_connection);
}

} // namespace Leap
