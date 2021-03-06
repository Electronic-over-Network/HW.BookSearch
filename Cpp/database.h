#pragma once
#include <iostream>
#include <vector>

struct Book
{
	Book(std::string, std::string, std::string, std::string, std::string);

	std::string title;
	std::string author;
	std::string date;
	std::string publisher;
	std::string genre;
};

enum class BOOK_FIELD
{
	BOOK_TITLE,
	BOOK_AUTHOR,
	BOOK_DATE,
	BOOK_PUBLISHER,
	BOOK_GENRE
};

class Database
{
public:
	Database(std::string);
	void add(Book);
	void search(BOOK_FIELD, std::string);
	void edit();
	void remove();
	void show(int);
	void save();
	int  length();
private:
	std::vector<Book> booklist;
};

class Application
{
public:
	Application(std::string);
private:
	Database* database;

	void SetupUI();
	void add();
	void search();
	void edit();
	void remove();
	void show();
	void save();
};
