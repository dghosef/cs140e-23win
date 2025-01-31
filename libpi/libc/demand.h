#ifndef __DEMAND_H__
#define __DEMAND_H__

#if 0
#ifdef RPI_UNIX
#   error "should not get here"
#endif
#endif

// print file:function:line with a message.
#define debug(msg, args...) \
    (printk)("%s:%s:%d:" msg, __FILE__, __FUNCTION__, __LINE__, ##args)

#define output printk

// print error message, die.
#define panic(msg, args...) do { 					    \
	(printk)("PANIC:%s:%s:%d:" msg "\n",                \
        __FILE__, __FUNCTION__, __LINE__, ##args);      \
	clean_reboot();							            \
} while(0)

// if assertion failed, die and reboot.
#define assert(bool) do {                                   \
    if((bool) == 0) {                                       \
        debug("ERROR: Assertion `%s` failed.\n", #bool);      \
	    clean_reboot();							            \
    }                                                       \
} while(0)

// stringify argument
#define _XSTRING(x) #x

// usage: 
//      demand(expr, msg)
// note, if it doesn't take special characters does not need quotes:
//      demand(x, x is 0!);
// but you can always add them: 
//      demand(x, "x is not 0 = %d", x);
// prints <msg> if <expr> is false.
// example:
//      demand(x < 3, x has bogus value!);
// note: 
//      if <_msg> contains a ',' you'll have to put it in quotes.
#define demand(_expr, _msg, args...) do {                           \
    if(!(_expr)) {                                                  \
        debug("ERROR: Demand `%s` failed: %s\n",                  \
                   _XSTRING(_expr), _XSTRING(_msg), ##args);        \
        clean_reboot();                                             \
    }                                                               \
} while(0)

/* Compile-time assertion used in function. */
#define AssertNow(x) switch(1) { case (x): case 0: ; }

// used to catch when calling unimplemented code.
#define unimplemented() panic("implement this function!\n");
// used to catch if reached code that is "impossible"
#define not_reached()   panic("NOTREACHED!\n");

#define todo(msg) panic("TODO: %s\n", msg)

/************************************************************
 * tracing macros used for testing.
 */

#define exit_success(args...)  \
    do { printk("SUCCESS:"); output(args); clean_reboot(); } while(0)

// used for tracing: just emit a TRACE: prefix so can grep
#define trace(args...) \
    do { printk("TRACE:%s:", __FUNCTION__); printk(args); } while(0)

#define trace_notreached() \
    trace_panic("should not reach\n")

#define trace_clean_exit(args...) \
    do { trace(args); clean_reboot(); } while(0)

#define trace_panic(args...) do { \
    printk("TRACE:ERROR:"); \
    printk(args); \
	clean_reboot();							\
} while(0)
#endif
