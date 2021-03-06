#include "database.h"
#include <fstream>
#include <string>

Database::Database(std::string filepath)
{
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

void Database::search(BOOK_FIELD field, std::string value)
{
	for (int index = 0; index < length(); index++)
	{
		std::string* ptr = reinterpret_cast<std::string*>(&booklist[index]);
		*(ptr + (static_cast<unsigned long>(field) * sizeof(std::string)));
	}
}

void Database::show(int index)
{
	std::cout << index << ". " << booklist[index].title << " (" << booklist[index].date << "��)" << std::endl
		<< "  * ����: " << booklist[index].author << std::endl
		<< "  * ���ǻ�: " << booklist[index].publisher << std::endl
		<< "  * �帣: " << booklist[index].genre << std::endl;
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
			<< "1. ���� �߰�" << std::endl
			<< "2. ���� �˻�" << std::endl
			<< "3. ���� ����" << std::endl
			<< "4. ���� ����" << std::endl
			<< "5. ���� ���" << std::endl
			<< "6. ����" << std::endl
			<< "7. ������" << std::endl
			<< "=====================" << std::endl
			<< "�޴��� �����ϼ���: ";

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
			std::cout << "�߸��� �Է��Դϴ�." << std::endl;
		}
		std::cout << std::endl;
	}
	add();
}

void Application::add()
{
	std::string title, author, date, publisher, genre;
	
	std::cout << "���� ������ �Է��ϼ���: ";
	std::cin >> title;

	std::cout << "���� ���ڸ� �Է��ϼ���: ";
	std::cin >> author;

	std::cout << "���� ���ǳ⵵�� �Է��ϼ���: ";
	std::cin >> date;

	std::cout << "���� ���ǻ縦 �Է��ϼ���: ";
	std::cin >> publisher;

	std::cout << "���� �帣�� �Է��ϼ���: ";
	std::cin >> genre;

	database->add(Book(title, author, date, publisher, genre));
	std::cout << "���� �߰� �Ϸ�!" << std::endl;
}

void Application::search()
{
	int field; std::string value;

	std::cout << "  " << static_cast<int>(BOOK_FIELD::BOOK_TITLE) << ". ����" << std::endl
		<< "  " << static_cast<int>(BOOK_FIELD::BOOK_AUTHOR) << ". ����" << std::endl
		<< "  " << static_cast<int>(BOOK_FIELD::BOOK_DATE) << ". ���ǳ⵵" << std::endl
		<< "  " << static_cast<int>(BOOK_FIELD::BOOK_PUBLISHER) << ". ���Ļ�" << std::endl
		<< "  " << static_cast<int>(BOOK_FIELD::BOOK_GENRE) << ". �帣" << std::endl
		<< "�˻��� ���� ������ �Է��ϼ���: ";
	std::cin >> field;
	std::cout << "�˻��� ���� ���� ������ �Է��ϼ���: ";
	std::cin >> value;
	
	database->search(static_cast<BOOK_FIELD>(field), value);
}

void Application::edit()
{

}

void Application::remove()
{

}

void Application::show()
{
	for (int index = 0; index < database->length(); index++)
		database->show(index);
}

void Application::save()
{

}

Book::Book(std::string title, std::string author, std::string date, std::string publisher, std::string genre)
{
	this->title = title;
	this->author = author;
	this->date = date;
	this->publisher = publisher;
	this->genre = genre;
}
