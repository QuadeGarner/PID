#ifndef Command
#define Command
enum class CMD_Type
{
    GO_HOME,
    UPDATE_TARGET,
    UPDATE_PID
};
typedef struct Command
{
    CMD_Type cmd;
    double argumnets[3];
};
/*
 * UPDATE_TARGET
        data[0] = target
    UPDATE_PID
        data[0] = kp
        data[1] = ki
        data[2] = kd
    GO_HOME
        data[] unused
 */
#endif