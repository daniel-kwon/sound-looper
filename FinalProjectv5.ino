//const double ADD_FOR_OVERFLOW = 65535.0 / 15.625; // max timer valuer (16 bit) divided by prescalar*1000
//// to get value in seconds
//volatile double timer_val = 0.0; // variable to store timer value
//volatile bool record_state = 0; // bool that toggles on or off depending on if the record button
//// was pressed; 0 = not pressed, 1 = pressed
//volatile bool record_flag = 0; // bool that checks if the record button was just pressed since
//// the second interrupt of the button press needs to be filtered out
//// 0 = not pressed, 1 = pressed
//volatile int resistance = 0;  // variable that stores resistance values
//typedef struct sound {        // struct for the array that stores data for each button press
//  int button;                 // member that stores which button was pressed
//  // 1 = red, 2 = yellow, 3 = green, 4 = blue, 5 = base case for loop
//  double time_stamp;          // member that stores the time stamp that the button was pressed at
//  int loop_number;
//  int type;
//};
//volatile double press_end = 0;  // variable that stores the timestamp of when the button is unpressed
//volatile sound sequence[40];    // array of structs that stores the sequence of what to play
//volatile bool press_flag = 0;   // bool that determines whether a button is pressed down at the moment
//                                // 0 = not pressed, 1 = pressed
//volatile int record_counter = 1;  // counter that cycles through the array values for recording
//volatile int playback_counter = 1;  // counter that cycles through array values for playback
//volatile double interrupt_time = 0; // variable that stores the interrupt time when triggered
//volatile double last_interrupt_time = 0;  // variabel that stores the previous interrupt's time
//volatile bool track1_flag = 0;      // bool that checks if at least one recording has been saved
//volatile int loop_num = 1;
//
//
//
//void setup() {
//  Serial.begin(9600);                   // start serial monitor
//  pinMode(2, INPUT_PULLUP);             // interrupt pin
//  pinMode(7, OUTPUT);
//  attachInterrupt(0, handler, CHANGE);  // attach interrupt
//  sequence[0].button = 5;               // set base case of sequence
//  sequence[0].time_stamp = 0;           // set base case of sequence
//  cli();                                // turn off interrupts
//  TCCR1A = 0;                           // reset register values
//  TCCR1B |= (1 << CS12);                // set timer prescalar to value of 1024
//  TCCR1B &= ~(1 << CS11);               // set timer prescalar to value of 1024
//  TCCR1B |= (1 << CS10);                // set timer prescalar to value of 1024
//  TIMSK1 |= (1 << 0);                   // turn on timer overflow interrupt
//  sei();                                // turn on interrupts
//}
//
//void loop() {
//  for (playback_counter = 1; track1_flag == 1 && (sequence[playback_counter].button == 1 || sequence[playback_counter].button == 2 || sequence[playback_counter].button == 3 || sequence[playback_counter].button == 4 || sequence[playback_counter].button == 5); playback_counter++) {
//    if (record_state == 0 && playback_counter == 1){
//      digitalWrite(7, 1);
//      Serial.println();
//      Serial.println("Playback Begin");
//    }
//    else if (playback_counter > 1){
//      digitalWrite(7,0);
//    }
//    if(sequence[playback_counter].button == 1 || sequence[playback_counter].button == 2 || sequence[playback_counter].button == 3 || sequence[playback_counter].button == 4 || sequence[playback_counter].button == 5){
//      print_event();
//    }
//  }
//}
//
//void print_event() {
//  delay(long(sequence[playback_counter].time_stamp - sequence[playback_counter - 1].time_stamp));
//  Serial.print("Loop ");
//  Serial.print(sequence[playback_counter].loop_number);
//  Serial.print(" ");
//  print_button_colour(sequence[playback_counter].button);
//  if(sequence[playback_counter].type == 1){
//    Serial.print(" button ON at: ");
//  }
//  if(sequence[playback_counter].type == 2){
//    Serial.print(" button OFF at: ");
//  }
//  Serial.println(sequence[playback_counter].time_stamp);
//}
//
//void print_button_colour(int button_id) {
//  if (button_id == 1) {
//    Serial.print("RED");
//  }
//  if (button_id == 2) {
//    Serial.print("YELLOW");
//  }
//  if (button_id == 3) {
//    Serial.print("GREEN");
//  }
//  if (button_id == 4) {
//    Serial.print("BLUE");
//  }
//}
//
//
//double get_timer_val() {          // returns current timer value
//  double current_timer_val = 0;
//  cli();
//  current_timer_val = timer_val;
//  sei();
//  double temp = current_timer_val + (double(TCNT1) / 15.625);
//  return temp;
//}
//
//ISR(TIMER1_OVF_vect) {            // timer overflow interrupt
//  timer_val = timer_val + ADD_FOR_OVERFLOW;   // adds max timer value to timer_val each overflow
//}
//
//void turn_on_interrupts() {
//  sei();
//}
//
////void swap(sound &a; sound &b){    // swap function for sort
////  sound temp = a;
////  a = b;
////  b = temp;
////  return;
////}
//
//void sort(sound a[]) {     // sort function
//  for (int i = 2; i < 39; ++i) {
//    for (int j = i - 1; j >= 1 && a[j + 1].time_stamp < a[j].time_stamp && a[j + 1].button != 0; j--) {
//      sound temp = a[j];
//      a[j] = a[j + 1];
//      a[j + 1] = temp;
//    }
//  }
//  return;
//}
//
//void on_button_press_always() {   // on button press set press_flag to true and record_flag to false
//  press_flag = 1;
//  record_flag = 0;
//  if(sequence[record_counter].button == 0 || sequence[record_counter].time_stamp == 0){
//    record_counter--;
//  }
//  record_counter++;
//}
//
//void on_button_release() {        // on button release calculate press_time,
//  cli();                          // set press flag to false, and increment counter
//  sequence[record_counter].button = sequence[record_counter - 1].button;
//  sequence[record_counter].time_stamp = get_timer_val();  // store current time stamp
//  sequence[record_counter].loop_number = loop_num;
//  sequence[record_counter].type = 2;
//  Serial.println(sequence[record_counter].button);
//  Serial.println(sequence[record_counter].time_stamp);
//  Serial.println(sequence[record_counter].type);
//  Serial.println();
//  if(sequence[record_counter].button == 0 || sequence[record_counter].time_stamp == 0){
//    record_counter--;
//  }
//  record_counter++;
//  press_flag = 0;
//  Serial.println("RELEASE");
//}
//
//void white_button() {           // white button (record button)
//  cli();                        // turn off interrupts
//  if (record_state == 1) {      // on second button press (no recording indicator)
//    track1_flag = 1;            // begin playback
//    sort(sequence);             // sort array
//    Serial.println("sort");
//    loop_num++;
//    playback_counter = 1;
//    for (int w = 0; w < 39; w++) {
//      Serial.println(sequence[w].button);
//      Serial.println(sequence[w].time_stamp);
//      Serial.println(sequence[w].type);
//      Serial.println();
//    }
//  }
//  record_state = !record_state;     // toggle record_state
//  record_flag = 1;                  // indicate that record button was pressed
//  //  restart_flag = 1;                 // indicate to restart void loop();
//  Serial.println("record button");
//  Serial.println(record_state);
//  TCNT1 = 0;                        // set arduino timer to 0
//  timer_val = 0.0;                  // set timer variable to zero
//}
//
//void handler() {
//  interrupt_time = get_timer_val();                   // stores interrupt trigger time
//  if (interrupt_time - last_interrupt_time > 100) {
//    /* checks if time between last and current interrupt is
//                                                           less than 0.1 secconds*/
//    resistance = analogRead(0);                       // stores current resistance value
//    if (resistance < 100) {                           // triggers record button actions
//      white_button();
//    }
//    else if (record_state == 1) {                     // checks if record button has been pressed
//      if (record_flag == 1 && resistance > 1000) {    // filters button release of record button
//        record_flag = 0;
//      }
//      else if (press_flag == 0) {                     // checks if button is pressed of released
//        if (resistance < 200) {                       // triggers red button actions
//            sequence[record_counter].button = 1;                    // store red button indicator value
//            double current_timer_val = 0;
//            cli();
//            current_timer_val = timer_val;
//            sei();
//            double temp = current_timer_val + (double(TCNT1) / 15.625);
//            sequence[record_counter].time_stamp = temp;  // store current time stamp
//            sequence[record_counter].loop_number = loop_num;
//            sequence[record_counter].type = 1;
//            press_flag = 1;
//            record_flag = 0;
//            if(sequence[record_counter].button == 0 || sequence[record_counter].time_stamp == 0){
//              record_counter--;
//            }
//            record_counter++;
//        }
//        else if (resistance < 400) {                  // triggers yellow button actions
//          sequence[record_counter].button = 2;          
//          double current_timer_val = 0;
//          cli();
//          current_timer_val = timer_val;
//          sei();
//          double temp = current_timer_val + (double(TCNT1) / 15.625);
//          sequence[record_counter].time_stamp = temp;  // store current time stamp
//          sequence[record_counter].loop_number = loop_num;
//          sequence[record_counter].type = 1;
//          press_flag = 1;
//          record_flag = 0;
//          if(sequence[record_counter].button == 0 || sequence[record_counter].time_stamp == 0){
//            record_counter--;
//          }
//          record_counter++;
//        }
//        else if (resistance < 600) {                  // triggers green button actions
//          sequence[record_counter].button = 3;        
//          double current_timer_val = 0;
//          cli();
//          current_timer_val = timer_val;
//          sei();
//          double temp = current_timer_val + (double(TCNT1) / 15.625);
//          sequence[record_counter].time_stamp = temp;  // store current time stamp
//          sequence[record_counter].loop_number = loop_num;
//          sequence[record_counter].type = 1;
//          press_flag = 1;
//          record_flag = 0;
//          if(sequence[record_counter].button == 0 || sequence[record_counter].time_stamp == 0){
//            record_counter--;
//          }
//          record_counter++;
//        }
//        else if (resistance < 800) {                  // triggers blue button actions
//          sequence[record_counter].button = 1;                    // store red button indicator value
//          double current_timer_val = 0;
//          cli();
//          current_timer_val = timer_val;
//          sei();
//          double temp = current_timer_val + (double(TCNT1) / 15.625);
//          sequence[record_counter].time_stamp = temp;  // store current time stamp
//          sequence[record_counter].loop_number = loop_num;
//          sequence[record_counter].type = 1;
//          press_flag = 1;
//          record_flag = 0;
//          if(sequence[record_counter].button == 0 || sequence[record_counter].time_stamp == 0){
//            record_counter--;
//          }
//          record_counter++;
//        }
//      }
//      else if (press_flag == 1) {                     // checks if button is pressed of released
//        on_button_release();                          // triggers actions for button release
//      }
//    }
//  }
//  last_interrupt_time = interrupt_time;               /* sets interrupt time to be the previous interrupt time
//                                                         of the next interrupt */
//  turn_on_interrupts();                               // turn on interrupts
//}
//
//

