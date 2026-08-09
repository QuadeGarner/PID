package Simulator.Parser;

import Simulator.Caculations.DataDTO.SerialParserDTO;
import com.fazecast.jSerialComm.SerialPort;
import com.fazecast.jSerialComm.SerialPortIOException;
import com.fazecast.jSerialComm.SerialPortTimeoutException;
import javafx.application.Platform;
import lombok.Getter;
import lombok.Setter;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Scanner;
@Setter
@Getter
public class SerialParser extends Thread {
    SerialPort port;
    private double target, error, lastError, currentPos, kP, kI, KD, percentComplete, power;
    String start = "";
    BufferedReader bufferedReader ;
    private boolean running = true;
    public SerialParser(SerialPort port) {
        this.port = port;
        bufferedReader = new BufferedReader(new InputStreamReader(port.getInputStream()));
    }

    /*
    Serial.print(String(controller.getTarget()) +","); target
    Serial.print(String(controller.computeError()) +",");  error
    Serial.print(String(controller.getLastError())+","); lastError
    Serial.print(String(vm.getPosition())+","); currentPos
    Serial.print(String(controller.getKp())+","); kP
    Serial.print(String(controller.getKd())+","); KD
    Serial.print(String(percentComplete)+"\n"); percentComplete
     */
    public  void scanData(){
        try {
            String s = bufferedReader.readLine();
            String[] stringSplit = s.split(",");
            if (!(stringSplit.length != 9 || stringSplit[0].isEmpty() || stringSplit[1].isEmpty() ||
                    stringSplit[2].isEmpty() || stringSplit[3].isEmpty() || stringSplit[4].isEmpty() || stringSplit[5].isEmpty()
                    || stringSplit[6].isEmpty() || stringSplit[7].isEmpty()||stringSplit[8].isEmpty())) {
                setTarget(Double.parseDouble(stringSplit[0]));
                setError(Double.parseDouble(stringSplit[1]));
                setLastError(Double.parseDouble(stringSplit[2]));
                setCurrentPos(Double.parseDouble(stringSplit[3]));
                setKP(Double.parseDouble(stringSplit[4]));
                setKI(Double.parseDouble(stringSplit[5]));
                setKD(Double.parseDouble(stringSplit[6]));
                setPercentComplete(Double.parseDouble(stringSplit[7]));
                setPower(Double.parseDouble(stringSplit[8]));
            }
        }catch (SerialPortTimeoutException ignored){
        } catch (IOException e) {
            e.printStackTrace();
            stopPaser();
            Platform.exit();
        }
    }
    public SerialParserDTO toDTO(){
        SerialParserDTO dto = new SerialParserDTO();
        dto.setTarget(getTarget());
        dto.setError(getError());
        dto.setLastError(getLastError());
        dto.setKD(getKD());
        dto.setKI(getKI());
        dto.setKP(getKP());
        dto.setPercentComplete(getPercentComplete());
        dto.setCurrentPos(getCurrentPos());
        dto.setPower(getPower());
        return dto;
    }
    public void run(){
        while(running){
            scanData();
        }
    }
    public void stopPaser(){
        running = false;
        port.closePort();
    }
    public SerialParserDTO getLastDTO(){
        return toDTO();
    }
}
