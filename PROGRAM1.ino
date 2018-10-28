int led1 = 7; //set leds and button with the corresponding Arduino pin 
int led2 = 6;
int led3 = 5;
const int button1 = 2;
const int button2 = 3;
const int button3 = 4;

int rnd = 0; // counts the round you are playing
int lifes = 3; // sets lifes to three 

String questions[3] = { "What is the capital of Turkey?\n  A. Ankara\n B. Istanbul\n C. Cappadocia", 
                        "Which of these singers is blind?\n A. Steven Tyler\n B. Stevie Wonder\n C. Bob Dylan", 
                        "Which car brand is not from Germany?\n A. Mercedes Benz\n B. Dodge\n C. Porsche" }; //write the questions and the answers 
                        
int buttonResponses[3] = {0, 1, 1}; //sets the correct button response

void setup() {
  pinMode(button1, INPUT); // set button as input and leds as outputs
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  digitalWrite(led1, HIGH);// turn on the three leds
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  Serial.begin(9600); // display 
}

void loop() {

  Serial.println(questions[rnd]); // prints the first question 

  while (digitalRead(button1) == HIGH && digitalRead(button2) == HIGH && digitalRead(button3) == HIGH) {} // holds the next question until you press a button 

  int resp; // acts as the index of the buttonResponses vector 
  if (digitalRead(button1) == LOW) { // if the right button is pressed resp values indicates the position of the right answer in each case
    resp = 0;
  } else if (digitalRead(button2) == LOW) {
    resp = 1;
  } else {
    resp = 2;
  }

  if (resp == buttonResponses[rnd]) { 
    rnd++; // makes the round counter increase by one when the answer is correct
    Serial.println("CORRECT!:)"); // prints correct in the screen 
    delay(500); // debounce
  } else {
    rnd = rnd; // if the answer is incorrect it stays in the same round
    Serial.println("WRONG!;("); // prints wrong in the screen 
    lifes --; // set the lifes counter minus one 
    setleds(lifes); // turns off one led
    delay(500);
  }

  if (lifes == 0) { // makes everything reset to start again 
    lifes = 3;
    rnd = 0;
    setleds(lifes);
    Serial.println("START AGAIN");
  }
  delay(500);
}

void setleds(int l) { // turns off one led when the answer is incorrect 
  if (l == 3) { // l is the number of lifes you have left
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
  } else if (l == 2) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
  } else if (l == 1) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
  } else if (l == 0) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  } else {
    Serial.println("ERROR"); // easy way to detect a problem in the code 
  }
}
