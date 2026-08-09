# Virtual CanBus Protocol


Message ID
----------
    0x202
_______
Name
----
    PIDStatus
______
Purpose
-------
    Broadcasts the current PIDController status to the virtual CAN network.
_______
Publisher
---------
    PIDController
_________

Subscribers
----------
    MotionCooridator
    TelemetryManager
    DiagnosticsManager(Future)
_________
Description
-----------
    The PIDStatus  message is used to notify the System about the status of the PIDProcess
    Every node on the virtual CAN network receives the frame
        * Nodes the require PID status information process the frame
        * All other nodes ignore it.
----------------------------------------------------------

Payload
------
    Version 1 
        CurrentError 
        LastError
        Output
_______
Future Extensions
---------
    * Intgral Accumlator
    * Derivative
    * Saturated Output
    * Contreller State
___________
Validation
----------
    None.
    PIDStatus is a read-only status message.
______
Transmission
------
    Broadcast every control loop iteration.
_______
Notes
-----
    * 