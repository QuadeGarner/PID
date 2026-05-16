module Simulator {
    requires javafx.controls;
    requires javafx.fxml;
    requires com.fazecast.jSerialComm;
    requires static lombok;

    opens Simulator to javafx.graphics;

}