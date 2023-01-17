#ifndef __LIBVECTOR_H
#define __LIBVECTOR_H 1

/* libc */
#include <sys/types.h>

/**
 * @brief Vector instance.
 *
 * Has an internal array that doubles in capacity
 * everytime it fills up.
 */
typedef struct {
	u_int32_t size;
	u_int32_t capacity;
	void **array;
} vector_t;

/* Create Vector */

/**
 * @brief New vector instance with the capacity to the nearest
 * 		  greater power of 2 to the capacity specified.
 *
 * @param cap Capacity
 * @return vector_t* Vector instance
 */
vector_t* vec_new_cap(u_int32_t cap);

/**
 * @brief Get a new empty vector instance.
 *
 * @return vector_t* Vector instance
 */
vector_t* vec_new(void);

/* CRUD */

/**
 * @brief Insert many elements at given index.
 *
 * @param vec Vector instance
 * @param index Index to insert elements to
 * @param count Number of elements to insert
 * @param ... Elements of the type `void*`, as many as needed
 */
void vec_insert_many_at_index(vector_t* vec, u_int32_t index, u_int32_t count, ...);

/**
 * @brief Insert an element at given index.
 *
 * @param vec Vector instance.
 * @param index Index to insert element at
 * @param value Element to insert at index
 */
void vec_insert_at_index(vector_t* vec, u_int32_t index, void* value);

/**
 * @brief Add the elements of a `source` vector to the end
 * 		  of `destination` vector.
 *
 * @param dest Destination vector instance
 * @param src Source vector instance
 */
void vec_push_back_vec(vector_t* dest, vector_t* src);

/**
 * @brief Add an element to the end of the vector.
 *
 * @param vec Vector instance
 * @param value Value to add
 */
void
vec_push_back(vector_t* vec, void* value);

/**
 * @brief Remove many elements from the index
 *
 * @param vec Vector instance
 * @param index Index to remove elements from
 * @param count Number of elements to remove
 * @return vector_t* Vector of the removed instances
 */
vector_t* vec_remove_many_from_index(vector_t *vec, u_int32_t index, int count);

/**
 * @brief Remove an element from an index.
 *
 * @param vec Vector instance
 * @param index Index to remove element from
 * @return void* The element removed
 */
void* vec_remove_from_index(vector_t *vec, u_int32_t index);

/**
 * @brief Remove the last element of the vector
 *
 * @param vec Vector instance
 * @return void* Removed element
 */
void* vec_pop_back(vector_t* vec);

/**
 * @brief Get the element at an index
 *
 * @param vec Vector instance
 * @param index Index of the element
 * @return void* Element at the given index
 */
void* vec_get(vector_t* vec, u_int32_t index);

/**
 * @brief Set the value of the element at the given index
 *
 * @param vec Vector instance
 * @param index Index of the element
 * @param value New value of element
 * @return void* Old value of element
 */
void* vec_set(vector_t* vec, u_int32_t index, void *value);

/**
 * @brief First element of the vector
 *
 * @param vec Vector instance
 * @return void* First element
 */
void* vec_front(vector_t* vec);

/**
 * @brief Last element of the vector
 *
 * @param vec Vector instance
 * @return void* Last element
 */
void* vec_back(vector_t* vec);

/**
 * @brief Size of the vector.
 *
 * @param vec Vector instance
 * @return u_int32_t Size
 */
u_int32_t vec_size(vector_t* vec);

/**
 * @brief Fit the internal array to be only as long as the number of
 * 		  elements present inside it.
 *
 * @param vec Vector instance
 */
void vec_shrink(vector_t* vec);

/**
 * @brief Free up vector instance
 *
 * @param vec Vector instance
 *
 * @warning This does not free up any dynamically allocated memory for
 * 			individual elements kept in the vector.
 */
void vec_free(vector_t* vec);

#endif