package com.example.controlapp;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
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
        ShootButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(MainActivity.this, "SHOOTING!", Toast.LENGTH_SHORT).show();
            }
        });
        UpButton = (ImageButton) findViewById(R.id.UpButton);
        UpButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(MainActivity.this, "GOING UP!", Toast.LENGTH_SHORT).show();
            }
        });
        BottomButton = (ImageButton) findViewById(R.id.BottomButton);
        BottomButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(MainActivity.this, "GOING DOWN!", Toast.LENGTH_SHORT).show();
            }
        });
        LeftButton = (ImageButton) findViewById(R.id.LeftButton);
        LeftButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(MainActivity.this, "TURN LEFT!", Toast.LENGTH_SHORT).show();
            }
        });
        RightButton = (ImageButton) findViewById(R.id.RightButton);
        RightButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(MainActivity.this, "TURN RIGHT!", Toast.LENGTH_SHORT).show();
            }
        });
    }
}