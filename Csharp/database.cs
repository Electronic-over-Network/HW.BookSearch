using System;
using System.IO;
using System.Collections.Generic;

namespace HW.BookSearch
{
    //==================================================
    // 데이터베이스 클래스
    // : UI에서 요청한 정보를 제공하거나 입력받아 업데이트한다.
    //==================================================
    class Database
    {
        private readonly List<Book> booklist = new();
        private readonly string filepath;

        /* 초기화: 자료 불러오기
        텍스트 파일에 있는 책 목록을 한 줄마다 불러와 Book 구조체로 구성된 리스트로 정리하여
        Database 객체에 저장한다. */
        public Database(string filepath)
        {
            this.filepath = filepath;
            string[] database = File.ReadAllLines(this.filepath);
            foreach (string data in database)
            {
                // 첫 번째 줄에 출판사와 장르 사이에 띄어쓰기가 두 번 적용되어 있어, StringSplitOptions으로 처리한다.
                string[] parsed = data.Split(new char[] { ' ', '\t' }, StringSplitOptions.RemoveEmptyEntries);

                booklist.Add(new Book() {
                    title     = parsed[0],
                    author    = parsed[1],
                    date      = parsed[2],
                    publisher = parsed[3],
                    genre     = parsed[4] }
                );
            }
        }

        ///<summary>
        ///책 정보 추가
        ///</summary>
        public void add(Book book)
        {
            booklist.Add(book);
        }

        ///<summary>
        ///책 정보 검색
        ///</summary>
        public void search(int field, string value)
        {
            foreach (var book in booklist)
            {
                switch ((BKFIELD)field)
                {
                    case BKFIELD.TITLE:
                        if (book.title == value) show(booklist.IndexOf(book));
                        break;
                    case BKFIELD.AUTHOR:
                        if (book.author == value) show(booklist.IndexOf(book));
                        break;
                    case BKFIELD.DATE:
                        if (book.date == value) show(booklist.IndexOf(book));
                        break;
                    case BKFIELD.PUBLISHER:
                        if (book.publisher == value) show(booklist.IndexOf(book));
                        break;
                    case BKFIELD.GENRE:
                        if (book.genre == value) show(booklist.IndexOf(book));
                        break;
                }
            }
        }

        ///<summary>
        /// 책 정보 수정
        ///</summary>
        public void edit(int index, int field, string value)
        {
            string[] arr = new string[(int)BKFIELD.BKFIELD_MAX] { 
                booklist[index].title, 
                booklist[index].author,
                booklist[index].date,
                booklist[index].publisher,
                booklist[index].genre,
            };

            arr[field] = value;

            booklist[index] = new Book()
            {
                title = arr[(int)BKFIELD.TITLE],
                author = arr[(int)BKFIELD.AUTHOR],
                date = arr[(int)BKFIELD.DATE],
                publisher = arr[(int)BKFIELD.PUBLISHER],
                genre = arr[(int)BKFIELD.GENRE],
            };
        }

        ///<summary>
        /// 책 정보 제거
        ///</summary>
        public void remove(int index)
        {
            booklist.RemoveAt(index);
        }

        ///<summary>
        /// 책 정보 보여주기
        ///</summary>
        public void show(int index)
        {
            Console.WriteLine($"{index}. {booklist[index].title} ({booklist[index].date})");
            Console.WriteLine($"  * Author: {booklist[index].author}");
            Console.WriteLine($"  * Genre: {booklist[index].genre}");
            Console.WriteLine($"  * Publisher: {booklist[index].publisher}");
        }

        ///<summary>
        /// 책 정보 저장
        ///</summary>
        public void save()
        {
            List<string> str = new();
            foreach (var book in booklist)
            {
                str.Add($"{book.title} {book.author} {book.date} {book.publisher} {book.genre}");
            }

            File.WriteAllLines(filepath, str);
        }

        ///<summary>
        ///데이터베이스 책 개수
        ///</summary>
        public int Length { get { return booklist.Count; } }
    }

    //==================================================
    // 책 구조체
    // : 책 정보를 컬렉션 형태가 아닌 정돈된 구조체로 정리한다.
    //==================================================
    struct Book
    {
        public string title;
        public string author;
        public string date;
        public string publisher;
        public string genre;
    }

    enum BKFIELD
    { 
        TITLE,
        AUTHOR,
        DATE,
        PUBLISHER,
        GENRE,
        BKFIELD_MAX
    }
}
