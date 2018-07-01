#include <iostream>
#include <cstdio>
#include <boost/format.hpp>
void
clear (void)
{    
  while ( getchar() != '\n' );
}
int index_menu()
{
	int op = 0;
	std::cout <<
"	**********************************\n"
"	        欢迎使用图书管理系统\n"
"	        1 管理员模式\n"
"	        2 读者模式\n"
"		3 退出\n" <<
	std::flush;
	while (op == 0) {
		std::cout << "请输入选项：" << std::flush;
		std::cin >> op;
		if (op == 1 ||
		    op == 2 ||
		    op == 3) {
			return op;
		} else{
			std::cout << "您的指令有误，请重新输入" << std::endl;
			clear();
			op = 0;
		}
	}
}

int admin_menu()
{
	int op = 0;
	std::cout <<
"	**********************************\n"
"	        1 建立图书库存信息\n"
"	        2 增加图书信息\n"
"		3 修改图书信息\n" 
"		4 删除图书信息\n" 
"		5 创建读者信息\n" 
"		6 增加读者信息\n" 
"		7 删除读者信息\n" 
"		8 修改读者信息\n" 
"		9 修改管理员密码\n" 
"		0 返回上一层目录\n"
"	**********************************\n" <<
	std::flush;
	while (op == 0) {
		std::cout << "请输入选项：" << std::flush;
		std::cin >> op;
		if (op >= 0 && op <= 9) {
			return op;
		}else{
			clear();
			std::cout << "您的指令有误，请重新输入" << std::endl;
			op = 0;
		}
	}
}
int reader_menu()
{
	int op = 0;
	std::cout <<
"	**********************************\n"
"	        1 借阅图书\n"
"	        2 归还图书\n"
"		3 查询图书\n" 
"		4 修改密码\n" 
"		5 查看借阅图书信息\n" 
"		0 返回上一层目录\n"
"	**********************************\n" << 
	std::flush;
	while (op == 0) {
		std::cout << "请输入选项：" << std::flush;
		std::cin >> op;
		if (op >= 0 && op <= 5) {
			return op;
		}else{
			std::cout << "您的指令有误，请重新输入" << std::endl;
			clear();
			op = 0;
		}
	}
}

