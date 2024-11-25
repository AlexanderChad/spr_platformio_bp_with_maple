#include <Arduino.h>

#define LED_BLINK_PIN PC13

void setup()
{
  pinMode(LED_BLINK_PIN, OUTPUT);
  Serial.begin();
  Serial.println("Started");
}

// Macros SW-timer, example: timer(cn_print, millis(), 1000)
#define timer(name, time_stamp, delay_ms)    \
  uint8_t time_flag_##name = 0;              \
  static uint32_t timer_##name = time_stamp; \
  if (time_stamp - timer_##name > delay_ms)  \
  {                                          \
    timer_##name = time_stamp;               \
    time_flag_##name = 0xFF;                 \
  }                                          \
  if (time_flag_##name)
// ==========================================================

// таск мигания светодиодом на плате
void blink_led_task()
{
  timer(led_blink, millis(), 500)
  {
    digitalWrite(LED_BLINK_PIN, !digitalRead(LED_BLINK_PIN));
  }
}

// таск печати условных секунд от момента запуска
void print_i_cn_task()
{
  static uint8_t i_cn = 0;
  timer(print_i_cn, millis(), 1000)
  {
    Serial.print("i_cn=");
    Serial.println(++i_cn);
  }
}

// таск ответа на нажатие цифровых кнопок 1, 2, 3 на клавиатуре (в терминале)
void serial_echo_pressed_button_task()
{
  if (Serial.available())
  {
    char in_ch = Serial.read();
    Serial.print("You pressed button \"");
    switch (in_ch)
    {
    case '1':
      Serial.print("one");
      break;
    case '2':
      Serial.print("two");
      break;
    case '3':
      Serial.print("three");
      break;
    default:
      Serial.print("unknown");
      break;
    }
    Serial.println("\"");
  }
}

void loop()
{
  blink_led_task();
  print_i_cn_task();
  serial_echo_pressed_button_task();
}
