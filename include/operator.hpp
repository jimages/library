#ifndef ABC
#define ABC
class Reader;
class Book;

int add_mulit_books();
int add_book();
int alter_book();
int delete_book();
int add_mulit_books();
int add_mulit_readers();
int add_reader();
int delete_reader();
int alter_reader();
int alter_manage_passwd();
int rent_book(Reader &r);
int back_book(Reader &r);
int search_book();
int alter_password(Reader &r);
int lookup(Reader &r);
#endif
