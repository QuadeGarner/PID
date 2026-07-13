# Virtual CanBus Protocol

Message ID
----------
     0x100

Name
----
MotorCommand

Purpose
-------
Command one or more motor controllers to perform a motion-related operation.

Publisher
---------
MotionCoordinator

Subscribers
-----------
MotorController

Description
-----------
The MotorCommand message is used to control one or more motors on the
virtual CAN network.

Every MotorController receives the message.

Each controller checks the DeviceID field:

    • If the DeviceID matches its own ID, execute the command.
    • If the DeviceID is ALL_MOTORS, execute the command.
    • Otherwise ignore the message.

----------------------------------------------------------

DeviceID

Purpose:
Identifies which motor(s) should execute the command.

Current Values

ALL_MOTORS
FRONT_LEFT
FRONT_RIGHT
BACK_LEFT
BACK_RIGHT

Future versions may add:

ARM
INTAKE
LIFT
STEERING
PTO
etc.

----------------------------------------------------------

Operation

Purpose:
Specifies the action the motor should perform.

Current Operations

MOVE
HOME
STOP
ENABLE
DISABLE

Future Operations

SET_ZERO
RESET_FAULT
CALIBRATE
FOLLOW_PROFILE

----------------------------------------------------------

Payload

Version 1

Target Position

Future Versions

Maximum Velocity

Maximum Acceleration

Motion Profile

Torque Limit

----------------------------------------------------------

Notes

• One CAN message may command every motor simultaneously by using
DeviceID = ALL_MOTORS.

• The CAN ID identifies the MESSAGE TYPE.

• The payload contains the command data.

• DeviceID determines WHO executes the command.

• Operation determines WHAT the receiver should do.

==========================================================
