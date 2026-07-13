# Virtual CanBus Protocol


Message ID
----------
    0x202
_______
Name
----
    EncoderStatus
______
Purpose
-------
    Broadcasts the current encoder statis of a motor to the virtual CAN network.
_______
Publisher
---------
    MotorController
_________

Subscribers
----------
    MotionCooridator
    TelemetryManager
    DiagnosticsManager(Future)
_________
Description
-----------
    The EncoderStatus  message is used to notify the MotionCoordinator about the status of the motors. 
    Every MotionCoordinator receives the message.
    Each MotionCoordinator checks the DeviceID field:
        * If the deviceID matches its own ID updates it internal status of the Motors.
        * Otherwise ignore the message.
----------------------------------------------------------

Payload
------
    Version 1 
        CurrentPosition 
        CurrentVelocity
_______
Future Extensions
---------
    * Direction
    * EncoderHealth
    * Encoder Temperature
    * Timestamp
___________
Validation
----------
    None.
    EncoderStatus is a read-only status message.
______
Transmission
------
    Broadcast every control loop iteration.
_______
Notes
-----
    * 