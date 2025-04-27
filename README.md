# HW2_AED

## Members
- Ashly Veliz
- Steve Ricapa
- Abel Escóbar
- Darlene Escobar

---

# Functions for a Circular Doubly Linked List

## 1. `T front()`
A simple function. We just return the head’s value if there’s a head node.

```cpp
T front() {
    if (!empty()) return head->val;
    return;
}
```

---

## 2. `T back()`
A simple function. Implemented by taking advantage of the head’s connection with the last node.

```cpp
T back() {
    if (!empty()) {
        return head->prev->val;
    }
}
```

---

## 3. `void push_front(T val)`
Implemented by considering two cases:  
1. **Lista vacía**: crea el único nodo y lo enlaza a sí mismo.  
2. **Lista no vacía**: inserta el nuevo nodo al inicio ajustando `prev` y `next`.

```cpp
void push_front(T val) {
    Node* aux = new Node(val);
    if (empty()) {
        head = aux;
        tail = aux;
        aux->next = aux;
        aux->prev = aux;
    }
    else {
        aux->next = head;
        aux->prev = tail;
        head->prev = aux;
        tail->next = aux;
        head = aux;
    }
}
```

---

## 4. `void push_back(T val)`
- **Caso vacío:** crea un único nodo que se enlaza a sí mismo en `next` y `prev`, y asigna `head` y `tail` a ese nodo.  
- **Caso general:**  
  1. Crea `aux` con el nuevo valor.  
  2. Ajusta `aux->prev = tail` y `aux->next = head`.  
  3. Apunta `tail->next` a `aux` y `head->prev` a `aux`.  
  4. Actualiza `tail = aux`.

```cpp
void push_back(T val) {
    Node* aux = new Node(val);
    if (empty()) {
        head = aux;
        tail = aux;
        aux->next = aux;
        aux->prev = aux;
    } else {
        aux->prev  = tail;
        aux->next  = head;
        tail->next = aux;
        head->prev = aux;
        tail       = aux;
    }
}
```

---

## 5. `T pop_front()`
- Si la lista está vacía, devuelve el valor por defecto (`T()`).  
- Guarda en `ret` el dato de `head`.  
- **Un solo nodo:** tras eliminarlo, deja `head` y `tail` en `nullptr`.  
- **Múltiples nodos:**  
  1. Avanza `head = head->next`.  
  2. Reenlaza `head->prev = tail` y `tail->next = head`.  
- Elimina el nodo antiguo y retorna `ret`.

```cpp
T pop_front() {
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
```

---

## 6. `T pop_back()`
- Comportamiento análogo a `pop_front`, pero sobre `tail`:  
  1. Guarda el dato de `tail`.  
  2. **Un solo nodo:** deja la lista vacía.  
  3. **Varios nodos:** retrocede `tail = tail->prev` y ajusta los enlaces circulares (`tail->next = head`, `head->prev = tail`).  
- Elimina el nodo viejo y retorna el valor.

```cpp
T pop_back() {
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
```
---

## 7. `void insert(T val, int index)`
Inserta un nuevo nodo con el valor `val` en la posición especificada `index`.  
- Si el índice es inválido, muestra un error.  
- Inserta al inicio o al final si el índice es `0` o igual al tamaño de la lista.  
- Para índices intermedios, recorre la lista y ajusta los punteros de los nodos.

```cpp
void insert(T val, int index) {
    if (index < 0 || index > size()) {
        cout << "Índice fuera de rango." << endl;
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
```

---

## 8. `void remove(int index)`
Elimina el nodo en la posición `index`.  
- Si el índice es inválido, muestra un error.  
- Elimina el primer o último nodo usando `pop_front` o `pop_back`.  
- Para nodos intermedios, recorre la lista, ajusta los punteros adyacentes y libera la memoria.

```cpp
void remove(int index) {
    if (index < 0 || index >= size()) {
        cout << "Índice fuera de rango." << endl;
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
```

---

## 9. `T operator[](int index)`
Permite acceder al valor almacenado en la posición `index` usando la notación de arreglo.  
- Si el índice es inválido, muestra un error y finaliza el programa.  
- Recorre la lista hasta el nodo deseado y devuelve su valor.

```cpp
T operator[](int index) {
    if (index < 0 || index >= size()) {
        cout << "Índice fuera de rango." << endl;
        exit(1); // O lanzar excepción
    }
    Node* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}
```

## 10. `bool empty()`
Comprueba si la lista está vacía, es decir, si no contiene ningún nodo.

```cpp
bool empty() {
    return head == nullptr;
}
```


---

## 11. `int size()`
Recorre la lista de manera circular para contar cuántos nodos contiene:
1. Si `head == nullptr`, retorna `0`.  
2. Comienza en `head`, avanza mediante `current = current->next` y aumenta un contador.  
3. Continúa hasta volver a `head`, entonces retorna el contador.

```cpp
int size() {
    if (empty()) return 0;
    int count = 1;
    Node* current = head->next;
    while (current != head) {
        ++count;
        current = current->next;
    }
    return count;
}
```
---

## 12. `void clear()`
Elimina todos los nodos y deja la lista vacía:
1. Mientras `head != nullptr`, guarda `temp = head`.  
2. Avanza `head = head->next`.  
3. Libera `temp`.  
4. Al finalizar, asigna `tail = nullptr`.

```cpp
void clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
}
```
---
## 13. `void reverse() `
Invierte el sentido de la lista cambiando `next` y `prev` en cada nodo, y luego permuta `head` y `tail`:
1. Si la lista está vacía, retorna inmediatamente.  
2. Recorre cada nodo (hasta volver a `head`):  
   - Intercambia `node->next` y `node->prev`.  
   - Avanza `node = node->prev` (antes `next`) para continuar el recorrido.  
3. Finalmente, `swap(head, tail)`.

```cpp
void reverse() {
    if (empty()) return;
    Node* current = head;
    do {
        std::swap(current->next, current->prev);
        current = current->prev; // antes next, ahora prev
    } while (current != head);
    std::swap(head, tail) ;
}
```
