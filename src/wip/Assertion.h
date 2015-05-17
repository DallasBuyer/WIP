#ifndef __ASSERTION_H__
#define __ASSERTION_H__

#include <assert.h>

#define BREAK_ASSERTION

#define DO_ASSERTION

#ifdef DO_ASSERTION
#ifdef BREAK_ASSERTION
#define CHECK(code)					assert(code);

#else

#define CHECK(code)					{if(!(code))printf("Assertion failure:\n"#code"\nFile:\n"__FILE__"\nLine:\n%d\n", __LINE__);}
#endif

//combine 'break' in "code" to use it.when something is wrong,just break so that do not run the remain code.
#define CHECKCODE(code)				do{code} while(0);



#endif

#endif