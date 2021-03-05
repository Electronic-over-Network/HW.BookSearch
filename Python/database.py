import numpy as np

#===================================================
# 상수
# : 책 정보 필드를 숫자로 접근하도록 하는 상수 역할을 한다.
#===================================================
BOOK_TITLE     = 0
BOOK_AUTHOR    = 1
BOOK_DATE      = 2
BOOK_PUBLISHER = 3
BOOK_GENRE     = 4

#===================================================
# 데이터베이스 클래스
# : 책 정보를 넘파이 형태가 아닌 정돈된 클래스로 정리한다.
#===================================================
class Database:

    """ 초기화: 자료 불러오기
    텍스트 파일에 있는 책 목록을 넘파이로 불러와 Book 클래스로 구성된 리스트로 정리하여 
    Database 객체에 저장한다.

    여기서 'UTF-8'은 텍스트가 8비트 유니코드로 인코딩되어 있기 때문이다. 만일 텍스트가 다른
    인코딩을 가지는 경우, 그에 맞게 encoding 인자도 변경해야 한다.
    """
    def __init__(self, filepath):
        self.booklist = list()
        database = np.loadtxt(filepath, dtype = str, encoding = 'UTF-8')
        for data in database:
            self.booklist.append(Book(data))

    # 책 정보 추가
    def add(self, title, author, date, publisher, genre):
        self.booklist.append(Book([title, author, date, publisher, genre]))

    # 책 정보 검색
    def search(self, field, value):
        index = []
        for book in self.booklist:
            if field == BOOK_TITLE:
                if book.title == value:
                    index.append(self.booklist.index(book))
            elif field == BOOK_AUTHOR:
                if book.author == value:
                    index.append(self.booklist.index(book))
            elif field == BOOK_DATE:
                if book.date == value:
                    index.append(self.booklist.index(book))
            elif field == BOOK_PUBLISHER:
                if book.publisher == value:
                    index.append(self.booklist.index(book))
            elif field == BOOK_GENRE:
                if book.genre == value:
                    index.append(self.booklist.index(book))
            else:
                ...

        for idx in index:
            self.show(idx)

    # 책 정보 수정
    def edit(self, index, field, value):
        info = [self.booklist[index].title, self.booklist[index].author, self.booklist[index].date, self.booklist[index].publisher, self.booklist[index].genre]
        info[field] = value
        self.booklist[index] = Book(info)

    # 책 정보 삭제
    def remove(self, index):
        del self.booklist[index]

    # 책 정보 보여주기
    def show(self, index):
        print(f"""{index}. {self.booklist[index].title} ({self.booklist[index].date}년)\
        \n  * 저자: {self.booklist[index].author}\
        \n  * 출판사: {self.booklist[index].publisher}\
        \n  * 장르: {self.booklist[index].genre}""")
    
    # 책 정보 저장
    def save(self, filepath):
        npBook = np.ndarray(shape = (self.Length, 5), dtype = '<U16')
        for book in self.booklist:
            npBook[self.booklist.index(book), BOOK_TITLE]     = book.title
            npBook[self.booklist.index(book), BOOK_AUTHOR]    = book.author
            npBook[self.booklist.index(book), BOOK_DATE]      = book.date
            npBook[self.booklist.index(book), BOOK_PUBLISHER] = book.publisher
            npBook[self.booklist.index(book), BOOK_GENRE]     = book.genre
        np.savetxt(filepath, npBook, fmt = "%s", encoding = 'UTF-8') 

    # 데이터베이스 책 개수
    @property
    def Length(self):
        return len(self.booklist)


#===================================================
# 책 클래스
# : 책 정보를 넘파이 형태가 아닌 정돈된 클래스로 정리한다.
#===================================================
class Book:

    """ 초기화: 책 정보 정리
    넘파이 데이터에서 할당받은 책 정보를 객체에 저장한다.
    한편, 해당 정보들은 함부로 변경할 수 없도록 호출만 가능한 프로퍼티를 사용하였다.
    """
    def __init__(self, info):
        self.__title     = info[BOOK_TITLE]
        self.__author    = info[BOOK_AUTHOR]
        self.__date      = info[BOOK_DATE]
        self.__publisher = info[BOOK_PUBLISHER]
        self.__genre     = info[BOOK_GENRE]

    # 제목
    @property
    def title(self):
        return self.__title
    
    # 작가
    @property
    def author(self):
        return self.__author

    # 출판년도
    @property
    def date(self):
        return self.__date
    
    # 출판사
    @property
    def publisher(self):
        return self.__publisher

    # 장르
    @property
    def genre(self):
        return self.__genre
