package com.example.controlapp;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.Toast;

import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;

public class MainActivity extends AppCompatActivity {
    private static String BROKER_URL = "";
    private static final String CLIENT_ID = "ControlApp";
    private MqttHandler mqttHandler;
    private String connectToastMsg = "";
    ImageButton ShootButton;
    ImageButton UpButton;
    ImageButton BottomButton;
    ImageButton LeftButton;
    ImageButton RightButton;
    Button ConnectButton;
    EditText addressTextField;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mqttHandler = new MqttHandler();
        ShootButton = (ImageButton) findViewById(R.id.ShootButton);
        ShootButton.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if(event.getAction()==MotionEvent.ACTION_DOWN){
                    //Toast.makeText(MainActivity.this, "SHOOT PRESS", Toast.LENGTH_SHORT).show();
                    publishMessage("ControlApp/Command","SHOOT");
                    return false;
                }
                else if (event.getAction() == MotionEvent.ACTION_UP){
                    //Toast.makeText(MainActivity.this, "SHOOT RELEASE", Toast.LENGTH_SHORT).show();
                    publishMessage("ControlApp/Command","STOP");
                    return false;
                }
                return true;
            }
        });
        UpButton = (ImageButton) findViewById(R.id.UpButton);
        UpButton.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if(event.getAction()==MotionEvent.ACTION_DOWN){
                    //Toast.makeText(MainActivity.this, "UP PRESS", Toast.LENGTH_SHORT).show();
                    publishMessage("ControlApp/Command","UP");
                    return false;
                }
                else if (event.getAction() == MotionEvent.ACTION_UP){
                    //Toast.makeText(MainActivity.this, "UP RELEASE", Toast.LENGTH_SHORT).show();
                    publishMessage("ControlApp/Command","STOP");
                    return false;
                }
                return true;
            }
        });
        BottomButton = (ImageButton) findViewById(R.id.BottomButton);
        BottomButton.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if(event.getAction()==MotionEvent.ACTION_DOWN){
                    //Toast.makeText(MainActivity.this, "DOWN PRESS", Toast.LENGTH_SHORT).show();
                    publishMessage("ControlApp/Command","DOWN");
                    return false;
                }
                else if (event.getAction() == MotionEvent.ACTION_UP){
                    //Toast.makeText(MainActivity.this, "DOWN RELEASE", Toast.LENGTH_SHORT).show();
                    publishMessage("ControlApp/Command","STOP");
                    return false;
                }
                return true;
            }
        });
        LeftButton = (ImageButton) findViewById(R.id.LeftButton);
        LeftButton.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if(event.getAction()==MotionEvent.ACTION_DOWN){
                    //Toast.makeText(MainActivity.this, "LEFT PRESS", Toast.LENGTH_SHORT).show();
                    publishMessage("ControlApp/Command","LEFT");
                    return false;
                }
                else if (event.getAction() == MotionEvent.ACTION_UP){
                    //Toast.makeText(MainActivity.this, "LEFT RELEASE", Toast.LENGTH_SHORT).show();
                    publishMessage("ControlApp/Command","STOP");
                    return false;
                }
                return true;
            }
        });
        RightButton = (ImageButton) findViewById(R.id.RightButton);
        RightButton.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if(event.getAction()==MotionEvent.ACTION_DOWN){
                    //Toast.makeText(MainActivity.this, "RIGHT PRESS", Toast.LENGTH_SHORT).show();
                    publishMessage("ControlApp/Command","RIGHT");
                    return false;
                }
                else if (event.getAction() == MotionEvent.ACTION_UP){
                    //Toast.makeText(MainActivity.this, "RIGHT RELEASE", Toast.LENGTH_SHORT).show();
                    publishMessage("ControlApp/Command","STOP");
                    return false;
                }
                return true;
            }
        });
        MqttConnectOptions options = new MqttConnectOptions();
        options.setCleanSession(true);
        options.setKeepAliveInterval(60);
        ConnectButton = (Button) findViewById(R.id.connect_btn);
        addressTextField = (EditText) findViewById(R.id.serverAddress);
        ConnectButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                BROKER_URL = addressTextField.getText().toString();
                connectToastMsg = "Connected to : " + BROKER_URL;
                mqttHandler.connect(BROKER_URL,CLIENT_ID);
                publishMessage("ControlApp/Connection","CONNECTED");
                Toast.makeText(MainActivity.this, connectToastMsg, Toast.LENGTH_SHORT).show();
            }
        });
    }
    private void publishMessage(String topic, String message){
        //Toast.makeText(this, "Publishing message: " + message, Toast.LENGTH_SHORT).show();
        mqttHandler.publish(topic,message);
    }
    private void subscribeToTopic(String topic){
        //Toast.makeText(this, "Subscribing to topic "+ topic, Toast.LENGTH_SHORT).show();
        mqttHandler.subscribe(topic);
    }
    @Override
    protected void onDestroy() {
        publishMessage("ControlApp/Connection", "DISCONNECTED");
        mqttHandler.disconnect();
        super.onDestroy();
    }
}