#include <stdlib.h>
#include <include/vector.h>
#include <include/util.h>
#include <stdarg.h>

#include <stdio.h>

/**
 * @brief Update the capacity of the internal array to the nearest
 * 		  power of 2 that will hold all the elements of the array.
 *
 * @param vec Vector instance
 * @param change Signed change from initial capacity
 * @return u_int32_t
 */
static u_int32_t
changed_cap(vector_t *vec, int64_t change)
{

	if(!change) {
		return vec->capacity;
	} else if(change > 0) {

		if(vec->size + change <= vec->capacity) {
			return vec->capacity;
		}

		u_int64_t new_cap = vec->capacity;
		while(new_cap < vec->size + change) {

			if(new_cap == 1) {
				new_cap = 2;
				continue;
			}

			new_cap = (new_cap >> 1) << 2;

			if(new_cap == 0) {
				new_cap = 1;
			}
		}

		if(new_cap > __INT32_MAX__) {
			error("Vector size limit reached.");
		}

		return (u_int32_t) new_cap;
	} else {

		if(vec->size == 0) {
			error("Vector size needs to be atleast 0");
		}

		if(vec->size + change == 0) {
			return 0;
		}

		int64_t new_cap = vec->capacity;
		while(new_cap >= (vec->size + change)) {

			if(new_cap == 0) {
				break;
			}

			new_cap = (new_cap >> 1);
		}

		if(new_cap == 0 && vec->size + change == 1) {
			new_cap = 1;
		} else {
			new_cap = new_cap << 1;
		}

		return new_cap;

	}
}

/**
 * @brief Resize the internal array of the vector by the signed changed
 * 		  from the initial value.
 *
 * @param vec Vector instance
 * @param cap_change Signed changed.
 */
static void
resize_internal_array(vector_t *vec, int64_t cap_change)
{
	int old_cap = vec->capacity;

	vec->capacity = changed_cap(vec, cap_change);

	if(vec->capacity == 0)
	{
		if(old_cap != 0) {
			free(vec->array);
		}

		vec->array = NULL;
		return;
	}

	vec->array = realloc(vec->array, sizeof(void*) * vec->capacity);
}

/**
 * @brief New vector instance with the capacity to the nearest
 * 		  greater power of 2 to the capacity specified.
 *
 * @param cap Capacity
 * @return vector_t* Vector instance
 */
vector_t*
vec_new_cap(u_int32_t cap)
{
	vector_t *vec = malloc(sizeof(vector_t));
	vec->size = 0;
	vec->capacity = 0;
	vec->array = NULL;

	if(cap == 0) {
		return vec;
	}

	resize_internal_array(vec, cap);

	return vec;
}

/**
 * @brief Get a new empty vector instance.
 *
 * @return vector_t* Vector instance
 */
vector_t*
vec_new(void)
{
	return vec_new_cap(0);
}

/**
 * @brief Insert many elements at given index.
 *
 * @param vec Vector instance
 * @param index Index to insert elements to
 * @param count Number of elements to insert
 * @param ... Elements of the type `void*`, as many as needed
 */
void
vec_insert_many_at_index(vector_t* vec, u_int32_t index, u_int32_t count, ...)
{
	int n = vec_size(vec);

	resize_internal_array(vec, count);

	for(int i = count-1; i>=0; i--) {
		vec->array[index + count + i] = vec->array[index + i];
	}

	va_list args;
	va_start(args, count);

	for(int i = index; i < index + count; i++) {
		vec->array[i] = va_arg(args, void*);
	}

	va_end(args);
	vec->size += count;
}

/**
 * @brief Insert an element at given index.
 *
 * @param vec Vector instance.
 * @param index Index to insert element at
 * @param value Element to insert at index
 */
void
vec_insert_at_index(vector_t* vec, u_int32_t index, void* value)
{
	vec_insert_many_at_index(vec, index, 1, value);
}

/**
 * @brief Add the elements of a `source` vector to the end
 * 		  of `destination` vector.
 *
 * @param dest Destination vector instance
 * @param src Source vector instance
 */
void
vec_push_back_vec(vector_t* dest, vector_t* src)
{
	resize_internal_array(dest, src->size);

	int n = src->size;
	for(int i = 0; i<n; i++) {
		dest->array[dest->size + i] = src->array[i];
	}

	dest->size+=src->size;
}

/**
 * @brief Add an element to the end of the vector.
 *
 * @param vec Vector instance
 * @param value Value to add
 */
void
vec_push_back(vector_t* vec, void* value)
{
	int n= vec->size;
	resize_internal_array(vec, 1);
	vec->array[n] = value;
	vec->size++;
}

/**
 * @brief Remove many elements from the index
 *
 * @param vec Vector instance
 * @param index Index to remove elements from
 * @param count Number of elements to remove
 * @return vector_t* Vector of the removed instances
 */
vector_t*
vec_remove_many_from_index(vector_t *vec, u_int32_t index, int count)
{
	vector_t *removed_items = vec_new_cap(count);

	for(u_int32_t i = 0; i < count; i++) {
		removed_items->array[i] = vec->array[index + i];
		vec->array[index + i] = vec->array[index + count + i];
	}

	resize_internal_array(vec, -count);
	vec->size-=count;
	removed_items->size = count;
	return removed_items;
}

/**
 * @brief Remove an element from an index.
 *
 * @param vec Vector instance
 * @param index Index to remove element from
 * @return void* The element removed
 */
void*
vec_remove_from_index(vector_t *vec, u_int32_t index)
{
	vector_t *removed_item = vec_remove_many_from_index(vec, index, 1);
	return removed_item->array[0];
}

/**
 * @brief Remove the last element of the vector
 *
 * @param vec Vector instance
 * @return void* Removed element
 */
void*
vec_pop_back(vector_t* vec)
{
	return vec_remove_from_index(vec, vec_size(vec) - 1);
}

/**
 * @brief Get the element at an index
 *
 * @param vec Vector instance
 * @param index Index of the element
 * @return void* Element at the given index
 */
void*
vec_get(vector_t* vec, u_int32_t index)
{
	if(index >= vec_size(vec)) {
		error("Out of bounds access.");
	}

	return vec->array[index];
}

/**
 * @brief Set the value of the element at the given index
 *
 * @param vec Vector instance
 * @param index Index of the element
 * @param value New value of element
 * @return void* Old value of element
 */
void*
vec_set(vector_t* vec, u_int32_t index, void *value)
{
	void *old_elem = vec->array[index];
	vec->array[index] = value;
	return old_elem;
}

/**
 * @brief First element of the vector
 *
 * @param vec Vector instance
 * @return void* First element
 */
void*
vec_front(vector_t* vec)
{
	return vec_get(vec, 0);
}

/**
 * @brief Last element of the vector
 *
 * @param vec Vector instance
 * @return void* Last element
 */
void*
vec_back(vector_t* vec)
{
	return vec_get(vec, vec->size - 1);
}

/**
 * @brief Size of the vector.
 *
 * @param vec Vector instance
 * @return u_int32_t Size
 */
u_int32_t
vec_size(vector_t* vec)
{
	return vec->size;
}

/**
 * @brief Fit the internal array to be only as long as the number of
 * 		  elements present inside it.
 *
 * @param vec Vector instance
 */
void
vec_shrink(vector_t* vec)
{
	resize_internal_array(vec, - (vec->capacity - vec_size(vec)));
}

/**
 * @brief Free up vector instance
 *
 * @param vec Vector instance
 *
 * @warning This does not free up any dynamically allocated memory for
 * 			individual elements kept in the vector.
 */
void
vec_free(vector_t* vec)
{
	free(vec->array);
	free(vec);
}