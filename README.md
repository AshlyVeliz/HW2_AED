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
- **Caso vacío:**  
  Crea un único nodo que se enlaza a sí mismo en `next` y `prev`, y asigna `head` y `tail` a ese nodo.
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
