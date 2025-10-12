# 🔗 LinkedListLib
**LinkedListLib** is a versatile C library implementing a **singly linked list** that can store **arrays of multiple primitive types** (`int`, `float`, `char`).  
Each list element can hold an **array of arbitrary length**, and the library provides an interface for adding, removing, copying, printing, and freeing memory.

---

## 📁 Project Structure
```
.
├── linkedlistlib.h   # Header file
├── linkedlistlib.c   # Implementation file
└── main.c            # Example usage
```

---

## ⚙️ Data Structure
```c
typedef struct listelement
{
    long length;       // Length of the array
    void *el;          // Pointer to the array
    char type;         // 'i' - int, 'f' - float, 'c' - char
    struct listelement *next; // Next list element
} listelement;
```

Each node contains:
- **an array of values** (`el`)
- **its length** (`length`)
- **data type** (`type`)
- **pointer to the next element** (`next`)

---

## 🧠 Library Functions

### 1. `append()`
```c
listelement* append(void *value, long length, char type, listelement *pn, long pos);
```
Adds a new array element to the list at the specified position.

| Parameter | Description |
|------------|-------------|
| `value` | Pointer to the array or element to insert |
| `length` | Number of elements in the array |
| `type` | Data type: `'i'`, `'f'`, `'c'` |
| `pn` | Pointer to the start of the list (or `NULL` to create a new list) |
| `pos` | Insertion position (`0` for start, `-1` for end) |

🔹 **Returns:** pointer to the updated list head.  
🔹 **NULL** if the insertion fails.

---

### 2. `pop()`
```c
listelement* pop(listelement *pn, long pos);
```
Removes an element from position `pos`.  
If `pos = -1`, removes the last element.

🔹 **Returns:** updated list pointer or `NULL` if empty or invalid position.

---

### 3. `len()`
```c
long len(listelement *pn);
```
Counts the number of elements in the list.  
🔹 **Returns:** list length (`long`).

---

### 4. `copyarr()`
```c
int copyarr(void *to, void *from, char type, long length);
```
Copies the contents of one array into another, respecting the data type.

🔹 **Returns:** `0` on success.

---

### 5. `retel()`
```c
listelement* retel(listelement *st, long pos);
```
Returns a pointer to the element at position `pos`.

🔹 **Returns:** pointer to the element, or `NULL` if invalid.

---

### 6. `printel()`
```c
int printel(listelement* pn, char btw[]);
```
Prints all array elements from a single node, separated by the string `btw`.

🔹 **Returns:** `0` on success, `1` if `pn == NULL`.

---

### 7. `printlist()`
```c
int printlist(listelement* pn, char btw[], char after[]);
```
Prints the entire list.  
`btw` — separator between elements,  
`after` — separator between arrays.

🔹 **Returns:** `0` on success.

---

### 8. `rmlist()`
```c
int rmlist(listelement *pn);
```
Frees all memory allocated for the list.

🔹 **Returns:** `0` after freeing memory.  
(You should set `pn = NULL` after calling this function.)

---

## 🧩 Example Usage (`main.c`)
```c
#include <stdio.h>
#include <string.h>
#include "linkedlistlib.h"

int main(void)
{
    int one[] = {1, 2, 3};
    char two[] = "two";
    float three = 3.7896;
    int four = 4;
    char five = '5';

    // Create and append elements
    listelement *st = append(one, 3, 'i', NULL, 0);
    st = append(two, strlen(two), 'c', st, 1);
    st = append(&three, 1, 'f', st, 2);
    st = append(&four, 1, 'i', st, 3);
    st = append(&five, 1, 'c', st, 4);

    // Print list
    printlist(st, "; ", "\n");

    // Length
    printf("List length: %ld\n", len(st));

    // Access and print a specific element
    printel(retel(st, 1), "; ");
    printf("\n");

    // Remove last element
    st = pop(st, -1);

    // Updated list
    printlist(st, "; ", "\n");

    // Free all memory
    rmlist(st);
    st = NULL;

    return 0;
}
```

---

## 🛠️ Compilation
```bash
gcc main.c linkedlistlib.c -o program
./program
```

---

## 📦 Features
- Supports **multiple data types** within the same list.
- Simple and minimal API in pure C.
- Manual memory control for flexibility.
- Ideal for dynamic data management and testing linked structures.

---

## ⚠️ Limitations
- No nested or custom user-defined types.
- Only shallow copies of arrays (no deep copy for structures).
- Type must match when printing; mismatches may produce undefined output.

---

## 🧾 License
Free for educational, research, or personal use.
