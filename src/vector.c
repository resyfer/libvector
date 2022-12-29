#include <include/vector.h>

vector_t*
vec_new(void)
{
	vector_t *vec = malloc(sizeof(vector_t));

	vec->size = 0;
	vec->capacity = 0;
	vec->array = NULL;

	return vec;
}

vector_t*
vec_new_size(u_int32_t size)
{
	vector_t *vec = malloc(sizeof(vector_t));
	void **array = malloc(size * sizeof(void*));

	vec->size = size;
	vec->capacity = size;
	vec->array = array;

	return vec;
}

void
vec_push_back(vector_t* vec, void* value)
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
vec_pop_back(vector_t* vec)
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
vec_get(vector_t* vec, u_int32_t index)
{
	if(index >= vec->size) {
		return NULL;
	}

	return vec->array[index];
}

// Returns old pointer
void*
vec_set(vector_t* vec, u_int32_t index, void *value)
{
	if(index >= vec->size) {
		return NULL;
	}

	void *old_elem = vec->array[index];
	vec->array[index] = value;
	return old_elem;
}

void*
vec_front(vector_t* vec)
{
	return vec_get(vec, 0);
}

void*
vec_back(vector_t* vec)
{
	return vec_get(vec, vec->size - 1);
}

u_int32_t
vec_size(vector_t* vec)
{
	return vec->size;
}

void
vec_shrink(vector_t* vec)
{
	vec->array = realloc(vec->array, vec->size * sizeof(void*));
	vec->capacity = vec->size;
}

void
vec_free(vector_t* vec)
{
	free(vec->array);
	free(vec);
}