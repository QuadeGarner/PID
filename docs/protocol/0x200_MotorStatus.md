# Virtual CanBus Protocol


Message ID
----------
    0x200
_______
Name
----
    MotorStatus
______
Purpose
-------
    Broadcasts the current operating state of a motor controller to the virtual Can network.
_______
Publisher
---------
    MotorController
_________
Subscribers
----------
    MotionCoordinator 
    TelemetryManager
    DiagnosticsManager(Future)
_________
Description
---------
    Provide the status of the MotorContoller, and the its motors
----------------------------------------------------------

Payload
------
    Version 1 
        * Current Power
        * Enabled State
_______
Future Extensions
---------
    * Applied Power
    * Motor Direction
    * Controller Enabled
    * Controller State
___________
Validation
----------
    None.
    MotorStatus is a read-only status message.
______
Transmission
------
    Broadcast every control loop iteration.
_______
Notes
-----
    * 