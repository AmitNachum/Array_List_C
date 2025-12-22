# Dynamic Array (C) — TerraWine / Coursework Utility

A small **dynamic array / “ArrayList-like” container written in C**.
It stores elements in a single contiguous buffer (`void* data`) and grows/shrinks with `realloc()` as items are appended or removed.

This is **not** Java’s `ArrayList` or C++ templates:

* C has **no runtime type information** for `void*` buffers.
* You must provide the **element size** and (optionally) **function pointers** for operations like equality, printing, and sorting.

---

## What this project includes

* **Generic storage** via `void*` + `size_of_data`
* **Append** (auto-expand when full)
* **Remove one** (shift or swap-with-last style, depending on your implementation)
* **Remove all occurrences**
* **Contains / search** using an injected `equals` function
* **Optional printing** via an injected `print` function
* **Optional sorting** via `qsort()` using an injected `compare`
* **Shrink** policy to reduce capacity when utilization drops below a threshold

---

## Design overview

### Core idea

* Allocate `data = malloc(size_of_data * capacity)`
* Keep metadata:

  * `length` = number of valid elements
  * `capacity` = allocated slots
  * `size_of_data` = element size in bytes

### Generic behavior via function pointers

Because C can’t know element types at runtime, you inject behaviors:

* `equals(const void*, const void*)` → used by `contains`, `remove`, `remove_all`
* `print(const void*, int)` (or similar) → used by `print_array`
* `compare(const void*, const void*)` → used by `qsort`

---

## Building

### Linux / macOS

```bash
make
./out
```

### Windows (MinGW/MSYS2)

1. Install **MSYS2** and the MinGW toolchain (or another GCC distribution).
2. Open the **MSYS2 MinGW64** shell.
3. From the project folder:

```bash
make
```

If you don’t use `make`, compile manually:

```bash
gcc -Wall -Wpedantic -Werror -g -o out main.c Dynamic_Array.c
```

---

## Usage (high level)

Typical flow:

1. Create the list with `init_list(sizeof(T), initialCapacity, equalsFn, printFn, compareFn)`
2. Call `da_append(...)` to add elements
3. Use `da_remove(...)` / `remove_element(...)` and `remove_all(...)`
4. Use `print_array(...)` if you provided a print function
5. Call `destructor_arraylist(...)` when done

---

## Important notes / limitations

* **Not type-safe**: if you pass the wrong `size_of_data` or wrong function pointers, you’ll get undefined behavior.
* **No deep-copy semantics** unless you implement them yourself (e.g., for structs containing heap pointers).
* **Realloc can move memory**: never keep long-lived pointers into the internal buffer across operations that may resize.
* **Remove strategy matters**:

  * *Shift-left* preserves order but costs O(n) per removal.
  * *Swap-with-last* is O(1) but changes order.
* **Sorting** requires a proper `compare` function that returns `<0`, `0`, `>0`.

---

## File layout

* `Dynamic_Array.h` — public API, struct definition, macros
* `Dynamic_Array.c` — implementation
* `main.c` — demo / sanity checks
* `Makefile` — build rules

---

## If you want, next steps

* Add `get(index)` / `set(index)` with bounds checking
* Add `reserve(newCapacity)`
* Add `clear()`
* Add optional “stable remove” vs “unstable remove” modes
* Add debug asserts + invariant checks (capacity >= length, etc.)

---

### Note

I wrote this README based on the API/function names you’ve been using in chat. If you re-upload the latest files and you want the README to match the *exact* signatures/comments, I can align it precisely.
