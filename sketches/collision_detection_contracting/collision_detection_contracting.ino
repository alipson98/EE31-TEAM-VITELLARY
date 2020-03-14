
// Collision Detection Constants
const int coll_detector = 18; // Must be an interrupt pin
const int front_bumper_in = 52;
// End Collision Detection Constants

// TODO: remove
const int ledpin = 13;

/*
 * BumperInfo
 * Holds all bumper information
 * front, left, right, back are true if the corresponding bumper pushed
 * collision true if any pushed (poll this variable)
 */
struct BumperInfo {
    bool front, left, right, back;
    bool collision;
};

BumperInfo bumpers;

void setup() {
  pinMode(coll_detector, INPUT);
  pinMode(ledpin, OUTPUT); // TODO: remove
  pinMode(front_bumper_in, INPUT);
  attachInterrupt(digitalPinToInterrupt(coll_detector), collisionISR, RISING);
  digitalWrite(ledpin, LOW);
}


void loop() {
    if (bumpers.collision) {
        if (bumpers.front) digitalWrite(ledpin, !digitalRead(ledpin));
        clearBumpers();
    }

}

void collisionISR(){
    if (digitalRead(front_bumper_in) == HIGH){
         bumpers.front = true;
         bumpers.collision = true;
    }
}

/*
 * clearBumpers
 * args: none
 * rets: none
 * does: set all bumper info to false
 *       call after handling a collision
 */
void clearBumpers() {
    bumpers.collision = false;
    bumpers.front = false;
    bumpers.back = false;
    bumpers.left = false;
    bumpers.right = false;
}
