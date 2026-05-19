package Simulator;


import Simulator.Caculations.DataCalculations;
import Simulator.Caculations.DataDTO.DataDTO;
import Simulator.Caculations.DataDTO.SerialParserDTO;
import Simulator.DataSection.DataPane;
import Simulator.GraphSection.GraphPane;
import Simulator.Parser.SerialParser;
import com.fazecast.jSerialComm.*;
import javafx.animation.AnimationTimer;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;



public class SerialDashboard extends Application {
    SerialPort port = SerialPort.getCommPort("COM7");
    SerialParserDTO dto ;
    DataDTO dataDTO;

    DataCalculations c = new DataCalculations();
    double timeX = 0;

   boolean open = open(port);



    SerialParser parser = new SerialParser(port);


    @Override
    public void start(Stage primaryStage) {
        Pane root = new Pane();
        startParser();
        GraphPane graphPane = new GraphPane();
        DataPane dataPane = new DataPane();
        Scene scene = new Scene(root, 1200, 600);
        graphPane.setGraphLayout();
        dataPane.setDataPane();
        root.getChildren().addAll(graphPane, dataPane);
        AnimationTimer timer = new AnimationTimer() {
            @Override
            public void handle(long l) {
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
        boolean open = port.openPort();
        setBaudRate(port);
        return open;

    }
    public void setBaudRate(SerialPort port){
        port.setBaudRate(115200);
    }
    public void startParser() throws IllegalThreadStateException{
        parser.start();
    }
}
