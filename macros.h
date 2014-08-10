/*
 * contains macros defined for Chapter 13
 */

/*
 * compares two integers
 */
#define compare(x,y) (x) == (y) ? 0:\
                    (x) < (y) ? -1:1

/*
 * prints the result of an expression
 */
#define print_value(expr) printf("exp = %d\n", expr)
