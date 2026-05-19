package Simulator.GraphSection;

import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Polyline;
import javafx.scene.shape.Rectangle;


public class GraphPane extends Pane{

    Polyline targetLine, motorLine, powerLine;
    public Rectangle rect = new Rectangle(800, 400, Color.LIGHTGRAY);

    public void setGraphLayout(){
        rect.setLayoutX(50);
        getChildren().addAll(rect, createMotorLine(),createPowerLine(), createTargetLine());

    }
    public void updateGraph(double time, double targetPoint, double motorPoint, double powerPoint){
        addTargetPoint(time, 200 - targetPoint);
        addMotorPoint(time, 200- motorPoint);
        addPowerPoint(time,300 - (powerPoint * 80));
    }
    public void clearGraph(){
        motorLine.getPoints().clear();
        powerLine.getPoints().clear();
        targetLine.getPoints().clear();
    }
    public Polyline createMotorLine(){
        motorLine = new Polyline();
        motorLine.setLayoutX(50);
        motorLine.setStroke(Color.YELLOW);
        motorLine.setStrokeWidth(2);
        return motorLine;
    }
    public Polyline createPowerLine(){
        powerLine = new Polyline();
        powerLine.setLayoutX(50);
        powerLine.setStroke(Color.WHITE);
        powerLine.setStrokeWidth(2);
        return powerLine;
    }
    public Polyline createTargetLine(){
        targetLine = new Polyline();
        targetLine.setLayoutX(50);
        targetLine.setStroke(Color.GREEN);
        targetLine.setStrokeWidth(2);
        return targetLine;
    }
    public void addTargetPoint(double time, double point ){
        targetLine.getPoints().addAll(time, point);
    }
    public void addMotorPoint(double time, double point){
        motorLine.getPoints().addAll(time, point);
    }
    public void addPowerPoint(double time, double point){
        powerLine.getPoints().addAll(time, point);
    }


}
