# HW2_AED
## Members:
1. Ashly Veliz 
2. Steve Ricapa
3. Abel Escóbar 
4. Darlene Escobar

# Functions for a Circular Doubly Linked List

## 1. T front()
A simple function. We just simple returns the head's value if there's a head node.

```cpp
    T front() {


        if (!empty()) return head->val;

        return;

    }
```
## 2. T back()
A simple function. Implemented by taking advantage of the head's connection with the last node.
```cpp
    T back() {

        if (!empty()){

            return head->prev->val;

        }

    }
```
## 3. void push_front()

Implemented by considering two cases : 1. Where there's no head node and 2. When there's a head node. We handle the pointers prev and next for properly insert the new node at the beginning of the CDLL.
```cpp

    void push_front(T val) {

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
```


#### The homework

![[Pasted image 20250426200336.png]]