package Simulator.CommandSection;

import javafx.scene.control.Slider;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;

public class CommandPane extends Pane {
    Rectangle rectangle = new Rectangle( 200,100, Color.LIGHTGRAY);
    Slider kP, kD;

    public void setCommandPane(){
        rectangle.setLayoutX(20);
        rectangle.setLayoutY(450);
        getChildren().addAll(rectangle, createKPSlider(), createKDSlider());
    }
    public Slider createKPSlider(){
        kP= new Slider();
        kP.setMax(1);
        kP.setMin(0.00);
        kP.setLayoutX(20);
        kP.setLayoutY(475);
        kP.setPrefWidth(195);
        return kP;
    }

    public Slider createKDSlider(){
        kD = new Slider();
        kD.setMax(0.35);
        kD.setMin(0.00);
        kD.setLayoutX(25);
        kD.setLayoutY(525);
        kD.setPrefWidth(195);
        return kD;
    }
    public double getKDSliderValue(){
        return kD.getValue();
    }
    public double getKPSliderValue(){
        return kP.getValue();
    }
    public CommandDTO toDTO(){
        CommandDTO dto = new CommandDTO();
        dto.setKP(getKPSliderValue());
        dto.setKD(getKDSliderValue());
        return  dto;
    }
}
