# Virtual CanBus Protocol


Message ID
----------
    0x301
_______
Name
----
    TimeSyncronization
______
Purpose
-------
    Command Sync all the times across the system. 
_______
Publisher
---------
    MotionCoordination
_________

Subscribers
----------
    PIDController
    MotorController
    Telemerty
_________
Description
-----------
    The TimeSycnization Frame, send a current time, and number of current ticks and allow the subsystems to resync there
    time and number of ticks if they fall out of sync with each other 
----------------------------------------------------------

Payload
------
    Version 1 
        current time 
        number of ticks
_______
Future Extensions
---------
    None 
___________
Validation
----------
    Read-only frame used to resync the subsystems to the main coordinator - MotionCoordinatior.
______
Notes
-----
    * This mesage updated all controllers internal time 
    * it does not command anything else about the system
    * The receiver is responible for reading the values and determining if changes are needed
    * The CAN ID indentifies the message type.
    * The DeviceID identifies which controller should update.