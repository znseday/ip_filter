#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
#include <algorithm>

#include "my_aux.h"

using namespace std;

int main()
{
	vector<ipType> ips;

#if (defined WIN32) || (defined WIN64)
	cout << "Home work, version: " << MyVersion() << endl << endl; // for debugging
	istream & i_stream = ifstream("ip_filter.tsv");
	if (!i_stream)
	{
		cout << "My error: the input file not found" << endl;
		exit(0);
	}
	ofstream o_stream("My_Out.txt"); // for debugging
#else
	istream& i_stream = cin;
#endif

	string line;
	while (getline(i_stream, line))
		ips.push_back(ConvertLineToIP(line));

	// lex sort
	sort(ips.begin(), ips.end());
	copy(ips.cbegin(), ips.cend(), ostream_iterator<ipType>(cout));
#if (defined WIN32) || (defined WIN64)
	copy(ips.cbegin(), ips.cend(), ostream_iterator<ipType>(o_stream)); // for debugging
#endif

	//auto LambdaFilterOne = [&ips](BYTE byte) // it's not necessary any more, cos we have LambdaFilterByBytes
	//{
	//	for (auto it = ips.cbegin(); it != ips.cend(); ++it)
	//		if ((*it).Bytes[0] == byte)
	//			cout << *it;
	//};
	//LambdaFilterOne((BYTE)1);

	auto LambdaFilterByBytes = [&ips](auto... params)
	{
		for (auto it = ips.cbegin(); it != ips.cend(); ++it)
			FilterByBytes(cout, *it, params...);
	};

	LambdaFilterByBytes((BYTE)1); // instead of LambdaFilterOne((BYTE)1); 

	//cout << "------------------------------------------------------" << endl;
	LambdaFilterByBytes((BYTE)46, (BYTE)70);
	//cout << "------------------------------------------------------" << endl;

	auto LambdaFilterAny = [&ips](BYTE byte)
	{
		for (auto it = ips.cbegin(); it != ips.cend(); ++it)
		//	if ((*it).Bytes[0] == byte || (*it).Bytes[1] == byte || (*it).Bytes[2] == byte || (*it).Bytes[3] == byte)
			if ( any_of( (*it).Bytes, (*it).Bytes + 4, [byte](BYTE val) {return val == byte; } ) ) 
				cout << *it;	
	};
	LambdaFilterAny((BYTE)46);

    return 0;
}
