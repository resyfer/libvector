#include <include/libvector.h>

struct vector*
vec_new(void)
{
	struct vector *vec = malloc(sizeof(struct vector));

	vec->size = 0;
	vec->capacity = 0;
	vec->array = NULL;

	return vec;
}

struct vector*
vec_new_size(u_int32_t size)
{
	struct vector *vec = malloc(sizeof(struct vector));
	void **array = malloc(size * sizeof(void*));

	vec->size = size;
	vec->capacity = size;
	vec->array = array;

	return vec;
}

void
vec_push_back(struct vector* vec, void* value)
{
	if(vec->size == vec->capacity) {
		if(vec->capacity == 0) {
			vec->capacity = 1;
		} else {
			vec->capacity = vec->capacity << 1;
		}

		vec->array = realloc(vec->array,vec->capacity * sizeof(void*));
	}

	vec->array[vec->size] = value;
	vec->size++;
}

void*
vec_pop_back(struct vector* vec)
{

	if(vec->capacity == 1) {
		void* elem = vec->array[0];

		free(vec->array);
		vec->array = NULL;

		vec->capacity = 0;
		vec->size = 0;
		return elem;
	}

	if (vec->size - 1== vec->capacity >> 1) {
		vec->capacity = vec->capacity >> 1;
		vec->array = realloc(vec->array, vec->capacity * sizeof(void*));
	}

	vec->size--;
	return vec->array[vec->size];
}

void*
vec_get(struct vector* vec, u_int32_t index)
{
	if(index >= vec->size) {
		return NULL;
	}

	return vec->array[index];
}

// Returns old pointer
void*
vec_set(struct vector* vec, u_int32_t index, void *value)
{
	if(index >= vec->size) {
		return NULL;
	}

	void *old_elem = vec->array[index];
	vec->array[index] = value;
	return old_elem;
}

void*
vec_front(struct vector* vec)
{
	return vec_get(vec, 0);
}

void*
vec_back(struct vector* vec)
{
	return vec_get(vec, vec->size - 1);
}

u_int32_t
vec_size(struct vector* vec)
{
	return vec->size;
}

void
vec_shrink(struct vector* vec)
{
	vec->array = realloc(vec->array, vec->size * sizeof(void*));
	vec->capacity = vec->size;
}

void
vec_free(struct vector* vec)
{
	free(vec->array);
	free(vec);
}