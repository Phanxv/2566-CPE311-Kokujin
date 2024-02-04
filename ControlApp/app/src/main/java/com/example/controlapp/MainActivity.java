package com.example.controlapp;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.widget.ImageButton;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    ImageButton ShootButton;
    ImageButton UpButton;
    ImageButton BottomButton;
    ImageButton LeftButton;
    ImageButton RightButton;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ShootButton = (ImageButton) findViewById(R.id.ShootButton);
        ShootButton.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if(event.getAction()==MotionEvent.ACTION_DOWN){
                    Toast.makeText(MainActivity.this, "SHOOT PRESS", Toast.LENGTH_SHORT).show();
                }
                else{
                    Toast.makeText(MainActivity.this, "SHOOT RELEASE", Toast.LENGTH_SHORT).show();
                }
                return true;
            }
        });
        UpButton = (ImageButton) findViewById(R.id.UpButton);
        UpButton.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if(event.getAction()==MotionEvent.ACTION_DOWN){
                    Toast.makeText(MainActivity.this, "UP PRESS", Toast.LENGTH_SHORT).show();
                }
                else{
                    Toast.makeText(MainActivity.this, "UP RELEASE", Toast.LENGTH_SHORT).show();
                }
                return true;
            }
        });
        BottomButton = (ImageButton) findViewById(R.id.BottomButton);
        BottomButton.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if(event.getAction()==MotionEvent.ACTION_DOWN){
                    Toast.makeText(MainActivity.this, "DOWN PRESS", Toast.LENGTH_SHORT).show();
                }
                else{
                    Toast.makeText(MainActivity.this, "DOWN RELEASE", Toast.LENGTH_SHORT).show();
                }
                return true;
            }
        });
        LeftButton = (ImageButton) findViewById(R.id.LeftButton);
        LeftButton.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if(event.getAction()==MotionEvent.ACTION_DOWN){
                    Toast.makeText(MainActivity.this, "LEFT PRESS", Toast.LENGTH_SHORT).show();
                }
                else{
                    Toast.makeText(MainActivity.this, "LEFT RELEASE", Toast.LENGTH_SHORT).show();
                }
                return true;
            }
        });
        RightButton = (ImageButton) findViewById(R.id.RightButton);
        RightButton.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if(event.getAction()==MotionEvent.ACTION_DOWN){
                    Toast.makeText(MainActivity.this, "RIGHT PRESS", Toast.LENGTH_SHORT).show();
                }
                else{
                    Toast.makeText(MainActivity.this, "RIGHT RELEASE", Toast.LENGTH_SHORT).show();
                }
                return true;
            }
        });
    }
}