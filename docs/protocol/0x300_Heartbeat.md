# Virtual CanBus Protocol


Message ID
----------
    0x300
_______
Name
----
    Heartbeart
______
Purpose
-------
    Periodically broadcast that a node is alive and participationg on the vitural Can Bus
_______
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
        NodeID
_______
Future Extensions
---------
    * 
___________
Validation
----------
    None.
    Heartbeat is a read-only status message.
______
Transmission
------
    Broadcast every 100 ms.
_______
Notes
-----
    * Used to detect node failure
    * Missing heartbeat may indicate a crashed or disconnected node.