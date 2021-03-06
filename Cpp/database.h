#pragma once
#include <iostream>
#include <vector>

enum class BKFIELD
{
	TITLE,
	AUTHOR,
	DATE,
	PUBLISHER,
	GENRE,
	BKFIELD_MAX
};

struct Book
{
	Book(std::string, std::string, std::string, std::string, std::string);

	std::string title;
	std::string author;
	std::string date;
	std::string publisher;
	std::string genre;
};

class Database
{
public:
	Database(std::string);
	void add(Book);
	void search(int, std::string);
	void edit(int, int, std::string);
	void remove(int);
	void show(int);
	void save();
	int  length();
private:
	std::vector<Book> booklist;
	std::string filepath;
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
