#include <libvector/vector.h>
#include <assert.h>
#include <stdio.h>

void push_back_test() {

	printf("\n!!--Vector Push Back Test--!!\n");

	int a = 10;

	vector_t vec;
	vec_new(&vec);

	assert(vec.array == NULL);
	assert(vec.size == 0);
	assert(vec_size(&vec) == 0);
	assert(vec.capacity == 0);

	printf("✅ Vector initialization\n");

	vec_push_back(&vec, (void*) &a);

	assert(vec_size(&vec) == 1);
	assert(vec.capacity == 1);

	printf("✅ Push back first element to vector\n");

	vec_push_back(&vec, (void*) &a);

	assert(vec_size(&vec) == 2);
	assert(vec.capacity == 2);

	printf("✅ Push back 2nd element to vector\n");

	vec_push_back(&vec, (void*) &a);

	assert(vec_size(&vec) == 3);
	assert(vec.capacity == 4);

	printf("✅ Push back 3rd element to vector\n");

	vector_t new_vec;
	vec_new(&new_vec);
	vec_push_back(&new_vec, (void*) &a);
	vec_push_back(&new_vec, (void*) &a);
	vec_push_back(&new_vec, (void*) &a);
	vec_push_back(&new_vec, (void*) &a);
	vec_push_back(&new_vec, (void*) &a);
	vec_push_back(&new_vec, (void*) &a);

	vec_push_back_vec(&vec, &new_vec);

	assert(vec_size(&new_vec) == 6);
	assert(new_vec.capacity == 8);
	assert(vec_size(&vec) == 9);
	assert(vec.capacity == 16);


	printf("✅ Push back another vector to vector\n");

	vec_free(&new_vec);
	vec_free(&vec);

	printf("✅ Free vector\n");
}

void insertion_test() {

	printf("\n!!--Insertion Test--!!\n");

	int b = 15;
	int a = 10;
	int index = 0;

	vector_t vec;
	vec_new_cap(&vec, 2);

	assert(vec_size(&vec) == 0);
	assert(vec.capacity == 2);

	printf("✅ Vector initialization with capacity\n");

	vec_push_back(&vec, (void*) &a);
	vec_push_back(&vec, (void*) &a);
	vec_push_back(&vec, (void*) &a);
	vec_push_back(&vec, (void*) &a);

	assert(*((int*) vec_front(&vec)) == a);
	vec_insert_at_index(&vec, index, (void*) &b);

	assert(*((int*) vec_front(&vec)) == b);
	assert(vec_size(&vec) == 5);
	assert(vec.capacity == 8);

	printf("✅ Insert at index %d\n", index);

	index = 3;
	vec_insert_at_index(&vec, index, (void*) &b);
	vec_insert_at_index(&vec, index, (void*) &b);
	vec_insert_at_index(&vec, index, (void*) &b);
	vec_insert_at_index(&vec, index, (void*) &b);

	assert(*((int*) vec_get(&vec, index)) == b);
	assert(vec_size(&vec) == 9);
	assert(vec.capacity == 16);

	printf("✅ Insert at index %d\n", index);

	int count = 3;
	vec_insert_many_at_index(&vec, index, count, &a, &b, &b);

	assert(*((int*) vec_get(&vec, index)) == a);
	assert(*((int*) vec_get(&vec, index+1)) == b);
	assert(*((int*) vec_get(&vec, index+2)) == b);
	assert(vec_size(&vec) == 12);
	assert(vec.capacity == 16);

	printf("✅ Insert many at index %d\n", index);

	vec_free(&vec);
}

void deletion_test() {

	printf("\n!!--Deletion Test--!!\n");

	int b = 15;
	int a = 10;
	int index = 0;

	vector_t vec;
	vec_new(&vec);

	vec_push_back(&vec, (void*) &a);
	vec_push_back(&vec, (void*) &b);
	vec_push_back(&vec, (void*) &a);
	vec_push_back(&vec, (void*) &b);
	vec_push_back(&vec, (void*) &a);
	vec_push_back(&vec, (void*) &b);

	assert(*((int*) vec_pop_back(&vec)) == b);
	assert(vec_size(&vec) == 5);
	assert(vec.capacity == 8);
	assert(*((int*) vec_pop_back(&vec)) == a);
	assert(vec_size(&vec) == 4);
	assert(vec.capacity == 4);

	printf("✅ Pop back\n");

	vec_push_back(&vec, (void*) &a);
	vec_push_back(&vec, (void*) &b);

	assert(*((int*)vec_remove_from_index(&vec, index)) == a);
	assert(vec_size(&vec) == 5);

	printf("✅ Remove from index %d\n", index);

	index = 3;
	assert(*((int*)vec_remove_from_index(&vec, index)) == b);
	assert(vec_size(&vec) == 4);
	vec_insert_at_index(&vec, index, (void*) &a);
	vec_insert_at_index(&vec, index, (void*) &b);

	printf("✅ Remove from index %d\n", index);

	index = 1;
	vector_t removed_elems;
	vec_new(&removed_elems);

	vec_remove_many_from_index(&vec, index, 3, &removed_elems);

	assert(vec_size(&removed_elems) == 3);
	assert(*((int*)removed_elems.array[0]) == b);
	assert(*((int*)removed_elems.array[1]) == a);
	assert(removed_elems.capacity == 4);

	assert(vec_size(&vec) == 3);
	assert(*((int*) vec_get(&vec, 1)) == a);

	vec_free(&removed_elems);

	printf("✅ Remove many from index %d\n", index);
}

void util_test() {

	printf("\n!!--Util Test--!!\n");

	int b = 15;
	int a = 10;
	int index = 1;

	vector_t vec;
	vec_new(&vec);

	vec_push_back(&vec, (void*) &a);
	vec_push_back(&vec, (void*) &b);
	vec_push_back(&vec, (void*) &a);
	vec_push_back(&vec, (void*) &b);
	vec_push_back(&vec, (void*) &a);
	vec_push_back(&vec, (void*) &b);

	assert(*((int*)vec_get(&vec, index)) == b);

	printf("✅ Vector get element at index %d\n", index);

	vec_set(&vec, index, (void*) &a);

	assert(*((int*)vec_get(&vec, index)) == a);

	printf("✅ Vector set element at index %d\n", index);

	assert(vec_size(&vec) == 6);

	printf("✅ Vector size\n");

	vec_free(&vec);
}

int main() {
	util_test();
	push_back_test();
	insertion_test();
	deletion_test();
	return 0;
}