#include <iostream>
#include <string>
#include "resource.h"
#include "member.h"
#include <vector>
using namespace std;
class library{
	private:
		vector <undergraduated> mem_list;
		vector <book> b_list;
	public:
		library();
		void data_get();
		void input_get();
		void process(string date, string resource_type, string resource_name, string op, string member_type, string member_name, int count);
		int daytoint(string s);
		string inttoday(int i);
};
