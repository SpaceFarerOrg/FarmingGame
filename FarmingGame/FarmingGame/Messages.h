#pragma once
#include "Messaging/Messages/BaseMessage.h"

#include <SFML/Window/Keyboard.hpp>

DEFINE_MSG_ONE_PARAM(ConnectionAccepted, std::string, hostName)

