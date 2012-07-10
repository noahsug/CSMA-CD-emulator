#ifndef __DEBUG_H__
#define __DEBUG_H__

#define DEBUG 1

#if DEBUG == 1
#define PRINT(x) std::cerr << x;
#else
#define PRINT(x)
#endif


#endif

