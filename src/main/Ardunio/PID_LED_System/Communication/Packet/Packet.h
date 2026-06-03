#ifndef PACKET
#define PACKET
class Packet{
    private:
        double kP;
        double kI;
        double kD;
        long completeionTime;
    public:
        void setKP(double);
        void setKI(double);
        void setKD(double);
        void setCompletionTime(long);
        double getKP();
        double getKI();
        double getKD();
        long getCompletionTime();
};
#endif