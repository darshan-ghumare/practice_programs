#ifndef __LOG_H__

#define __LOG_H__

/*
 * Previous versions of CPP implemented the comma-deletion extension much more generally. We have restricted it in this release to minimize the differences from C99.
 * To get the same effect with both this and previous versions of GCC, the token preceding the special ‘##’ must be a comma,
 * and there must be white space between that comma and whatever comes immediately before it:
 * #define eprintf(format, args...) fprintf (stderr, format , ##args)
 *
 * Source : https://gcc.gnu.org/onlinedocs/cpp/Variadic-Macros.html
 */
#define LOG_ERR(MSG, ...) do { \
            fprintf(stderr, "%s():%d " MSG "\n", __func__, __LINE__ , ##__VA_ARGS__); \
} while (0)


#endif //__LOG_H__
