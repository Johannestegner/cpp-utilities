#ifndef MACROS_H
#define MACROS_H

#ifndef NULL
#define NULL 0
#endif
#define delete_s(o) delete(o); o = NULL;
#define delete_array_s(a) delete[]a; a= NULL;

#endif