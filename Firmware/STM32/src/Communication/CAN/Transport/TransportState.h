#ifndef TRANSPORTSTATE
#define TRANSPORTSTATE
enum class TransportState
{
    IDLE,
    RECIEVING,
    COMPLETE,
    RECEIVING_COMPLETE
};
#endif