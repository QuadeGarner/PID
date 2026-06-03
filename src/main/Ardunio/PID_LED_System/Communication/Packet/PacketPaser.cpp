#include "PACKETPARSER.h"
void PacketParser:: startPacket(){
    // Set state to Field 1
    status = FieldStates::BUILDING_PACKET;
    state = FieldLoadingState::FIELD1;
    // clear all the array data
    std::fill(std::begin(field1Arr), std::end(field1Arr), NULL);
    std::fill(std::begin(field2Arr), std::end(field2Arr), NULL);
    std::fill(std::begin(field3Arr), std::end(field3Arr), NULL);
    // reset all indexes to 0
    i = 0; j = 0; k= 0;
}
Packet PacketParser:: endPacket(){
    status = FieldStates::PACKET_COMPLETE;
    Packet p;
    field1Arr[i] = '\0';
    field2Arr[j] = '\0';
    field3Arr[k] = '\0';
    p.setKP(atof(field1Arr));
    p.setKI(atof(field2Arr));
    p.setKD(atof(field3Arr));
    p.setCompletionTime(millis());
    return p;
}
void PacketParser::processDelimiter(char c){
    switch(state){
        case(FieldLoadingState::FIELD1):
            state = FieldLoadingState:: FIELD2;
            break;
        case(FieldLoadingState::FIELD2):
            state = FieldLoadingState::Field3;
            break;
            // update when added more fields to the packet
        case(FieldLoadingState::FIELD3):
            state = FieldLoadingState::ERROR;
}
bool PacketParser:: validateCharacter(char c){
    for( char  b : numbersArray){
        if( c == b ){
            return true;
        }
    }
    return false;
}
void PacketParser::fillArray(char arr[], char c, int i){
    arr[i]= c;
}
bool PacketParser:: determineTransportCharacter(char c){
        if( c == '$'|| c ==',' || c = '\n'){
            return true;
        }
        return false;
    }
bool  PacketParser::isCharacterAllowed(char c){
        char invalidCharacters[] {'*','!','@','#','%','&','^','(',')','-','_','+','=','<','>','?','/','{',
                '[','}','}','\0','|',};
        for(char b : invalidCharacters){
            if( c == b){
                status = FieldStates::PACKET_ERROR;
                return false;
            }
        }

        return true;
    }
Packet PacketParser::createPacket( char c){
    Packet p;
    if(isCharacterAllowed(c)){
        if(determineTransportCharacter(c)){
            if( c == '$'){
                startPacket();
            } else if( c==','){
                processDemlimiter(c);
            } else if(c == '\n')
                return endPacket();
            }
        }else{
            validateCharacter(c);
            switch(state){
                case FieldLoadingState::FIELD1:;
                    fillArray(fieldArr1, c, i);
                    i++;
                    break;
                case FieldLoadingState::FIELD2:
                    fillArray(fieldArr2, c, j);
                    j++;
                    break;
                case FieldLoadingState::FIELD3:
                    fillArray(fieldArr3, c, k);
                    k++;
                    break;
            }
        }
    }
}