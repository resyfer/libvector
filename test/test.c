#include <libvector/vector.h>
#include <assert.h>
#include <stdio.h>

void push_back_test() {

	printf("\n!!--Vector Initialization Test--!!\n");

	int a = 10;

	vector_t *vec = vec_new();

	assert(vec != NULL);
	assert(vec->array == NULL);
	assert(vec->size == 0);
	assert(vec_size(vec) == 0);
	assert(vec->capacity == 0);

	printf("✅ Vector initialization\n");

	vec_push_back(vec, (void*) &a);

	assert(vec_size(vec) == 1);
	assert(vec->capacity == 1);

	printf("✅ Push back first element to vector\n");

	vec_push_back(vec, (void*) &a);

	assert(vec_size(vec) == 2);
	assert(vec->capacity == 2);

	printf("✅ Push back 2nd element to vector\n");

	vec_push_back(vec, (void*) &a);

	assert(vec_size(vec) == 3);
	assert(vec->capacity == 4);

	printf("✅ Push back 3rd element to vector\n");

	vector_t *new_vec = vec_new();
	vec_push_back(new_vec, (void*) &a);
	vec_push_back(new_vec, (void*) &a);
	vec_push_back(new_vec, (void*) &a);
	vec_push_back(new_vec, (void*) &a);
	vec_push_back(new_vec, (void*) &a);
	vec_push_back(new_vec, (void*) &a);

	vec_push_back_vec(vec, new_vec);

	assert(new_vec != NULL);
	assert(vec_size(new_vec) == 6);
	assert(new_vec->capacity == 8);
	assert(vec_size(vec) == 9);
	assert(vec->capacity == 16);

	printf("✅ Push back another vector to vector\n");
}

void insertion_test() {

	printf("\n!!--Insertion Test--!!\n");

	int b = 15;
	int a = 10;
	int index = 0;

	vector_t *vec = vec_new();

	vec_push_back(vec, (void*) &a);
	vec_push_back(vec, (void*) &a);
	vec_push_back(vec, (void*) &a);
	vec_push_back(vec, (void*) &a);

	assert(*((int*) vec_front(vec)) == a);
	vec_insert_at_index(vec, index, (void*) &b);

	assert(*((int*) vec_front(vec)) == b);
	assert(vec_size(vec) == 5);
	assert(vec->capacity == 8);

	printf("✅ Insert at index %d\n", index);

	index = 3;
	vec_insert_at_index(vec, index, (void*) &b);
	vec_insert_at_index(vec, index, (void*) &b);
	vec_insert_at_index(vec, index, (void*) &b);
	vec_insert_at_index(vec, index, (void*) &b);

	assert(*((int*) vec_get(vec, index)) == b);
	assert(vec_size(vec) == 9);
	assert(vec->capacity == 16);

	printf("✅ Insert at index %d\n", index);

	int count = 3;
	vec_insert_many_at_index(vec, index, count, &a, &b, &b);

	assert(*((int*) vec_get(vec, index)) == a);
	assert(*((int*) vec_get(vec, index+1)) == b);
	assert(*((int*) vec_get(vec, index+2)) == b);
	assert(vec_size(vec) == 12);
	assert(vec->capacity == 16);

	printf("✅ Insert many at index %d\n", index);
}

void test3() {

}

void test4() {

}

int main() {
	push_back_test();
	insertion_test();
	test3();
	test4();

	return 0;
}