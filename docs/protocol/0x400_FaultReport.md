# Virtual CanBus Protocol


Message ID
----------
    0x400
_______
Name
----
    FaultReport
______
Purpose
-------
    Notifies the virtual CAN network that a node has entered a fault state._______
Publisher
---------
    Every Can Node
_________

Subscribers
----------
    Every Can Node
_________
Description
-----------
    
----------------------------------------------------------

Payload
------
    Version 1 
        NodeID of the node that trigger the Fault 
_______
Future Extensions
---------
    * Fault Code
    * Timestamp
    * Severity
    * Additional Data
___________
Validation
----------
    None.
    FaultReport  is a read-only status message.
______
Transmission
------
    Broadcast once during a detected fault. Broadcast again if the fault changes.
_______
Notes
-----
    * Used to gather data that cause a fault in the system.
    