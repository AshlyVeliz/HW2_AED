#include <iostream>
using namespace std;

template <typename T> // A DLL that capable to store general data
class DoubleLinkedList { 
private:
    struct Node {
        T data; 
        Node* prev;
        Node* next;
        Node(T val) : data(val), prev(nullptr), next(nullptr) {}
    };
    Node* head; 
    Node* tail;


public:
    DoubleLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoubleLinkedList() {
        clear();
    }

    bool empty() {
        return head == nullptr;
    }

    int size() {
        int size = 0;
        Node* current = head;
        while (current != nullptr) {
            size++;
            current = current->next;
        }
        return size;
    }

    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }

    T front() {
        // Implementar: Retorna el primer elemento
        if (!empty()) return head->val;
        return;
    }

    T back() {
        // Implementar: Retorna el último elemento
        if (!empty()){
            return head->prev->val;
        }
        
    }

    void push_front(T val) {
        // Implementar: Agrega elemento al inicio
        Node* aux = new Node(val);
        if(empty()){
            head = aux;
            tail = aux;
            aux ->next = aux;
            aux->prev = aux;
        }
        else{
            aux->next = head;
            aux -> prev = tail;
    
    
            head->prev = aux; // wont requere to update forward. Just backwards
            tail->next = aux;
            head = aux;
        }
        
    }

    void push_back(T val) {
        // Implementar: Agrega elemento al final
        Node* aux = new Node(val);
        if (empty()) {
            head = aux;
            tail = aux;
            aux->next = aux;
            aux->prev = aux;
        } else {
            aux->prev        = tail;
            aux->next        = head;
            tail->next       = aux;
            head->prev       = aux;
            tail             = aux;
        }
    }

    T pop_front() {
        // Implementar: Remueve y retorna el primer elemento
        if (empty()) return T();
        Node* aux = head;
        T ret    = aux->data;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = tail;
            tail->next = head;
        }
        delete aux;
        return ret;
    }

    T pop_back() {
        // Implementar: Remueve y retorna el último elemento
        if (empty()) return T();
        Node* aux = tail;
        T ret    = aux->data;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = head;
            head->prev = tail;
        }
        delete aux;
        return ret;
    }

    void insert(T val, int index) {
        // Implementar: Inserta elemento en posición indicada
    }

    void remove(int index) {
        // Implementar: Elimina elemento en posición indicada
    }

    T operator[](int index) {
        // Implementar: Acceso a elemento por índice
    }

    void reverse() {
        // Implementar: Invierte el orden de la lista
    }
};