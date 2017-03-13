#define RED_LED 15
#define GREEN_LED 12
#define BLUE_LED 13
#define BUTTON 4

#define BLINK_EVERY 1000

bool red_status = false;
bool green_status = false;
bool blue_status = false;
unsigned int last_blink_millis;

enum LedPolicy {LED_POLICY_OFF, LED_POLICY_ON, LED_POLICY_BLINK};

LedPolicy red_policy = LED_POLICY_OFF;
LedPolicy green_policy = LED_POLICY_OFF;
LedPolicy blue_policy = LED_POLICY_OFF;

void led_setup() {
  last_blink_millis = 0;
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(BUTTON, INPUT);
}

void led_loop() {
  unsigned int now = millis();
  if (now > last_blink_millis && now < last_blink_millis + BLINK_EVERY)
    return;
  if (red_policy == LED_POLICY_OFF) {
    red_status = false;
  } else if (red_policy == LED_POLICY_ON) {
    red_status = true;
  } else {
    red_status = !red_status;
  }

  if (green_policy == LED_POLICY_OFF) {
    green_status = false;
  } else if (green_policy == LED_POLICY_ON) {
    green_status = true;
  } else {
    green_status = !green_status;
  }

  if (blue_policy == LED_POLICY_OFF) {
    blue_status = false;
  } else if (blue_policy == LED_POLICY_ON) {
    blue_status = true;
  } else {
    blue_status = !red_status;
  }
  
  digitalWrite(RED_LED, red_status ? HIGH : LOW);
  digitalWrite(GREEN_LED, green_status ? HIGH : LOW);
  digitalWrite(BLUE_LED, blue_status ? HIGH : LOW);
  last_blink_millis = now;
}

void red_off() {
  red_policy = LED_POLICY_OFF;
}
void red_on() {
  red_policy = LED_POLICY_ON;
}
void red_blink() {
  red_policy = LED_POLICY_BLINK;
}

void green_off() {
  green_policy = LED_POLICY_OFF;
}
void green_on() {
  green_policy = LED_POLICY_ON;
}
void green_blink() {
  green_policy = LED_POLICY_BLINK;
}

void blue_off() {
  blue_policy = LED_POLICY_OFF;
}
void blue_on() {
  blue_policy = LED_POLICY_ON;
}
void blue_blink() {
  blue_policy = LED_POLICY_BLINK;
}


