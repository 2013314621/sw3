#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "library.h"
using namespace std;
library::library(){
	data_get();
	input_get();
}

void library::data_get(){
	ifstream in_1;
	in_1.open("resource.dat");
	string temp;
	in_1 >> temp;
	in_1 >> temp;
	int i = 0;
	while(in_1 >> temp){
		in_1 >> temp;
		book book_temp(temp);
		b_list.push_back(book_temp);	
	}
	in_1.close();
	
}
void library::input_get(){
	ifstream in_2;
	string date;
	string resource_type;
	string resource_name;
	string op;
	string member_type;
	string member_name;
	int count = 1;
	in_2.open("input.dat");
	string temp;
	in_2 >> date >> resource_type >> resource_name >> op >> member_type >> member_name; 
	while(in_2 >> date){
		in_2 >> resource_type >> resource_name >> op >> member_type >> member_name;
		process(date,resource_type,resource_name,op,member_type,member_name,count);
		count++;
	}
	in_2.close();
}
void library::process(string date, string resource_type, string resource_name, string op, string member_type, string member_name, int count){
	int flag = 0;
	int state = 0;
	int i = 0;
	int int_temp;
	string delay;
	for(auto a : b_list){
		if(a.name_get() == resource_name){
			flag = 1;
			state = 1;
		}
	}
	if(flag == 0){
		cout << count << "\t"<< "1" << "\tNon exist resource." << endl;
	}
	else{
		if(op == "B"){
			for(auto a : mem_list){
				if(a.name_get() == member_name){
					if((a.limit_get() != 0) && (state == 1)){ 
						cout << count << "\t2" << "\tExceeds your possible number of borrow. Possible # of borrows: 1" << endl;
						state = 0;	
					}
					if((a.ban_get() == 1) && (state == 1)){
						cout << count << "\t7" << "\tRestricted member until " << a.restricted_day_get() << endl;
						state = 0;	
					}
				}
			}
			for(auto a : b_list){
				if(a.name_get() == resource_name){
					if((a.borrow_member_get() != member_name) && (a.borrow_member_get() != "") && (state == 1)){
						cout << count << "\t5" << "\tOther member already borrowed this book. This book will be returned at " << a.return_day_get() << endl;
						state = 0;
					}
				} 
			}
			for(auto a: b_list){
				if(a.name_get() == resource_name){
					a.name_set(resource_name);
					a.borrow_member_set(member_name);
					a.return_day_set(date);
					b_list.push_back(a);
				}
			}
			if(state == 1){
				undergraduated b(member_name);
				b.book_name_set(resource_name);
				b.limit_set(1);
				mem_list.push_back(b);
				book c(resource_name);
				c.borrow_member_set(member_name);
				c.return_day_set(date);
				b_list.push_back(c);
				b_list.erase(b_list.begin()+i);
				i++;
				cout << count << "\t0" << "\tSuccess." << endl;
			}
		}
		if(op == "R"){
			for(auto a : mem_list){
				if((a.name_get() == member_name) && (a.book_name_get() == resource_name)){
					for(auto a : b_list){
						if(a.name_get() == resource_name){
							int_temp = daytoint(date) - daytoint(a.return_day_get());
							if(int_temp >13){
								int_temp = daytoint(date) + int_temp;
								delay = inttoday(int_temp);
								if(state == 1){
									for(auto a : mem_list){
										if(a.name_get() == member_name){
											a.restricted_day_set(delay);
											a.ban_set(1);
											a.limit_set(0);
											a.book_name_set("");
											cout << count << "\t7" << "\tDelayed return. You'll be restricted until " << a.restricted_day_get() << endl; 
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
int library :: daytoint(string s){
	string year, month, day;
	int year_int, month_int, day_int, all_day;
	year = s[0];
	year = year + s[1];
	month = s[3];
	month = month + s[4];
	day = s[6];
	day = day + s[7];
	year_int = stoi(year);
	month_int = stoi(month);
	day_int = stoi(day);
	all_day = year_int*360 + month_int*30 + day_int + 13;
	return all_day;
}
string library :: inttoday(int i){
	string year, month, day;
	year = to_string(i/360);
	if(year.length()==1) year = "0" + year;
	month = to_string((i%360)/30);
	if(month.length()==1) month = "0" + month;
	day = to_string((i%360)%30);
	if(day.length()==1) day = "0" + day;
	return year + "/" + month + "/" + day;	
}