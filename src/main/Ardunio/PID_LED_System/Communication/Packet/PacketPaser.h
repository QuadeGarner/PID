#ifndef PACKETPARSER
#define PACKETPARSER
#include "../../Enums/FieldLoadingStates.h"
#include "../../Enums/FieldStates.h"
#include "Packet.h"

class PacketParser
{
private:
    char numbersArray[11] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'};
    char targetArr[32];
    char field1Arr[32];
    char field2Arr[32];
    char field3Arr[32];
    int h = 0;
    int i = 0;
    int k = 0;
    int j = 0;
    FieldLoadingState state;
    FieldStates status;
    void fillArray(char[], char, int);
    void startPacket();
    Packet endPacket();
    void processDelimiter(char);
    bool validateCharacter(char);
    bool determineTransportCharacter(char c);
    bool isCharacterAllowed(char);
    Packet p;
    void checkCompletionStatus(Packet &);
    void checkValues(Packet &);
    bool checkForEmptyValues();

public:
    Packet
    createPacket(char c);
};
#endif