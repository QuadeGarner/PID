#ifndef  PACKETPARSER
#define PACKETPARSER
#include "FIELDLOADINGSTATE.h"
#include "FIELDSTATES.h"
#include "PACKET.h"
class PacketParser{
    private:
        char numbersArray[] = {'0','1','2','3','4','5','6','7','8','9','.',','};
        char field1Arr[32];
        char field2Arr[32];
        char field3Arr[32];
        int i =0;
        int k = 0;
        int j =0;
        FieldLoadingState state;
        FieldStates status;
        void fillArray(char[], char, int);
        void startPacket();
        void endPacket();
        void processDelimiter(char);
        bool validateCharacter(char);
        bool determineTransportCharacter(char c);
        bool isCharacterAllowed(char);

    public:
         Packet createPacket( char c);

};
#endif