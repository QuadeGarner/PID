#include <unity.h>
#include "../../src/Communication/CAN/Transport/Transport.h"
#include "../../src/Communication/CAN/Transport/TransportProtocol.h"
#include "../../src/Communication/CAN/CanProtocol.h"
#include "../../src/Librays/CanCodec.h"
void test_single_frame()
{
    TransportProtocol tp;

    CAN_Message message{};
    message.messageID = MOTOR_COMMAND;
    message.length = 4;

    CanCodec::encodeFloat(message, 0, 0.5f);

    auto frames = tp.buildFrames(message);

    TEST_ASSERT_EQUAL(1, frames.size());
    TEST_ASSERT_EQUAL(MOTOR_COMMAND, frames[0].id);
    TEST_ASSERT_EQUAL(4, frames[0].dlc);
}

void setup()
{
    UNITY_BEGIN();
    RUN_TEST(test_single_frame);
    UNITY_END();
}

void loop()
{
}