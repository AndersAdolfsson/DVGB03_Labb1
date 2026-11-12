#include "debug.h"

static bool bDebugEnabled = false;

void debug_set_enabled(bool NewValue)
{
    bDebugEnabled = NewValue;
}

bool debug_is_enabled(void)
{
    return bDebugEnabled;
}
