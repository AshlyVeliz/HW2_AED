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
        if (index < 0 || index > size()) {
            cout << "Indice fuera de rango." << endl;
            return;
        }
        if (index == 0) {
            push_front(val);
            return;
        }
        if (index == size()) {
            push_back(val);
            return;
        }
        Node* newNode = new Node(val);
        Node* current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        newNode->prev = current;
        current->next->prev = newNode;
        current->next = newNode;

    }

    void remove(int index) {
        // Implementar: Elimina elemento en posición indicada
        if (index < 0 || index >= size()) {
            cout << "Indice fuera de rango." << endl;
            return;
        }
        if (index == 0) {
            pop_front();
            return;
        }
        if (index == size() - 1) {
            pop_back();
            return;
        }
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
    }

    T operator[](int index) {
        // Implementar: Acceso a elemento por índice
        if (index < 0 || index >= size()) {
            cout << "Indice fuera de rango." << endl;
            exit(1);
        }

        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data ;
    }


};
