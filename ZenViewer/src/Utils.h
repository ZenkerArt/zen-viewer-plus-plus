#pragma once
#include <iostream>
#include <string>

inline void runtimeError(const std::string& text) {
	std::cout << text << std::endl;
	throw std::runtime_error(text.c_str());
}

inline std::string makeUtf8Str(const std::u8string& utf8)
{
	return std::string(reinterpret_cast<const char*>(utf8.c_str()), utf8.size());
}
