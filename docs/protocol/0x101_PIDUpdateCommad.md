# Virtual CanBus Protocol


Message ID
----------
    0x101
_______
Name
----
    PIDUpdate
______
Purpose
-------
    Command to change the KP, KI, KP valuse of the PIDController
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
        * If the DeviceID matches its own ID update the gains.
        * If the DeviceID is ALL_MOTORSm, update every controller.
        * Otherwise ignore the message.
----------------------------------------------------------

Payload
------
    Version 1 
        kP - portinal
        kI - Intgeral
        kD - Derivate
_______
Future Extensions
---------
• Feed Forward Gain (kF)
• Integral Limit
• Output Limits
• Deadband
• Derivative Filter Constant
• Control Loop Frequency
___________
Validation
----------

    * kP >= 0
    * kI >= 0
    * kD >= 0

Receiver should reject invalid gain values.
______
Notes
-----
    * This mesage updated contoller parameters only.
    * it does not command motor movement.
    * The receiver is responible for validating the gain values before applying them.
    * Invalid values should be ignored or rejected.
    * The CAN ID indentifies the message type.
    * The DeviceID identifies which controller should update.