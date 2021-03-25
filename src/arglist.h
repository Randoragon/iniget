/** @file
 * A list of query arguments extracted from a file.
 */

#ifndef ARGLIST_H
#define ARGLIST_H

#include <stdlib.h>
#include <limits.h>

/********************************************************
 *                     CONSTANTS                        *
 ********************************************************/

/** This enum stores all possible value types
 * that can be stored in an ArgList.
 */
enum ArgValType {

    /** uninitialized value */
    ARGVAL_TYPE_NONE,

    /** integer */
    ARGVAL_TYPE_INT,

    /** double */
    ARGVAL_TYPE_FLOAT,

    /** string of characters */
    ARGVAL_TYPE_STRING
};

/********************************************************
 *                      TYPEDEFS                        *
 ********************************************************/

/** @cond */
typedef struct ArgList ArgList;
typedef struct ArgVal ArgVal;
typedef enum ArgValType ArgValType;
/** @endcond */


/********************************************************
 *                     DATA TYPES                       *
 ********************************************************/

/** A simple arglist of ints implemented as an array.
 *
 * This structure is used during the initial stage of
 * running a @ref Query (@ref runQueries). Since each
 * query is file-agnostic, it only holds strings denoting
 * the names of section/key pairs (@ref Query::data) to be used
 * during computation. For the computation stage, however,
 * these section/key pairs are useless, as we are interested
 * in the actual in-file values. That's why, prior to
 * computation, an ArgList is populated with the needed values
 * (each query gets its own ArgList (@ref Query::args), and
 * each ArgList is indexed exactly like that query's @ref
 * Query::data array).
 */
struct ArgList
{
    /** Array of values. */
    ArgVal *data;

    /** Number of elements on the arglist. */
    size_t size;
};

/** Holds a single value of one of types defined in
 * @ref ArgValType.
 */
struct ArgVal
{
    /** The type of @ref value */
    ArgValType type;

    /** The value */
    union {
        int i;
        double f;
        char *s;
    } value;
};


/********************************************************
 *                     FUNCTIONS                        *
 ********************************************************/

/** Allocates a new arglist and returns its address.
 *
 * @param size The length of the arglist.
 *
 * @returns
 * - valid address - success
 * - @c NULL - failure (malloc)
 */
ArgList *arglistCreate(size_t size);

/** Frees all memory owned by the arglist. */
void arglistFree(ArgList *arglist);

#endif /* ARGLIST_H */
