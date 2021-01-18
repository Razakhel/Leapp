#pragma once

#ifndef LEAPP_LEAPP_HPP
#define LEAPP_LEAPP_HPP

// Deactivating some warnings triggered by the Leap header
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4201)
#endif

#include "LeapC.h"

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#endif // LEAPP_LEAPP_HPP
