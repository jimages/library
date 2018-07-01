#include "operator.hpp"
#include "menu.hpp"
#include <iostream>
#include <string>
#include "model/dat_source.hpp"
#include "model/reader.hpp"
#include "model/book.hpp"

int admin();
int reader();
int main()
{
	while (true)
	{
		auto op = index_menu();
		switch (op) {
			case 1: admin();
				break;
			case 2: reader();
				break;
			case 3: exit(0);
				break;
		}
	}
	return 0;
}

int admin()
{
	while (true)
	{
		auto op = admin_menu();
		switch (op) {
			case 1: add_mulit_books();
				break;
			case 2: add_book();
				break;
			case 3: alter_book();
				break;
			case 4: delete_book();
				break;
			case 5: add_mulit_readers();
				break;
			case 6: add_reader(); 
				break;
			case 7: delete_reader();
				break;
			case 8: alter_reader();
				break;
			case 9: alter_manage_passwd();
				break;
			case 0: return 1;
		}
	}
}
int reader()
{
	clear();
	std::string num, password;
	std::cout << "请输入你的号码和密码以空格分割" << std::endl;
	std::cin >> num >> password;
	DatSource dat;
	auto user = dat.get_reader_by_num(num);
	auto p = user[0];
	// Todo: check the num
	while (true)
	{
		auto op = reader_menu();
		switch (op) {
			case 1: rent_book(p);
				break;
			case 2: back_book(p);
				break;
			case 3: search_book();
				break;
			case 4: alter_password(p);
				break;
			case 5: lookup(p);
				break;
			case 0: return 1;
		}
	}
return 0;
}

