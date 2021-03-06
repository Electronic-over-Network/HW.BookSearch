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
	std::cout << index << ". " << booklist[index].title << " (" << booklist[index].date << "년)" << std::endl
		<< "  * 저자: " << booklist[index].author << std::endl
		<< "  * 출판사: " << booklist[index].publisher << std::endl
		<< "  * 장르: " << booklist[index].genre << std::endl;
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
			<< "1. 도서 추가" << std::endl
			<< "2. 도서 검색" << std::endl
			<< "3. 도서 수정" << std::endl
			<< "4. 도서 삭제" << std::endl
			<< "5. 도서 목록" << std::endl
			<< "6. 저장" << std::endl
			<< "7. 나가기" << std::endl
			<< "=====================" << std::endl
			<< "메뉴를 선택하세요: ";

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
			std::cout << "잘못된 입력입니다." << std::endl;
		}
		std::cout << std::endl;
	}
	add();
}

void Application::add()
{
	std::string title, author, date, publisher, genre;
	
	std::cout << "도서 제목을 입력하세요: ";
	std::cin >> title;

	std::cout << "도서 저자를 입력하세요: ";
	std::cin >> author;

	std::cout << "도서 출판년도를 입력하세요: ";
	std::cin >> date;

	std::cout << "도서 출판사를 입력하세요: ";
	std::cin >> publisher;

	std::cout << "도서 장르를 입력하세요: ";
	std::cin >> genre;

	database->add(Book(title, author, date, publisher, genre));
	std::cout << "도서 추가 완료!" << std::endl;
}

void Application::search()
{
	int field; std::string value;

	std::cout << "  " << static_cast<int>(BOOK_FIELD::BOOK_TITLE) << ". 제목" << std::endl
		<< "  " << static_cast<int>(BOOK_FIELD::BOOK_AUTHOR) << ". 저자" << std::endl
		<< "  " << static_cast<int>(BOOK_FIELD::BOOK_DATE) << ". 출판년도" << std::endl
		<< "  " << static_cast<int>(BOOK_FIELD::BOOK_PUBLISHER) << ". 출파사" << std::endl
		<< "  " << static_cast<int>(BOOK_FIELD::BOOK_GENRE) << ". 장르" << std::endl
		<< "검색할 도서 정보를 입력하세요: ";
	std::cin >> field;
	std::cout << "검색할 도서 정보 내용을 입력하세요: ";
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
