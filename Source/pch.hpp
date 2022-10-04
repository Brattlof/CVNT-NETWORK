#pragma once

// WINSOCK
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
//
#include <iostream>
#include <unordered_map>
#include <mutex>
#include <thread>
#include <functional>

#define LOG(...) std::cout << "[LOG] " << __VA_ARGS__ << "\n"
#define LOGFMT(fmt, ...) printf("[LOG] " fmt "\n", __VA_ARGS__)