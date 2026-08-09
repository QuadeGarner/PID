# Virtual CanBus Protocol


Message ID
----------
    0x102
_______
Name
----
    PIDCommand
______
Purpose
-------
    Command to run the Math of the PIDController to determine output 
_______
Publisher
---------
    MotionCoordinator
_________

Subscribers
----------
    PIDController
_________
Description
-----------
    THe PIDUpdate message is used to modift the controller gains while the system is running. 
    Every PIDContoller receives the message.
    Each controller checks the DeviceID field:
        *
        * Otherwise ignore the message.
----------------------------------------------------------

Payload
------
    Version 1 
        target
        Position
        delta t
_______
Future Extensions
---------
• 
___________
Validation
----------

______
Notes
-----
    * This mesage updated contoller parameters only.
    * it does not command motor movement.
    * The receiver is responible for validating the gain values before applying them.
    * Invalid values should be ignored or rejected.
    * The CAN ID indentifies the message type.
    * The DeviceID identifies which controller should update.