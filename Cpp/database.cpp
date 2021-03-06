#include "database.h"
#include <fstream>

Book::Book(std::string title, std::string author, std::string date, std::string publisher, std::string genre)
{
	this->title = title;
	this->author = author;
	this->date = date;
	this->publisher = publisher;
	this->genre = genre;
}

Database::Database(std::string filepath)
{
	this->filepath = filepath;
	std::ifstream ifile(filepath);
	std::string title, author, date, publisher, genre;
	while (ifile)
	{
		ifile >> title;
		ifile >> author;
		ifile >> date;
		ifile >> publisher;
		ifile >> genre;
		if (!ifile) break;
		booklist.push_back(Book(title, author, date, publisher, genre));
	}
	ifile.close();
}

void Database::add(Book book)
{
	booklist.push_back(book);
}

void Database::search(int field, std::string value)
{
	for (int index = 0; index < length(); index++)
	{
		std::string* ptr = reinterpret_cast<std::string*>(&booklist[index]);
		if (value == *(ptr + field))
		{
			show(index);
		}
	}
}

void Database::edit(int index, int field, std::string value)
{
	std::string* ptr = reinterpret_cast<std::string*>(&booklist[index]);
	*(ptr + field) = value;
}

void Database::remove(int index)
{
	booklist.erase(booklist.begin() + index);
}

void Database::show(int index)
{
	std::cout << index << ". " << booklist[index].title << " (" << booklist[index].date << ")" << std::endl
		<< "  * Author: " << booklist[index].author << std::endl
		<< "  * Genre: " << booklist[index].genre << std::endl
		<< "  * Publisher: " << booklist[index].publisher << std::endl;
}

void Database::save()
{
	std::ofstream ofile(filepath, std::ofstream::trunc);
	for (Book book : booklist)
	{
		ofile << book.title << " " << book.author << " " << book.date
			<< " " << book.publisher << " " << book.genre << std::endl;
	}
}

int Database::length()
{
	return booklist.size();
}

Application::Application(std::string filepath)
{
	database = new Database(filepath);
	SetupUI();
}

void Application::SetupUI()
{
	while (true)
	{
		std::cout
			<< "=====================" << std::endl
			<< "|      OPTIONS      |" << std::endl
			<< "| ----------------- |" << std::endl
			<< "| 1. Add            |" << std::endl
			<< "| 2. Search         |" << std::endl
			<< "| 3. Edit           |" << std::endl
			<< "| 4. Remove         |" << std::endl
			<< "| 5. List           |" << std::endl
			<< "| 6. Save           |" << std::endl
			<< "| 7. Exit           |" << std::endl
			<< "=====================" << std::endl
			<< "Select from the menu: ";

		int option;
		std::cin >> option;

		switch (option)
		{
		case 1:
			add();
			break;
		case 2:
			search();
			break;
		case 3:
			edit();
			break;
		case 4:
			remove();
			break;
		case 5:
			show();
			break;
		case 6:
			save();
			break;
		case 7:
			save();
			return;
		default:
			std::cout << "Invalid input." << std::endl;
		}
		std::cout << std::endl;
	}
}

void Application::add()
{
	std::string title, author, date, publisher, genre;

	std::cout << ">> Enter the title: ";
	std::cin >> title;

	std::cout << ">> Enter the author: ";
	std::cin >> author;

	std::cout << ">> Enter the published date: ";
	std::cin >> date;

	std::cout << ">> Enter the publisher: ";
	std::cin >> publisher;

	std::cout << ">> Enter the genre: ";
	std::cin >> genre;

	database->add(Book(title, author, date, publisher, genre));
	std::cout << "Book added!" << std::endl;
}

void Application::search()
{
	int field;
	std::string value;

	std::cout << "  " << static_cast<int>(BKFIELD::TITLE) << ". Title" << std::endl
		<< "  " << static_cast<int>(BKFIELD::AUTHOR) << ". Author" << std::endl
		<< "  " << static_cast<int>(BKFIELD::DATE) << ". Published date" << std::endl
		<< "  " << static_cast<int>(BKFIELD::PUBLISHER) << ". Publisher" << std::endl
		<< "  " << static_cast<int>(BKFIELD::GENRE) << ". Genre" << std::endl
		<< ">> Select the book field to search: ";
	std::cin >> field;
	std::cout << ">> Enter the book field content to search:";
	std::cin >> value;

	database->search(field, value);
}

void Application::edit()
{
	int index, field;
	std::string value;

	std::cout << ">> Select the book to edit: ";
	std::cin >> index;

	if (index < database->length() && !(index < 0))
	{
		std::cout << "  " << static_cast<int>(BKFIELD::TITLE) << ". Title" << std::endl
			<< "  " << static_cast<int>(BKFIELD::AUTHOR) << ". Author" << std::endl
			<< "  " << static_cast<int>(BKFIELD::DATE) << ". Published date" << std::endl
			<< "  " << static_cast<int>(BKFIELD::PUBLISHER) << ". Publisher" << std::endl
			<< "  " << static_cast<int>(BKFIELD::GENRE) << ". Genre" << std::endl
			<< ">> Select the book field to search: ";
		std::cin >> field;

		if (field < static_cast<int>(BKFIELD::BKFIELD_MAX) && !(field < 0))
		{
			std::cout << ">> Enter a new content for the field: ";
				std::cin >> value;

				database->edit(index, field, value);
		}
		else
		{
			std::cout << "Invalid book field." << std::endl;
		}
	}
	else
	{
		std::cout << "Unable to find a book from the index." << std::endl;
	}
}

void Application::remove()
{
	show();

	int index;
	std::cout << ">> Select the book to remove: ";
	std::cin >> index;
	if (index < database->length() && !(index < 0))
	{
		database->remove(index);
		std::cout << "Book removed!" << std::endl;
	}
	else
	{
		std::cout << "Unable to find a book from the index." << std::endl;
	}
}

void Application::show()
{
	for (int index = 0; index < database->length(); index++)
	{
		database->show(index);
	}
}

void Application::save()
{
	database->save();
	std::cout << "Book saved!" << std::endl;
}
