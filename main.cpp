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
#else
	istream& i_stream = cin;
#endif

	string line;
	while (getline(i_stream, line))
		ips.push_back(ConvertLineToIP(line));

	// lex sort
	//sort(ips.begin(), ips.end(), greater_equal<ipType>()); // Why does it throw "invalid comparator"?

	sort(ips.begin(), ips.end(), greater<ipType>());

	for (auto it = ips.cbegin(); it != ips.cend(); ++it) // Added, cos std::copy doesn't work any more !
		cout << *it;

	//copy(ips.cbegin(), ips.cend(), ostream_iterator<ipType>(cout)); // doesn't work any more((( Why???


	//auto LambdaFilterOne = [&ips](BYTE byte) // it's not necessary any more, cos we have LambdaFilterByBytes !
	//{
	//	for (auto it = ips.cbegin(); it != ips.cend(); ++it)
	//		if ((*it).Bytes[0] == byte) // for the old version when we use char[4] 
	//			cout << *it;
	//};
	//LambdaFilterOne((BYTE)1);

	auto LambdaFilterByBytes = [&ips](auto... params)
	{
		ipType a { (params)... }; // ??? it works, hmm...
		const int argc = sizeof...(params);
		for (int i = argc; i < 4; i++)
			a.push_back((BYTE)0);  // for lower_bound

		ipType b { (params)... }; // ??? it works, hmm...
		for (int i = argc; i < 4; i++)
			b.push_back((BYTE)255); // for upper_bound

		//vector<ipType>::reverse_iterator it = lower_bound(ips.cbegin(), ips.cend(), a, greater<ipType>()/*, [](ipType cur, ipType a) {return; }*/);
		//auto it_l = lower_bound(ips.cbegin(), ips.cend(), a , [](ipType a, ipType cur) {return cur < a; });
		//auto it_u = upper_bound(ips.cbegin(), ips.cend(), b , [](ipType b, ipType cur) {return cur < b; });

		auto it_l = lower_bound(ips.cbegin(), ips.cend(), a, greater<ipType>());
		auto it_u = upper_bound(ips.cbegin(), ips.cend(), b, greater<ipType>());

		//cout << "--------------------" << endl;
		//cout << *it_l;   // for debugging
		//cout << *it_u;   // for debugging
		//cout << "--------------------" << endl;

		for (; it_l != it_u; ++it_u)
			cout << *it_u;

//		for (auto it = ips.cbegin(); it != ips.cend(); ++it) // for an old linearic version
//			FilterByBytes(cout, *it, params...);         // causes "Deprecated" warning
	};

	LambdaFilterByBytes((BYTE)1); // instead of LambdaFilterOne((BYTE)1); 

	//cout << "------------------------------------------------------" << endl;
	LambdaFilterByBytes((BYTE)46, (BYTE)70);
	//cout << "------------------------------------------------------" << endl;

	auto LambdaFilterAny = [&ips](BYTE byte)
	{
		for (auto it = ips.cbegin(); it != ips.cend(); ++it)
		//	if ((*it).Bytes[0] == byte || (*it).Bytes[1] == byte || (*it).Bytes[2] == byte || (*it).Bytes[3] == byte)
		//	if ( any_of( (*it).Bytes, (*it).Bytes + 4, [byte](BYTE val) {return val == byte; } ) ) 
			if (any_of((*it).cbegin(), (*it).cend(), [byte](BYTE val) {return val == byte; }))
				cout << *it;	
	};
	LambdaFilterAny((BYTE)46);

    return 0;
}
