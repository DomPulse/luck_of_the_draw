// Pin Definitions
#define EN_PIN 8    // LOW: Driver enabled, HIGH: Driver disabled
#define STEP_PIN 10  // Step on the rising edge
#define DIR_PIN 9  // Set stepping direction

int microSecondsDelay = 1000;  // Delay in microseconds between each step
float steps_p_degree = 8.8888;
float goal_degree = 10.0;
float current_degree = 0.0;
int net_steps = 0; 

float p_coef = 10.0;
float i_coef = 0.02;
float d_coef = 0.2;

float p_error = 0.0;
float i_error = 0.0;
float d_error = 0.0;

float max_i = 100.0;
float min_i = -100.0;
float i_decay = 0.95;

float intensity = 0.0;
float alpha = 0.00001; //avoids div by 0?
float dwell_time = 1000.0;
long millis_last_move = 0;

void setup() 
{
  // Configure pin modes
  pinMode(EN_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  // Initialize pin states
  digitalWrite(DIR_PIN, LOW);  // Set initial direction
  digitalWrite(EN_PIN, LOW);   // Enable the driver

  Serial.begin(9600);
}

void loop()
{
  if (Serial.available() > 1) 
  {
    goal_degree = Serial.parseFloat();
  }

  calc_pid();
  dwell_time = 1.0/intensity;

  //Serial.print(current_degree);
  //Serial.print(" ");
  //Serial.println(goal_degree);

  if (millis() - millis_last_move > 100*abs(dwell_time))
  {
    millis_last_move = millis();
    digitalWrite(DIR_PIN, dwell_time > 0);
    digitalWrite(STEP_PIN, !digitalRead(STEP_PIN));
    current_degree += (1 - 2*(dwell_time < 0))/steps_p_degree;
  }

}

void calc_pid()
{
  p_error = goal_degree - current_degree;
  d_error = intensity;
  i_error += p_error;
  i_error *= i_decay;
  
  if (i_error > max_i)
  {
    i_error = max_i;
  }

  if (i_error < min_i)
  {
    i_error = min_i;
  }

  intensity = p_coef*p_error + i_coef*i_error + d_coef*d_error + alpha;
}
