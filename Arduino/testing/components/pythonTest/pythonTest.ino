void setup(){
    Serial.begin(9600);
}

char buf[10];

void loop(){
    // Response received
    if (Serial.available() > 0){
        buf[0] = Serial.read();
        // if (buf[0] == "B"){
        //     Serial.println(buf);
        // }
        // Serial.println(buf[0]);
    }
    delay(500);
    
    // Request new data
    Serial.println("U");
    delay(500);
}