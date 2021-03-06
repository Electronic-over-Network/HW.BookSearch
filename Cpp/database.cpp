#include "database.h"
#include <fstream>

/* 구조체 생성자
구조체는 모든 맴버가 public인 클래스와 동일하다. 그러므로 구조체 또한 생성자를
가질 수가 있다. 객체를 생성하는 즉시 책 정보가 자동으로 각 필드에 저장된다. */
Book::Book(std::string title, std::string author, std::string date, std::string publisher, std::string genre)
{
	this->title = title;
	this->author = author;
	this->date = date;
	this->publisher = publisher;
	this->genre = genre;
}

/* 데이터베이스 생성자
텍스트 파일에 있는 책 목록을 단어마다 불러와 Book 클래스로 구성된 구조체에 정리하여 
벡터 컨테이너에 저장한다. 만일 더이상 읽을 내용이 없으면 조건문이 발동된다. */
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

// 책 정보 추가
void Database::add(Book book)
{
	booklist.push_back(book);
}

// 책 정보 검색
void Database::search(int field, std::string value)
{
	/* 포인터로 접근한 구조체 필드
	Database::edit() 함수 정의에 기입된 주석 설명 참조 */
	for (int index = 0; index < length(); index++)
	{
		std::string* ptr = reinterpret_cast<std::string*>(&booklist[index]);
		if (value == *(ptr + field))
		{
			show(index);
		}
	}
}

// 책 정보 수정
void Database::edit(int index, int field, std::string value)
{
	/* 포인터로 접근한 구조체 필드
	구조체의 맴버는 title - author - data - publisher - genre 순으로 
	선언되었다. 그리고 해당 맴버들은 실제 메모리 구조도 이와 같은 순서로 할당된다.
	
	간단히 예를 들어, 64비트 시스템에서 std::string는 총 0x40 바이트를 차지한다.
	그리고 임의로 선택한 Book 객체의 각 맴버들이 할당된 메모리 주소는 다음과 같다:

	&title     = 0x0000011319D47470
	&author    = 0x0000011319D474B0
	&data      = 0x0000011319D474F0
	&publisher = 0x0000011319D47530
	&genre     = 0x0000011319D47570

	각 맴버들의 주소들은 모두 위에서 언급한 0x40 만큼 동일한 간격을 가지고 있다.
	그러므로 포인터를 통해서 구조체 맴버를 접근은 전혀 문제가 없다.

	해당 기법은 C++가 아닌 C 언어에서도 흔히 사용되므로 알아두면 매우 유용하다. */
	std::string* ptr = reinterpret_cast<std::string*>(&booklist[index]);
	*(ptr + field) = value;
}

// 책 정보 삭제
void Database::remove(int index)
{
	booklist.erase(booklist.begin() + index);
}

// 책 정보 보여주기
void Database::show(int index)
{
	std::cout << index << ". " << booklist[index].title << " (" << booklist[index].date << ")" << std::endl
		<< "  * Author: " << booklist[index].author << std::endl
		<< "  * Genre: " << booklist[index].genre << std::endl
		<< "  * Publisher: " << booklist[index].publisher << std::endl;
}

// 책 정보 저장 
void Database::save()
{
	std::ofstream ofile(filepath, std::ofstream::trunc);
	for (Book book : booklist)
	{
		ofile << book.title << " " << book.author << " " << book.date
			<< " " << book.publisher << " " << book.genre << std::endl;
	}
}

// 데이터베이스 책 개수
int Database::length()
{
	return booklist.size();
}

Application::Application(std::string filepath)
{
	database = new Database(filepath);
	SetupUI();
}

// 사용자 인터페이스: 메뉴
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

// 사용자 인터페이스: 1. 도서 추가
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

// 사용자 인터페이스: 2. 도서 검색
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

// 사용자 인터페이스: 3. 도서 수정
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

// 사용자 인터페이스: 4. 도서 제거
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

// 사용자 인터페이스: 5. 도서 목록
void Application::show()
{
	for (int index = 0; index < database->length(); index++)
	{
		database->show(index);
	}
}

// 사용자 인터페이스: 6. 저장
void Application::save()
{
	database->save();
	std::cout << "Book saved!" << std::endl;
}
