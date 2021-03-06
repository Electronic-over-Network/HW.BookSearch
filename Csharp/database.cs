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

        public void add(Book book)
        {
            booklist.Add(book);
        }

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

        public void edit(int index, int field, string value)
        { 

        }

        public void remove(int index)
        {
            booklist.RemoveAt(index);
        }

        public void show(int index)
        {
            Console.WriteLine($"{index}. {booklist[index].title} ({booklist[index].date})");
            Console.WriteLine($"  * Author: {booklist[index].author}");
            Console.WriteLine($"  * Genre: {booklist[index].genre}");
            Console.WriteLine($"  * Publisher: {booklist[index].publisher}");
        }

        public void save()
        { 
        
        }

        // 데이터베이스 책 개수
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
    }
}
