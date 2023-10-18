//@author Maltseva K.V.

#include "LinkedList.h"
#include"TestIteratorLinkedList.h"

int main() {

    setlocale(LC_ALL, "rus");
    //создаем лист
    
    LinkedList<int> list;
    list.InsertTail(7);
    list.InsertHead(10);
    list.InsertTail(44);
    list.InsertTail(21);
    list.InsertHead(11);
    list.InsertAfter(44, 56);
    list.Print();

   for (auto it = list.begin(); it != list.end(); ++it) {
       cout << *it << " ";
    }
   // Поиск элемента
   
 
   cout << "Элемент " << list.Search(66) << " найден" <<endl;
   cout << "Элемент " << list.Search(11) << " найден" << endl;

    list.Print();

  
    list.Remove(44);
    list.Print();

    cout << "Исходный список: " << endl;;
    list.Print();

   cout << "Отсортированный список: "<<endl;
   list.Sort();
   list.Print();

   TestLinkedListBegin();
   TestDataOperator();
   TestIncOperator();
   TestOperatorEqual();
   TestOperatorUnequal();
   TestLinkedListEnd();
    return 0;
}