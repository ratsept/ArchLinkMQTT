
#ifndef DBG_H__
#define DBG_H__

#include "SEGGER_RTT.h"

//#ifdef DEBUG
//#define DBG(x, ...) { SEGGER_RTT_printf(0, "[DBG] " x "\r\n", ## __VA_ARGS__); }
//#define WARN(x, ...) { SEGGER_RTT_printf(0, RTT_CTRL_TEXT_YELLOW "[WARN] " x "\r\n" RTT_CTRL_RESET, ## __VA_ARGS__); }
/*
#define ERR(x, ...) { SEGGER_RTT_printf(0,                                                                 \
                                        RTT_CTRL_TEXT_BRIGHT_RED "[ERR] [%s:%d] " x "\r\n" RTT_CTRL_RESET, \
                                        __func__,                                                          \
                                        __LINE__,                                                          \
                                        ## __VA_ARGS__); }
*/
//#else
#define DBG(x, ...)
#define WARN(x, ...)
#define ERR(x, ...)
//#endif

#endif //DBG_H__
