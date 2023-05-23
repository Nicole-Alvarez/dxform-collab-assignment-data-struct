#ifndef __FILE_NAME__
        #include <string.h>
        #ifdef __unix__
                #define __FILE_NAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
        #else
                #define __FILE_NAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
        #endif
#endif

#define _context_str "In %s, line %d (%s)\n"
#define _context_args __FILE_NAME__, __LINE__, __func__
#define _context_str "In %s, line %d (%s)\n"
#define _context_args __FILE_NAME__, __LINE__, __func__
#define printerr_null_param() fprintf(stderr, "ERROR: NULL root parameter.\n" _context_str, _context_args)
#define printerr_allocation() fprintf(stderr, "ERROR: Unable to allocate memory.\n" _context_str, _context_args)
