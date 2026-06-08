#ifndef CURRENTSTATES
#define CURRENTSTATES
enum class CurrentState
{
    WAITING_FOR_DATA,
    READING_DATA,
    TIMEOUT
};
#endif