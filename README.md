# libvector

A vector library for C. Easy to use as well as takes in any data type. For instructions on usage, please go [here](#usage).

For installation, please go [here](#installation). For documentation, please go [here](#documentation).

## Usage

### TL;DR

The shown below is a tl;dr version. Proper instructions are [here](#step-1)

```c
#include <libvector/libvector.h>
#include <stdio.h>

int main() {
	struct vector *vec = vec_new();

	char a = 10;
	vec_push_back(vec, (void*) &a);

	int b = 15;
	vec_push_back(vec, (void*) &b);

	char *c = "hello world";
	vec_push_back(vec, (void*) c);

	int *d = vec_get(vec, 1);
	printf("%d\n", *d);

	char *e = vec_pop_back(vec);
	printf("%s\n", e);

	int f = 30;
	int *g = vec_set(vec, 1, &f);
	printf("%d\n", *g);

	int *h = vec_back(vec);
	printf("%d\n", *h);

	vec_free(vec);

	return 0;
}
```

Compile and run:

```bash
$ gcc test.c -o test.o -lvector
$ ./test.o
```

### Step 1

Import the library:

```c
#include <libvector/libvector.h>
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

Install all the the dependencies before moving on the next step (preferably in the same order as given below):

- [libqueue](https://github.com/resyfer/libqueue.git)

**NOTE**: Their installation instructions will be provided in their documentation as well.

After installing dependencies, installation of library:

```bash
git clone https://github.com/resyfer/libtpool.git
cd libtpool
make install
cd ..
rm -rf libtpool
```

Provide the password when prompted.

## Documentation

### Intialization

```c
struct vector* vec_new(void); //Initialize empty vector
struct vector* vec_new_size(u_int32_t size); //Initialize with some initial size
```

### Push-Pop

```c
void vec_push_back(struct vector* vec, void* value);
void* vec_pop_back(struct vector* vec);
```

### Get-Set

```c
void* vec_get(struct vector* vec, u_int32_t index);
void* vec_set(struct vector* vec, u_int32_t index, void *value);
```

### Free

```c
vec_free(vec);
```

**NOTE**: This does **not** free the individual elements of the vector. If you've dynamically allocated them, it's you're responsibility to deallocate them _before_ freeing the vector with this.

### Miscellaneous

```c
void* vec_front(struct vector* vec); // Returns first element
void* vec_back(struct vector* vec); // Returns last element
u_int32_t vec_size(struct vector* vec); // Returns size of vector
void vec_shrink(struct vector* vec); // Shrinks the internal array to the number of elements pushed in it.
```
