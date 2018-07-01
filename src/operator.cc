#include "model/reader.hpp"
#include "model/book.hpp"
#include "model/dat_source.hpp"
#include <string>
#include <algorithm>
#include <iostream>
using std::string;
DatSource datt;
int add_mulit_books()
{
	string name,ind;
	std::cout << "请输入书名，索引号（以空格分开）。 例如：" << std::endl;
	std::cout << "活着 1123" << std::endl;
	while(std::cin >> name >> ind)
	{
		Book r(name, ind);
		datt.insert(r);
	}
	std::cout << "图书录入完成" << std::endl;
	return 0;
}
int add_book()
{
	string name,ind;
	std::cout << "请输入书名，索引号（以空格分开）。 例如：" << std::endl;
	std::cout << "活着 1123" << std::endl;
	std::cin >> name >> ind;
	Book r(name, ind);
	datt.insert(r);
	std::cout << "图书录入完成" << std::endl;
	return 0;
}
int alter_book()
{
	string name, ind;
	std::cout << "请输入要修改的图书索引号" << std::endl;
	std::cin >> ind;
	auto books = datt.get_book_by_index(ind);
	std::cout << "请输出你要的修改的信息，输入书名，索引号（以空格分开）" << std::endl;
	std::cin >> name >> ind;
	std::for_each(books.begin(), books.end(), [&name, &ind] (Book &r) {r.name = name, r.index = ind; datt.update(r);});
	return 0;
}
int delete_book()
{
	string name, ind;
	std::cout << "请输入要删除的图书索引号" << std::endl;
	std::cin >> ind;
	auto books = datt.get_book_by_index(ind);
	std::cin >> name >> ind;
	std::for_each(books.begin(), books.end(), [&name, &ind] (Book &r) {r.name = name, r.index = ind; datt.remove(r);});
	return 0;
}
int add_mulit_readers()
{
	string name, num, passwd;
	std::cout << "请输入号码，姓名，密码（以空格分开）。 例如：" << std::endl;
	std::cout << "1123 王仁泉 123" << std::endl;
	while(std::cin >> num >> name >> passwd)
	{
		Reader r(name, num, passwd);
		datt.insert(r);
	}
	std::cout << "读者录入完成" << std::endl;
	return 0;
}
int add_reader()
{
	string name, num, passwd;
	std::cout << "请输入号码，姓名，密码（以空格分开）。 例如：" << std::endl;
	std::cout << "1123 王仁泉 123" << std::endl;
	std::cin >> num >> name >> passwd;
	Reader r(name, num, passwd);
	datt.insert(r);
	std::cout << "读者录入完成" << std::endl;
	return 0;
}
int delete_reader()
{
	string num;
	std::cout << "请输入你要删除的读者的号码" << std::endl;
	std::cin >> num;
	auto u = datt.get_reader_by_num(num)[0];
	datt.remove(u);
	return 0;
}
int alter_reader()
{
	string num, name, password;
	std::cout << "请输入你要修改信息的读者的号码" << std::endl;
	std::cin >> num;
	auto u = datt.get_reader_by_num(num)[0];
	std::cout << "请输入你要修改的信息, 号码 姓名 密码, 例如：" << std::endl;
	std::cout << "2123 王仁泉 1231" << std::flush;
	u.num = num;
	u.name = name;
	u.password = password;
	datt.update(u);
	return 0;
}
int alter_manage_passwd()
{
	string password;
	std::cout << "请输入新的管理员密码" << std::endl;
	std::cin >> password;
	datt.set_manage_password(password);
	return 0;
}
int rent_book(Reader &r)
{
	string num;
	std::cout << "请输入借入的书籍索引号码" << std::endl;
	std::cin >> num;
	auto b = datt.get_book_by_index(num);
	if (b.size() == 0)
		throw std::runtime_error("no book");
	datt.rent_book(r, b[0]);
	return 0;
}
int back_book(Reader &r)
{
	string num;
	std::cout << "请输入借入的书籍索引号码" << std::endl;
	std::cin >> num;
	auto b = datt.get_book_by_index(num);
	datt.back_book(r, *b.begin());
	return 0;
}

int search_book()
{
	string name;
	std::cout << "请输入您要查询的书名" << std::endl;
	std::cin >> name;
	auto b = datt.get_book_by_name(name);
	std::for_each(b.begin(), b.end(), [](Book &b){ std::cout << b;});
	return 0;
}
int alter_password(Reader &r)
{
	std::cout << "请输入你要修改的密码" << std::endl;
	std::cin >> r.password;
	datt.update(r);
	return 0;
}
int lookup(Reader &r)
{
	auto p = datt.lookup(r);
	std::for_each(p.begin(), p.end(), [](Book &r){ std::cout << r; });
	return 0;
}

