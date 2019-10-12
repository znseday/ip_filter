#pragma once

#include <iostream>
#include <string>
#include <vector>

int MyVersion();

// !!! I intentionally use "std::" because it's a header !!!

using BYTE = unsigned char;

struct ipType
{
	BYTE Bytes[4];
	bool operator<(const ipType& ob) const;
};

std::ostream& operator<<(std::ostream& s, const ipType& ob);

ipType ConvertLineToIP(const std::string &str);

template<typename... Args>
void FilterByBytes(std::ostream& s, ipType ip, Args... args)
{
	const int argc = sizeof...(args);
	BYTE a[argc] = { (args)... };
	//for (int i = 0; i < argc; i++)
	//	cout << (int)a[i] << ((i < (argc-1)) ? '.' : '\n'); // for debugging

	//bool success = true;
	//for (int i = 0; i < argc; i++)
	//	if (ip.Bytes[i] != a[i])
	//		success = false;

	//if (success)
	//	s << ip;

	if ( std::equal(a, a + argc, ip.Bytes) )
		s << ip;
}