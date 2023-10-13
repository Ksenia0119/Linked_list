#pragma once
//@author Maltseva K.V.
#include"AbstractIterator.h"
#include <iostream>
using namespace std;
//Класс узла списка
template<class T>
class Node {
public:
    T data;//поле данных узла
    Node<T>* next;//указатель на следующий узел
    Node<T>* prev;//указатель на предыдущий узел

    //конструктор класса с параметром
    Node(const T& data) {
        this->data = data;
        next = nullptr;
        prev = nullptr;
    }
};

//Класс двусвязного списка
template<class T>
class LinkedList :public Iterable<T> {
private:
    Node<T>* head;//указатель на голову списка
    Node<T>* tail;//указател  на хвост списка

public:
    //конструктор по умолчанию
    LinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    void InsertHead(const T& data);                            // Вставка в голову списка
    void InsertTail(const T& data);                            // Вставка в хвост списка
    void InsertAfter(const T& DataAfter, const T& data);       // Вставка узла после определенного значения
    void Print();                                              // Печать списка
    int Search(int data);                                      // Поиск узла со значением
    void Clear();                                              // Удаление списка
    void Remove(int data);                                     // Удаление узла
    void Sort();                                               // Сортировка выбором (возрастающий порядок)

  
   //класс итератора двусвязного списка
    template<class T>
    class ListIterator :public Iterator<T> {
    private:
        Node<T>* current;  // Указатель на текущий узел
    public:
        //Конструктор
        ListIterator(Node<T>* node) : current(node) {}

        // Оператор разыменования-доступа к данным
        T& operator*() const override {
            //возвращает данные текущего узла
            return current->data;
        }
        //Оператор инкремента
        ListIterator& operator++() override {
            //если текущий не равен nullptr
            if (current != nullptr) {
                //переходим к следующему узлу
                current = current->next;
            }
            //возвращаем ссылку на текущий объект
            return *this;
        }
        // Оператор равенства
        bool operator==(const Iterator<T>& other) const override {
            const ListIterator* otherIterator = dynamic_cast<const ListIterator*>(&other);
            return otherIterator && current == otherIterator->current;
        }
        // Оператор неравенства
        bool operator!=(const Iterator<T>& other) const override {
            return !(*this == other);
        }
        //// Итератор начала списка
        //ListIterator begin() const override {
        //    //возвращает итератор ,который указывает на головной узел списка
        //    return ListIterator(head);
        //}

        //// Итератор конца списка
        //ListIterator end() const override {
        //    //возвращает итератор,который указывает на позицию после последнего узла списка
        //    return ListIterator(nullptr);
        //}
      // Итератор начала списка
       

    };
    // Итератор начала списка
    ListIterator<T>& begin() const override {
        //возвращает итератор ,который указывает на головной узел списка
        return ListIterator<T>(head);
    }
    // Итератор начала списка
    ListIterator<T>&& end() const override {
        //возвращает итератор ,который указывает на головной узел списка
        return ListIterator<T>(nullptr);
    }

    //// Итератор конца списка
    //ListIterator<T> &end() const override {
    //    ListIterator<T> *n= new  ListIterator<T>(head);
    //    //возвращает итератор,который указывает на позицию после последнего узла списка
    //    return *n;
    //}
};


//реализация методов класса двусвязного списка
//вставка в голову списка
template<class T>
void LinkedList<T>::InsertHead(const T& data) {
    //создание нового узла
    Node<T>* newNode = new Node<T>(data);
    // Если список пустой,новый узел становится головным и хвостовым
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    }
    //иначе
    else {
        //привязываем новый узел к текущей голове
        newNode->next = head;
        // устанавливаем ссылку на предыдущий узел для текущей головы
        head->prev = newNode;
        // новый узел становится головным
        head = newNode;
    }

}
//вставка в хвост списка
template<class T>
void LinkedList<T>::InsertTail(const T& data) {
    //создание нового узла
    Node<T>* newNode = new Node<T>(data);
    // Если список пустой,новый узел становится головным и хвостовым
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    }
    else {
        // Привязываем новый узел к текущему хвосту
        tail->next = newNode;
        // Устанавливаем ссылку на предыдущий узел
        newNode->prev = tail;
        // Новый узел становится хвостовым
        tail = newNode;
    }
}

//вставка узла в список после определенного значения
template<class T>
void LinkedList<T>::InsertAfter(const T& DataAfter, const T& data) {
    //создание нового узла
    Node<T>* newNode = new Node<T>(data);  //текущий узел указывает на голову
    Node<T>* current = head;
    //пока текущий не равен nullptr
    while (current != nullptr) {
        //сравниваем данные в текущем узле с искомыми данными 
        if (current->data == DataAfter) {
            //если текущий равен хвосту
            if (current == tail) {
                tail = newNode;  // Обновляем хвост списка , если вставляем после хвостового узла
            }
            // Устанавливаем ссылку на предыдущий узел для нового узла
            newNode->prev = current;
            // Устанавливаем ссылку на следующий узел для нового узла
            newNode->next = current->next;
            if (current->next != nullptr) {
                // Устанавливаем ссылку на предыдущий узел для следующего узла
                current->next->prev = newNode;
            }
            // Устанавливаем ссылку на следующий узел для текущего узла
            current->next = newNode;
            return;
        }
        // Переходим к следующему узлу
        current = current->next;
    }
}
//печать списка
template<class T>
void LinkedList<T>::Print() {
    // Установка текущего узла на голову списка
    Node<T>* current = head;
    while (current != nullptr) {
        // Выводим данные текущего узла
        cout << current->data << " ";
        // Переходим на следующий узел
        current = current->next;
    }
    cout << endl;
}
//поиск узла со значением
template<class T>
int LinkedList<T>::Search(int data) {
    // Установка текущего узла на голову списка
    Node<T>* current = head;
    //пока текущий не равен nullptr
    while (current != nullptr) {
        //если данные в текущем узле равны искомым
        if (current->data == data) {
            // Возвращаем текущий узел,если элемент найден
            return current->data;
        }
        // Переходим к следующему узлу
        current = current->next;
    }
    // Если элемент не найден, возвращаем -1
    return -1;
}
//удаление списка
template<class T>
void LinkedList<T>::Clear() {
    while (head != nullptr) {
        Node<T>* current = head;
        head = head->next;
        delete current;

    }
    tail = nullptr;
}
//удаление узла
template<class T>
void LinkedList<T>::Remove(int data) {
    // Установка текущего узла на голову списка
    Node<T>* current = head;
    //пока текущий не равен nullptr
    while (current != nullptr) {
        //если данные в текущем узле равны искомым
        if (current->data == data) {
            //если текущий узел головной
            if (current == head) {
                // Обновляем голову списка,если удаляемый элемент- головной узел
                head = current->next;
            }
            //если текущии узел хвост
            if (current == tail) {
                // Обновляем хвост списка, если удаляемый элемент - хвостовой узел
                tail = current->prev;
            }
            //если у текущего предыдущий не равен nullptr
            if (current->prev != nullptr) {
                // Обновляем  ссылку на следующий узел ,для предыдущего узла
                current->prev->next = current->next;
            }
            //если у текущего следующийне равен nullptr
            if (current->next != nullptr) {
                // Обновляем ссылку на предыдущий узел для следующего узла
                current->next->prev = current->prev;
            }
            // Удаляем текущий узел
            delete current;
            return;
        }
        // Переходим к следующему узлу
        current = current->next;
    }
}

// Сортировка выбором(возрастающий порядок)
template<class T>
void LinkedList<T>::Sort() {
    // Установка текущего узла на голову списка
    Node<T>* current = head;
    //пока текущий не равен nullptr
    while (current != nullptr) {
        // Установка минимального узла на текущий узел
        Node<T>* minNode = current;
        // Установка временного указателя на следующий узел
        Node<T>* temp = current->next;
        //пока следующий узел не равен nullptr
        while (temp != nullptr) {
            if (temp->data < minNode->data) {
                // Обновление минимального узла, если найден узел с меньшим значением
                minNode = temp;
            }
            // Переход к следующему узлу
            temp = temp->next;
        }
        if (minNode != current) {
            // Обмен значениями узлов
            int tempData = current->data;
            current->data = minNode->data;
            minNode->data = tempData;
        }
        current = current->next;
    }
}