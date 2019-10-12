#define BOOST_TEST_MODULE ip_filter_test_module

#include "my_aux.h"

#include <boost/test/unit_test.hpp>

using namespace std;

BOOST_AUTO_TEST_SUITE(ip_filter_test_suite)

BOOST_AUTO_TEST_CASE(ip_filter_test_MyVersion)
{
    BOOST_CHECK(MyVersion() > 0);
}

BOOST_AUTO_TEST_CASE(ip_filter_test_ConvertLineToIP)
{
	string TestString = "100.2.30.44";
	ipType ip = ConvertLineToIP(TestString);
	//BOOST_CHECK(ip.Bytes[0] == 100 && ip.Bytes[1] == 2 && ip.Bytes[2] == 30 && ip.Bytes[3] == 44);
	BOOST_CHECK(ip[0] == 100 && ip[1] == 2 && ip[2] == 30 && ip[3] == 44);
}

BOOST_AUTO_TEST_CASE(ip_filter_test_FilterByBytes)
{
	string TestString = "100.2.30.44";
	
	ipType ip = ConvertLineToIP(TestString);
	//cout << "ip for test: " << ip;
	//cout << "result ip (must be the same): ";
	//FilterByBytes(cout, ip, (BYTE)100, (BYTE)2);
	stringstream ss;
	FilterByBytes(ss, ip, (BYTE)100, (BYTE)2);
	string test;
	ss >> test;

	BOOST_REQUIRE_EQUAL(TestString, test);
}

BOOST_AUTO_TEST_CASE(ip_filter_test_FilterByBytes_not)
{
	string TestString = "100.2.30.44";

	ipType ip = ConvertLineToIP(TestString);
	//cout << "ip for test: " << ip;
	//cout << "result ip (must be the same): ";
	//FilterByBytes(cout, ip, (BYTE)100, (BYTE)2);
	stringstream ss;
	FilterByBytes(ss, ip, (BYTE)100, (BYTE)74, (BYTE)30);
	string test;
	ss >> test;

	BOOST_REQUIRE_NE(TestString, test);
}


BOOST_AUTO_TEST_SUITE_END()
