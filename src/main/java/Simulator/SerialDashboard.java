package Simulator;


import Simulator.Caculations.DataCalculations;
import Simulator.Caculations.DataDTO.DataDTO;
import Simulator.Caculations.DataDTO.SerialParserDTO;
import Simulator.CommandSection.CommandDTO;
import Simulator.CommandSection.CommandPane;
import Simulator.DataSection.DataPane;
import Simulator.GraphSection.GraphPane;
import Simulator.Parser.SerialParser;
import com.fazecast.jSerialComm.*;
import javafx.animation.AnimationTimer;
import javafx.application.Application;
import javafx.application.Platform;
import javafx.scene.Scene;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;

import java.nio.charset.StandardCharsets;


public class SerialDashboard extends Application {
    static SerialPort port = SerialPort.getCommPort("COM8");
    SerialParserDTO dto ;
    DataDTO dataDTO;
    CommandDTO commandDTO = new CommandDTO();
    DataCalculations c = new DataCalculations();
    double timeX = 0;
    boolean allowed = false;
    boolean open = open(port);
    long lastSend = 0;


    static SerialParser parser = new SerialParser(port);


    @Override
    public void start(Stage primaryStage) {
        Pane root = new Pane();
        startParser();
        GraphPane graphPane = new GraphPane();
        DataPane dataPane = new DataPane();
        CommandPane commandPane = new CommandPane();
        Scene scene = new Scene(root, 1200, 600);
        graphPane.setGraphLayout();
        dataPane.setDataPane();
        commandPane.setCommandPane();
        root.getChildren().addAll(graphPane, dataPane, commandPane);
        AnimationTimer timer = new AnimationTimer() {
            @Override
            public void handle(long l) {
                long now = System.currentTimeMillis();
                if (now - lastSend > 100 &&commandDTO.getKD() != commandPane.getKDSliderValue()||
                        commandDTO.getKP() != commandPane.getKPSliderValue()) {
                    commandDTO = commandPane.toDTO();
                    port.writeBytes(commandDTO.toString().getBytes(StandardCharsets.UTF_8), commandDTO.toString().length());
                    lastSend = now;
                }
                dto = parser.getLastDTO();
                c.fromDTO(dto);
                dataDTO = c.computeMetrics();
                timeX += 0.5;
                graphPane.updateGraph(timeX,dataDTO.getPosMap(),  dataDTO.getTargetMap() , dataDTO.getPower());
                dataPane.updateLabels(dataDTO);
                if (timeX > 800) {
                    graphPane.clearGraph();
                    timeX = 0;
                }
            }
        };
            primaryStage.setTitle("Motor Firmware Telemetry");
            primaryStage.setScene(scene);
            primaryStage.show();
            timer.start();
    }
    public static void main(String[] args) {
        launch(args);
    }
    public boolean open(SerialPort port){

        port.setComPortParameters(
                115200,
                8,
                SerialPort.ONE_STOP_BIT,
                SerialPort.NO_PARITY);

        port.setComPortTimeouts(
                SerialPort.TIMEOUT_READ_BLOCKING,
                1000,
                0);

        boolean opened = port.openPort();

        System.out.println("Opened = " + opened);
        System.out.println("Port = " + port.getSystemPortName());

        return opened;
    }
    public void startParser() throws IllegalThreadStateException{
        parser.start();
    }
    @Override
    public void stop() throws Exception{
        parser.stopPaser();
        super.stop();
    }
}
