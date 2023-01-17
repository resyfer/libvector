# libvector

A vector library for C. Easy to use as well as takes in any data type.For
instructions on usage, please go [here](#usage) and for examples visit this
[file](/examples/example.c)

For installation, please go [here](#installation). For documentation, please go
[here](#documentation).

## Usage

Compile and run:

```bash
$ gcc test.c -o test.o -lvector
$ ./test.o
```

### Step 1

Import the library:

```c
#include <libvector/vector.h>
```

**NOTE**: Link the library and dependencies when compiling

```bash
$ gcc a.c -o a.o -lvector
```

### Step 2

#### Push

To push an element at the back of the vector:

```c
char a = 10;
vec_push_back(vec, (void*) &a);
```

#### Pop

To pop an element from the back of the vector:

```c
char *b = vec_pop_back(vec);
printf("%s\n", b);
```

#### Get

To get an element at `index`:

```c
int *c = vec_get(vec, 1);
printf("%d\n", *c);
```

### Set

To set an element at `index`:

```c
int d = 30;
int *e = vec_set(vec, 1, &d);
printf("%d\n", *e);
```

**NOTE**: The value returned from `vec_set` is the older value of the element at `index` in the vector, ie. value before updating it to `d`.

**NOTE**: It is good practice to use `free` using the returned pointer to older value if you added any elements to the vector that were dynamically allocated. This is the reason why it returns it at all.

### Step 3

Free the vector after use:

```c
vec_free(vec);
```

## Installation

Make sure to have [make](https://www.gnu.org/software/make/), [gcc](https://www.gnu.org/software/gcc/) and [git](https://git-scm.com/) installed.

```bash
git clone https://github.com/resyfer/libvector.git
cd libvector
make install
cd ..
rm -rf libvector
```

Provide the password when prompted.

## Documentation

### Intialization

```c
vector_t* vec_new(void); //Initialize empty vector
vector_t* vec_new_size(u_int32_t size); //Initialize with some initial size
```

### Push-Pop

```c
void vec_push_back(vector_t* vec, void* value);
void* vec_pop_back(vector_t* vec);
```

### Get-Set

```c
void* vec_get(vector_t* vec, u_int32_t index);
void* vec_set(vector_t* vec, u_int32_t index, void *value);
```

### Free

```c
void vec_free(vector_t* vec);
```

**NOTE**: This does **not** free the individual elements of the vector. If you've dynamically allocated them, it's you're responsibility to deallocate them _before_ freeing the vector with this.

### Miscellaneous

```c
void* vec_front(vector_t* vec); // Returns first element
void* vec_back(vector_t* vec); // Returns last element
u_int32_t vec_size(vector_t* vec); // Returns size of vector
void vec_shrink(vector_t* vec); // Shrinks the internal array to the number of elements pushed in it.
```
