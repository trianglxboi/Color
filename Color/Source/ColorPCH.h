#pragma once

#ifdef CL_PLATFORM_WINDOWS
	#include <Windows.h>
#elif defined CL_PLATFORM_LINUX
	#include <linux/limits.h>
	#include <unistd.h>
#endif

#include <unordered_map>
#include <unordered_set>
#include <string_view>
#include <filesystem>
#include <functional>
#include <typeindex>
#include <optional>
#include <typeinfo>
#include <iostream>
#include <fstream>
#include <sstream>
#include <variant>
#include <bitset>
#include <thread>
#include <atomic>
#include <string>
#include <vector>
#include <memory>
#include <chrono>
#include <random>
#include <limits>
#include <array>
#include <mutex>
#include <regex>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <set>
#include <new>
#include <any>
