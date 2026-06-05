#include "PACKETPARSER.h"
void PacketParser:: startPacket(){
    // Set state to Field 1
    status = FieldStates::BUILDING_PACKET;
    p.setStartTime(millis());
    state = FieldLoadingState::FIELD1;
    // clear all the array data
    p.setStatus(PacketStatus::NOT_VALIDATED_YET);
    std::fill(std::begin(field1Arr), std::end(field1Arr), NULL);
    std::fill(std::begin(field2Arr), std::end(field2Arr), NULL);
    std::fill(std::begin(field3Arr), std::end(field3Arr), NULL);
    // reset all indexes to 0
    i = 0; j = 0; k= 0;
}
Packet PacketParser:: endPacket(){
    //assume vaild only override if not
    status = FieldStates::PACKET_COMPELTE;
    p.setCompletionStatus(PacketCompletionStatus::VALID_COMPLETION_TIME);
    field1Arr[i] = '\0';
    field2Arr[j] = '\0';
    field3Arr[k] = '\0';
    if(checkForEmptys()){
       p.setStatus(PacketStatus::INVALID_NULL);
       p.setCompletionTime(millis());
       return p;
    }

    p.setKP(atof(field1Arr));
    p.setKI(atof(field2Arr));
    p.setKD(atof(field3Arr));
    p.setCompletionTime(millis());
    // assume valid override if not
    p.setStatus(PacketStatus::VALID);
    checkCompletionStatus(p);
    checkValues(p);
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
        if( c == '$'|| c ==',' || c == '\n'){
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
    if(isCharacterAllowed(c)){
        if(determineTransportCharacter(c)){
            if( c == '$'){
                startPacket();
                return p;
            } else if( c==','){
                processDemlimiter(c);
                return p;
            } else if(c == '\n'){
                return endPacket();
            }
        }else{
            if(validateCharacter(c)){
                switch(state){
                    case FieldLoadingState::FIELD1:;
                        fillArray(fieldArr1, c, i);
                        i++;
                        p.setStatus(PacketStatus::NOT_VALIDATED_YET);
                        return p;
                    case FieldLoadingState::FIELD2:
                        fillArray(fieldArr2, c, j);
                        j++;
                        p.setStatus(PacketStatus::NOT_VALIDATED_YET);
                        return p;
                    case FieldLoadingState::FIELD3:
                        fillArray(fieldArr3, c, k);
                        k++;
                        p.setStatus(PacketStatus::NOT_VALIDATED_YET);
                        return p;
                    default:
                        p.setStatus(PacketStatus::PACKET_INCOMPLETE_ERROR);
                        return p;
                }
            }else{
                p.setCompletionTime(millis());
                p.setStatus(PacketStatus::INVALID_CHARACTER);
                return p;
            }
        }
    }else{
        p.setCompletionTime(millis());
        p.setStatus(PacketStatus::INVALID_CHARACTER);
        return p;
    }
}
void PacketParser::checkCompletionStatus(Packet& p){
    if(p.getCompletionTime() - p.getStartTime() > 1000){
        p.setCompletionStatus(PacketCompletionStatus::INVAILD_PACKET_TIMEOUT);
    }else{
        p.setCompletionStatus(PacketCompletionStatus::VALID_COMPLETION_TIME);
    }
}
bool PacketParser:: checkForEmptyValues(){
    if(field1Arr[0] == NULL|| field2Arr[0] == NULL|| field3Arr[0] == NULL ){
        return true;
    }
    return false;
void PacketParser::checkValues(Packet& p){
    if(p.getKP() > 1|| p.getKI()> 0.1|| p.getKD() > 0.5 || p.getKP() < 0 || p.getKI() < 0|| p.getKD() < 0){
        p.setStatus(PacketStatus::INVAILD_PACKET_RANGE)
    }else
       p.setStatus(PacketStatus::VALID);
    }
}