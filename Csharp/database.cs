using System;
using System.IO;
using System.Collections.Generic;

namespace HW.BookSearch
{
    //==================================================
    // 데이터베이스 클래스
    // : 책 정보를 넘파이 형태가 아닌 정돈된 클래스로 정리한다.
    //==================================================
    class Database
    {
        private readonly List<Book> booklist = new();

        /* 초기화: 자료 불러오기
        텍스트 파일에 있는 책 목록을 넘파이로 불러와 Book 클래스로 구성된 리스트로 정리하여
        Database 객체에 저장한다.

        여기서 'UTF-8'은 텍스트가 8비트 유니코드로 인코딩되어 있기 때문이다.만일 텍스트가 다른
        인코딩을 가지는 경우, 그에 맞게 encoding 인자도 변경해야 한다. */
        public Database(string filepath)
        {
            string[] database = File.ReadAllLines(filepath);
            foreach (string data in database)
            {
                // 첫 번째 줄에 출판사와 장르 사이에 띄어쓰기가 두 번 적용되어 있어, StringSplitOptions으로 처리한다.
                string[] parsed = data.Split(new char[] { ' ', '\t' }, StringSplitOptions.RemoveEmptyEntries);

                booklist.Add(new Book() {
                    title = parsed[0],
                    author = parsed[1],
                    date = Convert.ToInt32(parsed[2]),
                    publisher = parsed[3],
                    genre = parsed[4] });
            }
        }
    }

    //==================================================
    // 책 구조체
    // : 책 정보를 컬렉션 형태가 아닌 정돈된 구조체로 정리한다.
    //==================================================
    struct Book
    {
        public string title;
        public string author;
        public int date;
        public string publisher;
        public string genre;
    }
}
