/*
	General Public License 3.0v
	Source url: https://github.com/devproje/arduino_works/blob/master/fnd_1234/fnd_1234.ino
 */

#define FND1000 12
#define FND100 11
#define FND10 10
#define FND1 9

class FND {
  private:
    int _delay = 2;
    int _fnd_bit[10][7] = {
      {1, 1, 1, 1, 1, 1, 0}, // 0
      {0, 1, 1, 0, 0, 0, 0}, // 1
      {1, 1, 0, 1, 1, 0, 1}, // 2
      {1, 1, 1, 1, 0, 0, 1}, // 3
      {0, 1, 1, 0, 0, 1, 1}, // 4
      {1, 0, 1, 1, 0, 1, 1}, // 5
      {1, 0, 1, 1, 1, 1, 1}, // 6
      {1, 1, 1, 0, 0, 1, 0}, // 7
      {1, 1, 1, 1, 1, 1, 1}, // 8
      {1, 1, 1, 1, 0, 1, 1}  // 9
};
  public:
    void set_delay(int ms) {
      _delay = ms;  
    }
    
    void print_fnd(int pin, int value) {
      digitalWrite(FND1000, FND1000 != pin);
      digitalWrite(FND100, FND100 != pin);
      digitalWrite(FND10, FND10 != pin);
      digitalWrite(FND1, FND1 != pin);

      for (int i = 0; i < 7; i++) {
        digitalWrite(i + 2, _fnd_bit[value][i]);
      }
      
      delay(_delay);
    }
};

void setup() {
  for (int i = 2; i < 13; i++) {
    pinMode(i, OUTPUT);
  }

  Serial.begin(9600);
}

void loop() {
  FND fnd = FND();

  for (int i = 0; i < 10000; i++) {
  
    fnd.print_fnd(FND1000, 1);
    fnd.print_fnd(FND100, 2);
    fnd.print_fnd(FND10, 3);
    fnd.print_fnd(FND1, 4);
  }
}
