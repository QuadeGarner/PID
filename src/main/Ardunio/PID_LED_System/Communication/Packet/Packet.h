#ifndef PACKET
#define PACKET
#include "PacketStatus.h"
#include "PacketCompletionStatus.h"
class Packet{
    private:
        double target;
        double kP;
        double kI;
        double kD;
        long completeionTime;
        long startTime;
        PacketStatus status;
        PacketCompletionStatus completionStatus;
    public:
        void setTarget(double);
        void setKP(double);
        void setKI(double);
        void setKD(double);
        void setCompletionTime(long);
        void setTarget();
        double getKP();
        double getKI();
        double getKD();
        long getCompletionTime();
        void setStartTime(long);
        long getStartTime();
        PacketStatus getPacketStatus();
        void setStatus(PacketStatus);
        PacketCompletionStatus getCompletionStatus();
        void setCompletionStatus(PacketCompletionStatus)
        void clearData();
};
#endif