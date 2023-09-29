#include "simpletools.h" // Include simpletools
#include "servo.h" // Include servo library
#include "ping.h"  // Include Ultrasonic Sensor

void forward(void); 
void reverse_(void); //forward declaration of function to move robot forward at fastest speed
void stopmotors(void); //forward declaration of function to stop robot
void turnright(void); //forward declaration of function to turn robot
void turnleft(void);  //forward declaration of function to turn robot left
void turnright_lf(void);
void turnleft_lf(void);
void spinleft(void);  //forward declaration of function to spin robot left
void spinright(void); //forward declaration of function to spin robot right
void linefollow(void);//forward declaration of function to enable robot line follow at fastest speed
void calibrate(void *par1); //forward declaration of function to calibrate the Pulolo reflectance sensor
void intersection_blink(void *par2); // Intersection code
void pingfromcog2(void *par3);//forward declaration of function to read obstacle at the left of robot
void pingfromcog3(void *par4);//forward declaration of function to read obstacle at the right of robot
void aruco_follow(void);
void spinright_slow(void);
void spinleft_slow(void); 
void turnleft_slow(void);
void turnright_slow(void);

static volatile int blink;
volatile int sensor_mean;  // intersection variable
//volatile int front; // distance reading for front ultrasonic sensor
volatile int left;// distance reading for left ultrasonic sensor
volatile int right;// distance reading for right ultrasonic sensor
volatile int position, a; //position helps tell us where the black line is during line follow, while a helps us control when to calibrate and when to read position values
//volatile int intersection; //this helps us determine when we are at an intersection
volatile float scaled_sensor_val[8]; //stores the final reading of sensor values
unsigned int stack1[40 + 95]; // controls the second cog
unsigned int stack2[40 + 25]; //controls the third cog
unsigned int stack3[40 + 25]; //controls the 4th cog
unsigned int stack4[40 + 25]; //controls the 4th cog


int movecount;
int maininter; // counter for the center lane
int mainobstacle; // obstacle variable for the main lane
int allinter;
int section;
int left_flag;
int right_flag;
int c;
int d;
int l;
int r;
int aruco;
int park;
int main()                                    // Main function
{
  a = 1; // begin calibration
  cogstart((void*)calibrate, NULL, stack1, sizeof(stack1));// start up cog 1 and run calibrate function
  pause(2000); // wait 2 seconds
  
  
  movecount = 30;
  spinright(); // spin ring
  movecount = 60;
  spinleft(); // spin left
  movecount = 30;
  spinright(); // spin right
  stopmotors();  //stop motors
  a=2; // stop calibration and just keep reading position value
  
  // initial variables to operate sequences
  maininter = 0;
  mainobstacle =0;
  section =1;
  left_flag =0;
  right_flag =0;
  aruco =0;
  park =0;

  
  //variables to control turns
  


  //start ultrasonic cogs (2 and 3)
  cogstart((void*)intersection_blink, NULL, stack2, sizeof(stack2));  // start second cog
  cogstart((void*)pingfromcog2, NULL, stack3, sizeof(stack3)); // start third cog
  cogstart((void*)pingfromcog3, NULL, stack4, sizeof(stack4)); // start third cog
  
  set_direction(11,0);
  set_direction(15,0); 
  set_direction(13,0); 
  
  set_direction(8,1);
  set_direction(14,1); 
  set_direction(12,1);
  
  set_output(14,0);
  set_output(12,0);
  //set_direction(8,0);
  
  l =0;
  r =0;
  
  
  

  while(1)
  {         
    
   if(sensor_mean <300){
     do{
       
      if (park ==1){
        
        aruco_follow(); 

         }  
       else if(section ==4 && sensor_mean <50){
         movecount =20;  
         forward();
         pause(200);
         stopmotors();
         pause(50);
         set_output(12,1);
         l += input(15);
         r += input(13);
         set_output(12,0);
         set_output(8,1);
         
         
         if(l>0 && aruco ==0){
           do{
           aruco += input(11);
           movecount =10;
           spinleft_slow();
           pause(5);
           stopmotors();
           pause(200);
           park = 1;          
          }while(l>0 && aruco ==0);            
            }
            
         else if (r>0 && aruco ==0){
           do{
           aruco +=input(11);
           movecount =10;
           spinright_slow();
           pause(5);
           stopmotors();
           pause(200); 
           park = 1;
        } while(r>0 && aruco ==0);   
                 
       } 
       
        set_output(8,0);
        movecount = 20;
        stopmotors(); 
        pause(100);        
         
         }
         

       
       else if(maininter ==0){
       set_output(12,1);
       l += input(15);
       r += input(13);
       linefollow();
       }
       
       else if(maininter ==2 && left ==1 && mainobstacle ==0 && left_flag ==1){
            mainobstacle +=1;
            maininter +=1;
            movecount = 20;
            forward();
            pause(500);
            spinleft();
            pause(200);
            stopmotors();
            reverse_();
            pause(1100);
            stopmotors();
            set_output(14,1);
            set_output(14,0);
            pause(2000);
            forward();
            pause(1100);
            spinleft();
            pause(200);          
         }
        else if(maininter ==6 && right ==1 && mainobstacle ==1 && left_flag ==1){
            mainobstacle +=1;
            maininter +=1;            
            movecount = 20;
            forward();
            pause(650);
            spinright();
            pause(200);
            stopmotors();
            reverse_();
            pause(1100);
            stopmotors();            
            set_output(14,1);       
            set_output(14,0);            
            pause(2000);
            forward();
            pause(1100);
            spinleft();
            pause(200); 
         }  
       else if(maininter ==2 && right ==1 && mainobstacle ==0 && right_flag ==1){
            mainobstacle +=1;
            maininter +=1;            
            movecount = 20;
            forward();
            pause(750);
            spinright();
            pause(200);
            stopmotors();
            reverse_();
            pause(1100);
            stopmotors();            
            set_output(14,1);
            set_output(14,0);            
            pause(2000);
            forward();
            pause(1100);
            spinright();
            pause(200);       
         }
        else if(maininter ==6 && left ==1 && mainobstacle ==1 && right_flag ==1){
            mainobstacle +=1;
            maininter +=1;
            movecount = 20;
            forward();
            pause(500);
            spinleft();
            pause(200);
            stopmotors();
            reverse_();
            pause(1100);
            stopmotors();            
            set_output(14,1);
            set_output(14,0);            
            pause(2000);
            forward();
            pause(1100);
            spinright();
            pause(200); 
         }              
       
       else{
         linefollow();
         }
       }while(sensor_mean<300);
     }
        
   else if(sensor_mean>300){
     
     
     if(park ==1){
       do{
         stopmotors();
         pause(5);
         blink =1;
         }while(park ==1);
       }
     else if(maininter ==0){
       maininter +=1;
       movecount =20;
       stopmotors();
       set_output(12,1);
       l += input(15);
       r += input(13);
       set_output(12,0);
       blink =1;
       
       if(l>0){
         l=0;
         left_flag =1;
         movecount =20;
         turnleft();
         pause(600);

          } 
       else if (r>0){
         r =0;
         right_flag =1;
         movecount =20;
         turnright();
         pause(600);
        
       }                 
         
         } 
         
      else if(maininter ==1 && left_flag ==1){
          maininter +=1;
          movecount =20;
          turnright();
          pause(600); 
          blink =1;       
        }
      else if ((maininter ==3||maininter==5 ||maininter ==7) && left_flag ==1){
          maininter +=1;
          movecount =20;
          turnleft();
          pause(600); 
          blink =1;
        }
      else if (maininter ==8 && left_flag ==1){
      
          maininter =0;
          mainobstacle =0;
          left_flag =0;
          movecount =20;
          section +=1;
          turnright();
          pause(600);  
          blink =1;   
    }
      
      else if(maininter ==1 && right_flag ==1){
         maininter +=1;
         movecount =20;
         turnleft();
         pause(600);
         blink =1;        
        }
      else if ((maininter ==3||maininter==5 ||maininter ==7) && right_flag ==1){
          maininter +=1;
          movecount =20;
          turnright();
          pause(600);
          blink =1; 
        }
        
      else if (maininter ==8 && right_flag ==1){
      
          maininter =0;
          mainobstacle =0;
          right_flag =0;
          movecount =20;
          section +=1;
          turnleft();
          pause(600);
          blink =1;     
    }     
      else{
        maininter +=1;
        movecount = 20;
        forward();
        pause(100); 
        blink =1;
        }
       
          
       }
        
  }  
}


void calibrate(void *par1){
  int cal_ini_sensor_val[8];
  int cal_sensor_val[8];
  int max_cal[8];
  int min_cal[8];
  int cal_value;
  int sensor_ini_val[8];
  int sensor_val[8];
  int sensor_scale_sum;
  
  set_directions(7, 0, 0b11111111);          // P7...P0 -> output
  set_outputs(7, 0, 0b11111111);
  pause(10);
  for(int i=0;i<8;i++){
    cal_ini_sensor_val[i] = rc_time(i,1);
    max_cal[i] = cal_ini_sensor_val[i];
    min_cal[i]= cal_ini_sensor_val[i];
  }

 while(a==1)
  {
    set_directions(7, 0, 0b11111111);          // P7...P0 -> output
    set_outputs(7, 0, 0b11111111);
    pause(10);
  
  for(int i=0;i<8;i++){
    cal_sensor_val[i] = rc_time(i,1);
  } 
 
  for(int i=0;i<8;i++){
  if(min_cal[i] >cal_sensor_val[i]){
      min_cal[i]= cal_sensor_val[i];
    }
    else if (max_cal[i]<cal_sensor_val[i]){
      max_cal[i] = cal_sensor_val[i];
      }
    }
  }
  
   while(a==2){
    set_directions(7, 0, 0b11111111);          // P7...P0 -> output
    set_outputs(7, 0, 0b11111111);
    pause(10);    
   for(int i=0;i<8;i++){
    sensor_ini_val[i] = rc_time(i,1);
    sensor_val[i] = sensor_ini_val[i];
      if(sensor_val[i]< min_cal[i]){
        sensor_val[i] = min_cal[i];          
      }
      else if (sensor_val[i] >max_cal[i]){
        sensor_val[i] = max_cal[i];
        }
   }
     sensor_scale_sum = 0;      
     for(int i=0;i<8;i++){
       float A = (float)(max_cal[i] -sensor_val[i]);
       float B =(float) (max_cal[i] - min_cal[i]);
       float C = (A/B);
       scaled_sensor_val[i] = 1000 -(1000*(C));
       sensor_scale_sum  += scaled_sensor_val[i];
       
       }
    sensor_mean = (int)(sensor_scale_sum/8);
    float D = 0*scaled_sensor_val[0]+ 1000*scaled_sensor_val[1]+2000*scaled_sensor_val[2]+3000*scaled_sensor_val[3]+4000*scaled_sensor_val[4]+5000*scaled_sensor_val[5]+6000*scaled_sensor_val[6]+7000*scaled_sensor_val[7];
    float E = scaled_sensor_val[0]+ scaled_sensor_val[1]+scaled_sensor_val[2]+scaled_sensor_val[3]+scaled_sensor_val[4]+scaled_sensor_val[5]+scaled_sensor_val[6]+scaled_sensor_val[7];
    position = (int)(D/E);

    }   
       
} 
void turnright_lf(void) {
  for (int i = 0; i < movecount; i++) {
    servo_speed(16,30);
    servo_speed(17,0);
    pause(20);
  }
}

// turn robot right by stopping left motor and turning right motor forward
void turnleft_lf(void) {
  for (int i = 0; i < movecount; i++) {
    servo_speed(16,0);
    servo_speed(17,-30);
    pause(20);
  }
}

void linefollow(void){
     if (position < 3000) {
    do {
      movecount = 1;
      turnright_lf();
       } while (position < 3000);
  } else if (position > 4000)
    do {
      movecount = 1;
      turnleft_lf();
     
    } while (position > 4000);
  movecount = 2;
  forward();
 }  
 

// blink led at intersection
void intersection_blink(void *par2) {
  while(1){
    
    //whenever blink is 0 turn off both leds
    while(blink ==0){
      low(26);
      pause(10);
      }
    
    
    while(blink ==1){ //when blink is one turn on red led, wait for 0.2 seconds and turn it off
    high(26);
    pause(200);
    blink =0;
    
  }  
} 
}

// read distance with left ultrasonic sensor then convert it to an obstacle true or false. 
void pingfromcog2(void *par3) {
  int a;
  while(1)
{
  a =ping_cm(10);
  if(a>7){
    left = 0;}
  else if(a>2 && a <7){
    left = 1;
    } 
}
}

// read distance with right ultrasonic sensor then convert it to an obstacle true or false. 
void pingfromcog3(void *par4) {
  int a;
  while(1)
{
  a =ping_cm(9);
  if(a>7){
    right = 0;}
  else if (a>2 && a<7) {
    right = 1;
    } 
}
}
void forward(void) {
  for (int i = 0; i < movecount; i++) {
    servo_speed(16,30);
    servo_speed(17,-30);
    pause(5);
  }
}

// stop robot by stopping both motors 
void stopmotors(void) {
  for (int i = 0; i < movecount; i++) {
    servo_speed(16,0);
    servo_speed(17,0);
    pause(20);
  }
}
// turn robot right by stopping right motor and turning left motor forward
void turnright(void) {
  for (int i = 0; i < movecount; i++) {
    servo_speed(16,95);
    servo_speed(17,0);
    pause(20);
  }
}

// turn robot right by stopping left motor and turning right motor forward
void turnleft(void) {
  for (int i = 0; i < movecount; i++) {
    servo_speed(16,0);
    servo_speed(17,-95);
    pause(20);
  }
}

// spin robot right by turning both motors forward 
void spinright(void) {
  for (int i = 0; i < movecount; i++) {
    servo_speed(16,95);
    servo_speed(17,95);
    pause(20);
  }
}

void spinright_slow(void) {
  for (int i = 0; i < movecount; i++) {
    servo_speed(16,20);
    servo_speed(17,20);
    pause(20);
  }
}
// spin robot left by turning both motors backwards
void spinleft(void) {
  for (int i = 0; i < movecount; i++) {
    servo_speed(16,-95);
    servo_speed(17,-95);
    pause(20);
  }
}
void spinleft_slow(void) {
  for (int i = 0; i < movecount; i++) {
    servo_speed(16,-20);
    servo_speed(17,-20);
    pause(20);
  }
}

void aruco_follow(void){
  
    set_output(12,1);
    set_output(14,1);
    
    int pi = input(15);
    int pi2 = input(13);
    
    
    if (pi2 ==1) {
    do {
      pi2 = input(13);
      movecount = 2;
      turnright_slow();
      pause(5);

       } while (pi2 ==1);
  } else if (pi ==1)
    do {
      pi = input(15);
      movecount = 2;
      turnleft_slow();
      pause(5);
     
    } while (pi ==1);
  movecount = 2;
  forward();  
 
  
  }
  
void turnright_slow(void) {
  for (int i = 0; i < movecount; i++) {
    servo_speed(16,20);
    servo_speed(17,0);
    pause(5);
  }
}

// turn robot right by stopping left motor and turning right motor forward
void turnleft_slow(void) {
  for (int i = 0; i < movecount; i++) {
    servo_speed(16,0);
    servo_speed(17,-20);
    pause(5);
  }
}
void reverse_(void) {
  for (int i = 0; i < movecount; i++) {
    servo_speed(16,-30);
    servo_speed(17,30);
    pause(5);
  }
}





      
      
    