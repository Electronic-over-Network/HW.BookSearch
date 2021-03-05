from database import *
import numpy as np

class Application:
    def __init__(self, filepath):
        self.filepath = filepath
        self.database = Database(self.filepath)
        self.SetupUI()

    # 사용자 인터페이스: 메뉴
    def SetupUI(self):
        while(True):
            print("""=====================\
                \n1. 도서 추가\
                \n2. 도서 검색\
                \n3. 도서 정보 수정\
                \n4. 도서 삭제\
                \n5. 현재 총 도서 목록\
                \n6. 저장\
                \n7. 나가기\
                \n=====================""")

            # 예외처리: 숫자 이외의 입력을 받을 시...
            try:
                option = int(input("메뉴를 선택하세요: "))
            except:
                print("잘못된 입력입니다.\n")
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
                print("잘못된 입력입니다.")
            print() # 한줄 띄어쓰기
    
    # 사용자 인터페이스: 1. 도서 추가
    def add(self):
        title     = input("도서 제목을 입력하세요: ")
        author    = input("도서 저자를 입력하세요: ")
        date      = input("도서 출판년도를 입력하세요: ")
        publisher = input("도서 출판사를 입력하세요: ")
        genre     = input("도서 장르를 입력하세요: ")
        self.database.add(title, author, date, publisher, genre)
        print("도서 추가 완료!")

    # 사용자 인터페이스: 2. 도서 검색
    def search(self):
        try:
            print(f"""  {BOOK_TITLE}. 제목\
                \n  {BOOK_AUTHOR}. 저자\
                \n  {BOOK_DATE}. 출판년도\
                \n  {BOOK_PUBLISHER}. 출판사\
                \n  {BOOK_GENRE}. 장르""")
            field = int(input("검색할 도서 정보를 선택하세요: "))
            value = input("검색할 도서 정보 내용을 입력하세요: ")
            self.database.search(field, value)
        except ValueError:
            ...

    # 사용자 인터페이스: 3. 도서 정보 수정
    def edit(self):
        try:
            index = int(input("수정할 도서를 선택하세요: "))
            print(f"""  {BOOK_TITLE}. 제목\
                \n  {BOOK_AUTHOR}. 저자\
                \n  {BOOK_DATE}. 출판년도\
                \n  {BOOK_PUBLISHER}. 출판사\
                \n  {BOOK_GENRE}. 장르""")
            field = int(input("수정할 도서 정보를 선택하세요: "))
            value = input("수정할 도서 정보 내용을 입력하세요: ")
            self.database.edit(index, field, value)
            print("도서 수정 완료!")
        except ValueError:
            print("도서 삭제를 취소합니다.")
        except IndexError:
            print("해당 번호의 도서를 찾을 수 없습니다.")

    # 사용자 인터페이스: 4. 도서 삭제
    def remove(self):
        self.show()
        try:
            index = int(input("삭제할 도서를 선택하세요: "))
            self.database.remove(index)
            print("도서 삭제 완료!")
        except ValueError:
            print("도서 삭제를 취소합니다.")
        except IndexError:
            print("해당 번호의 도서를 찾을 수 없습니다.")

    # 사용자 인터페이스: 5. 현재 총 도서 목록
    def show(self):
        for index in range(self.database.Length):
            self.database.show(index)

    # 사용자 인터페이스: 6. 저장
    def save(self):
        self.database.save(self.filepath)


""" 시작점
본격적으로 파이썬이 시작되는 부분이다. 이는 C/C++의 main() 함수 
역할을 하는 동시, import와 같이 모듈로 호출되면 동작하지 않는다.
"""
if __name__ == "__main__":
    app = Application("booklist.txt")
