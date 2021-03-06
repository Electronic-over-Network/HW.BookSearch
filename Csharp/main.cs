using System;

namespace HW.BookSearch
{
    class Program
    {
        /* 시작점
        본격적으로 파이썬이 시작되는 부분이다.이는 C/C++의 main() 함수
        역할을 하는 동시, import와 같이 모듈로 호출되면 동작하지 않는다. */
        static void Main()
        {
            var _ = new Application("booklist.txt");
        }
    }

    class Application
    {
        private readonly Database database;
        private readonly string filepath;

        public Application(string filepath)
        {
            this.filepath = filepath;
            database = new(this.filepath);
            SetupUI();
        }

        ///<summary>
        ///사용자 인터페이스: 메뉴
        ///</summary>
        private void SetupUI()
        {

        }


        ///<summary>
        ///사용자 인터페이스: 1. 도서 추가
        ///</summary>
        private void add()
        {

        }

        ///<summary>
        ///사용자 인터페이스: 2. 도서 검색
        ///</summary>
        private void search()
        {

        }

        ///<summary>
        ///사용자 인터페이스: 3. 도서 정보 수정
        ///</summary>
        private void edit()
        {

        }

        ///<summary>
        ///사용자 인터페이스: 4. 도서 삭제
        ///</summary>
        private void remove()
        {

        }

        ///<summary>
        ///사용자 인터페이스: 5. 현재 총 도서 목록
        ///</summary>
        private void show()
        {

        }

        ///<summary>
        ///사용자 인터페이스: 6. 저장
        ///</summary>
        private void save()
        {

        }
    }
}
