from database import *

class Application:
    def __init__(self, filepath):
        self.filepath = filepath
        self.database = Database(self.filepath)
        self.SetupUI()

    # 사용자 인터페이스: 메뉴
    def SetupUI(self):
        while(True):
            print("""=====================\
                \n|      OPTIONS      |\
                \n| ----------------- |\
                \n| 1. Add            |\
                \n| 2. Search         |\
                \n| 3. Edit           |\
                \n| 4. Remove         |\
                \n| 5. List           |\
                \n| 6. Save           |\
                \n| 7. Exit           |\
                \n=====================""")

            # 예외처리: 숫자 이외의 입력을 받을 시...
            try:
                option = int(input("Select from the menu: "))
            except:
                print("Invalid input.\n")
                continue

            if option == 1:
                self.add()
            elif option == 2:
                self.search()
            elif option == 3:
                self.edit()
            elif option == 4:
                self.remove()
            elif option == 5:
                self.show()
            elif option == 6:
                self.save()
            elif option == 7:
                self.save()
                break
            else:
                print("Invalid input.")
            print() # 한줄 띄어쓰기
        print("Exiting...")
    
    # 사용자 인터페이스: 1. 도서 추가
    def add(self):
        title     = input(">> Enter the title: ")
        author    = input(">> Enter the author: ")
        date      = input(">> Enter the published date: ")
        publisher = input(">> Enter the publisher: ")
        genre     = input(">> Enter the genre: ")
        self.database.add(title, author, date, publisher, genre)
        print("Book added!")

    # 사용자 인터페이스: 2. 도서 검색
    def search(self):
        try:
            print(f"""  {BOOK_TITLE}. Title\
                \n  {BOOK_AUTHOR}. Author\
                \n  {BOOK_DATE}. Published date\
                \n  {BOOK_PUBLISHER}. Publisher\
                \n  {BOOK_GENRE}. Genre""")
            field = int(input(">> Select the book field to search: "))
            value = input(">> Enter the book field content to search: ")
            self.database.search(field, value)
        except ValueError:
            ...

    # 사용자 인터페이스: 3. 도서 정보 수정
    def edit(self):
        try:
            index = int(input(">> Select the book to edit: "))
            print(f"""  {BOOK_TITLE}. Title\
                \n  {BOOK_AUTHOR}. Author\
                \n  {BOOK_DATE}. Published date\
                \n  {BOOK_PUBLISHER}. Publisher\
                \n  {BOOK_GENRE}. Genre""")
            field = int(input(">> Select the book field to edit: "))
            value = input(">> Enter a new content for the field: ")
            self.database.edit(index, field, value)
            print("Book edited!")
        except ValueError:
            print("Cancelled editing.")
        except IndexError:
            print("Unable to find a book from the index.")

    # 사용자 인터페이스: 4. 도서 삭제
    def remove(self):
        self.show()
        try:
            index = int(input(">> Select the book to remove: "))
            self.database.remove(index)
            print("Book removed!")
        except ValueError:
            print("Cancelled removing.")
        except IndexError:
            print("Unable to find a book from the index.")

    # 사용자 인터페이스: 5. 현재 총 도서 목록
    def show(self):
        for index in range(self.database.Length):
            self.database.show(index)

    # 사용자 인터페이스: 6. 저장
    def save(self):
        self.database.save(self.filepath)
        print("Book saved!")


""" 시작점
본격적으로 파이썬이 시작되는 부분이다. 이는 C/C++의 main() 함수 
역할을 하는 동시, import와 같이 모듈로 호출되면 동작하지 않는다.
"""
if __name__ == "__main__":
    app = Application("booklist.txt")
