package Simulator.Caculations.DataDTO;

import Simulator.Parser.SerialParser;
import lombok.Getter;
import lombok.Setter;

/*
    Serial.print(String(controller.getTarget()) +","); target
    Serial.print(String(controller.computeError()) +",");  error
    Serial.print(String(controller.getLastError())+","); lastError
    Serial.print(String(vm.getPosition())+","); currentPos
    Serial.print(String(controller.getKp())+","); kP
    Serial.print(String(controller.getKd())+","); KD
    Serial.print(String(percentComplete)+"\n"); percentComplete
    Serial.print(String(controller.getPower) +",");
     */
@Getter
@Setter
public class SerialParserDTO {
    private double target, error, lastError, currentPos, kP,KD, percentComplete, power, kI;

}
