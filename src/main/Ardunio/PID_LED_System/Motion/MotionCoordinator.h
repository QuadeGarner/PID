#ifndef MOTIONCONTROLLER
#define MOTIONCONTROLLER
class{
    private:
        double target;
        double positon;
        static double home;
        double power;
    public:
        double getTarget();
        double getPosition();
        double getHome();
        double getPower();
        void setTarget(double);
        void setPosition();
        static void setHome(double);
        void setPower(double);
};
#endif