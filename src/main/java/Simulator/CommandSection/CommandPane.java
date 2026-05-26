package Simulator.CommandSection;

import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;

public class CommandPane extends Pane {
    Rectangle rectangle = new Rectangle( 200,100, Color.LIGHTGRAY);
    Slider kP, kD, kI;
    Label kPLabel, kILabel, kDLabel;
    public void setCommandPane(){
        rectangle.setLayoutX(20);
        rectangle.setLayoutY(450);
        getChildren().addAll(rectangle, createKPSlider(),createKISlider(), createKDSlider(), createKDLabel(),
                createKILabel(), createKPLabel());
    }
    public Slider createKPSlider(){
        kP= new Slider();
        kP.setMax(1);
        kP.setMin(0.00);
        kP.setLayoutX(30);
        kP.setLayoutY(475);
        kP.setPrefWidth(195);
        return kP;
    }

    public Slider createKDSlider(){
        kD = new Slider();
        kD.setMax(0.35);
        kD.setMin(0.00);
        kD.setLayoutX(30);
        kD.setLayoutY(525);
        kD.setPrefWidth(195);
        return kD;
    }
    public Slider createKISlider(){
        kI = new Slider();
        kI.setMax(0.25);
        kI.setMin(0.00);
        kI.setLayoutX(30);
        kI.setLayoutY(500);
        kI.setPrefWidth(195);
        return kI;
    }
    public double getKDSliderValue(){
        return kD.getValue();
    }
    public double getKISliderValue(){
        return  kI.getValue();
    }
    public double getKPSliderValue(){
        return kP.getValue();
    }
    public Label createKPLabel(){
        kPLabel = new Label("Portional");
        kPLabel.setTextFill(Color.WHITE);
        kPLabel.setLayoutX(30);
        kPLabel.setLayoutY(460);
        return kPLabel;
    }
    public Label createKILabel(){
        kILabel = new Label("Intergal");
        kILabel.setTextFill(Color.WHITE);
        kILabel.setLayoutX(30);
        kILabel.setLayoutY(485);
        return kILabel;
    }
    public Label createKDLabel(){
        kDLabel = new Label("Derivate");
        kDLabel.setTextFill(Color.WHITE);
        kDLabel.setLayoutX(30);
        kDLabel.setLayoutY(510);
        return kDLabel;
    }
    public CommandDTO toDTO(){
        CommandDTO dto = new CommandDTO();
        dto.setKP(getKPSliderValue());
        dto.setKI(getKISliderValue());
        dto.setKD(getKDSliderValue());
        return  dto;
    }
}
