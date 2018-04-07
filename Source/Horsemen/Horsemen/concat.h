#ifndef CONCAT_H
#define CONCAT_H

#define CONCAT_NX(A, B) A ## B
#define CONCAT(A, B) CONCAT_NX(A, B)

#define STRINGIZE_NX(A) #A
#define STRINGIZE(A) STRINGIZE_NX(A)

#endif