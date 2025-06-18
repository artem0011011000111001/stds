// --- Define Memory Macros
#ifdef _STDS_PTR_
#ifndef new
#define new make_ptr // replacement of keyword new
#endif // new

#ifndef delete
#define delete // disable delete keyword
#endif // delete
#endif