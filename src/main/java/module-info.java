module Simulator {
    requires javafx.controls;
    requires javafx.fxml;
    requires com.fazecast.jSerialComm;

    opens Simulator to javafx.graphics;

}