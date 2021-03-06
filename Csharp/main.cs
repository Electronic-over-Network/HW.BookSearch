using System;

namespace HW.BookSearch
{
    class Program
    {
        /* 시작점
        프로그램이 시작되는 함수이다. */
        static void Main()
        {   
            var _ = new Application("booklist.txt");
        }
    }

    class Application
    {
        private readonly Database database;

        public Application(string filepath)
        {
            database = new(filepath);
            SetupUI();
        }

        ///<summary>
        ///사용자 인터페이스: 메뉴
        ///</summary>
        private void SetupUI()
        {
            while (true)
            {
                Console.WriteLine("=====================");
                Console.WriteLine("|      OPTIONS      |");
                Console.WriteLine("| ----------------- |");
                Console.WriteLine("| 1. Add            |");
                Console.WriteLine("| 2. Search         |");
                Console.WriteLine("| 3. Edit           |");
                Console.WriteLine("| 4. Remove         |");
                Console.WriteLine("| 5. List           |");
                Console.WriteLine("| 6. Save           |");
                Console.WriteLine("| 7. Exit           |");
                Console.WriteLine("=====================");
                Console.Write("Select from the menu: ");

                int option;
                try
                {
                    option = Convert.ToInt32(Console.ReadLine());
                }
                catch (FormatException)
                {
                    Console.WriteLine("Invalid input.\n");
                    continue;
                }

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
                        Console.WriteLine("Invalid input.");
                        break;
                }
                Console.WriteLine();
            }
        }

        ///<summary>
        ///사용자 인터페이스: 1. 도서 추가
        ///</summary>
        private void add()
        {
            Console.Write(">> Enter the title: ");
            string title = Console.ReadLine();

            Console.Write(">> Enter the author: ");
            string author = Console.ReadLine();

            Console.Write(">> Enter the published date: ");
            string date = Console.ReadLine();

            Console.Write(">> Enter the publisher: ");
            string publisher = Console.ReadLine();

            Console.Write(">> Enter the genre: ");
            string genre = Console.ReadLine();

            database.add(new Book()
            {
                title = title,
                author = author,
                date = date,
                publisher = publisher,
                genre = genre
            });

            Console.WriteLine("Book added!");
        }

        ///<summary>
        ///사용자 인터페이스: 2. 도서 검색
        ///</summary>
        private void search()
        {
            Console.WriteLine($"  {(int)BKFIELD.TITLE}. Title");
            Console.WriteLine($"  {(int)BKFIELD.AUTHOR}. Author");
            Console.WriteLine($"  {(int)BKFIELD.DATE}. Published date");
            Console.WriteLine($"  {(int)BKFIELD.PUBLISHER}. Publisher");
            Console.WriteLine($"  {(int)BKFIELD.GENRE}. Genre");

            try
            {
                Console.Write(">> Select the book field to search: ");
                int field = Convert.ToInt32(Console.ReadLine());

                Console.Write(">> Enter the book field content to search:");
                string value = Console.ReadLine();

                database.search(field, value);
            }
            catch (FormatException)
            {
                Console.WriteLine("Invalid input.");
            }
        }

        ///<summary>
        ///사용자 인터페이스: 3. 도서 정보 수정
        ///</summary>
        private void edit()
        {
            try
            {
                Console.Write(">> Select the book to edit: ");
                int index = Convert.ToInt32(Console.ReadLine());

                if (index < database.Length && !(index < 0))
                {
                    Console.WriteLine($"  {(int)BKFIELD.TITLE}. Title");
                    Console.WriteLine($"  {(int)BKFIELD.AUTHOR}. Author");
                    Console.WriteLine($"  {(int)BKFIELD.DATE}. Published date");
                    Console.WriteLine($"  {(int)BKFIELD.PUBLISHER}. Publisher");
                    Console.WriteLine($"  {(int)BKFIELD.GENRE}. Genre");

                    Console.Write(">> Select the book field to search: ");
                    int field = Convert.ToInt32(Console.ReadLine());
                    if (field < (int)BKFIELD.BKFIELD_MAX && !(field < 0))
                    {
                        Console.Write(">> Enter a new content for the field: ");
                        string value = Console.ReadLine();

                        database.edit(index, field, value);
                    }
                    else
                    {
                        Console.WriteLine("Invalid book field.");
                    }
                }
                else
                {
                    Console.WriteLine("Unable to find a book from the index.");
                }
            }
            catch (FormatException)
            {
                Console.WriteLine("Invalid input.");
            }
        }

        ///<summary>
        ///사용자 인터페이스: 4. 도서 삭제
        ///</summary>
        private void remove()
        {
            show();

            int index;
            Console.Write(">> Select the book to remove: ");
            try
            {
                index = Convert.ToInt32(Console.ReadLine());
                if (index < database.Length && !(index < 0))
                {
                    database.remove(index);
                    Console.WriteLine("Book removed!");
                }
                else
                {
                    Console.WriteLine("Unable to find a book from the index.");
                }
            }
            catch (FormatException)
            {
                Console.WriteLine("Invalid input.");
            }
        }

        ///<summary>
        ///사용자 인터페이스: 5. 현재 총 도서 목록
        ///</summary>
        private void show()
        {
            for (int index = 0; index < database.Length; index++)
            {
                database.show(index);
            }
        }

        ///<summary>
        ///사용자 인터페이스: 6. 저장
        ///</summary>
        private void save()
        {
            database.save();
            Console.WriteLine("Book saved!");
        }
    }
}
