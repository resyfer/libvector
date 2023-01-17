#include <libvector/vector.h>
#include <stdio.h>

int main() {

	// Initialize empty vector instance
	vector_t *vec = vec_new();

	// Add an element of any data type to the end of the vector
	char a = 10;
	vec_push_back(vec, (void*) &a);

	int b = 15;
	vec_push_back(vec, (void*) &b);

	char *c = "hello world";
	vec_push_back(vec, (void*) c);

	// Remove the last element from vector
	char *d = vec_pop_back(vec);
	printf("%s\n", d);

	// Get element at an index
	int *e = vec_get(vec, 1);
	printf("%d\n", *e);

	// Update value of element at index
	int f = 30;
	int *g = vec_set(vec, 1, &f);
	printf("%d\n", *g);

	// Get first element of vector.
	int *h = vec_back(vec);
	printf("%d\n", *h);

	// Get last element of vector.
	int *i = vec_back(vec);
	printf("%d\n", *i);

	// Check documentation for further operations on vectors.

	// Free the vector
	vec_free(vec);

	return 0;
}