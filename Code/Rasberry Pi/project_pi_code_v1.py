import cv2
import numpy as np
import time
import RPi.GPIO as GPIO
from cv2 import aruco
import serial

GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)

serial_port ='/dev/serial0'
baud_rate = 9600
ser = serial.Serial(serial_port,baud_rate, timeout=1)

defective_lf=15
nondefective_rt= 13
inaruco=16
indir = 11
noman_aruco = 22

arucofollow = 18

red_led = 37
green_led =36

tot_def =0
tot_nondef =0

GPIO.setup(defective_lf,GPIO.OUT)
GPIO.setup(nondefective_rt,GPIO.OUT)
GPIO.setup(arucofollow,GPIO.OUT)
GPIO.setup(inaruco,GPIO.IN)
GPIO.setup(indir,GPIO.IN)


#leds
GPIO.setup(red_led,GPIO.OUT)
GPIO.setup(green_led,GPIO.OUT)


def send_command(command):
    ser.write(command.encode())
def send_command2(command):
    ser.write(str(command).encode('utf-8'))

def nothing(x):
    pass

def get_direction(frame):
    direction = 0  # left =1, right =2
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    l_b = np.array([100, 51, 51])
    u_b = np.array([130, 255, 255]) 
    mask = cv2.inRange(hsv, l_b, u_b)
    res = cv2.bitwise_and(frame, frame, mask=mask)
    
    # apply thresholding to convert the HSV image to a binary image
    ret,thresh = cv2.threshold(mask,150,255,0)

    # find the contours
    contours,hierarchy = cv2.findContours(thresh , cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
    for cnt in contours:
        x,y,w,h = cv2.boundingRect(cnt)
        if cv2.contourArea(cnt)<100:
             continue
        approx = cv2.approxPolyDP(cnt, 0.01*cv2.arcLength(cnt, True), True)
        #print (approx)
        if len(approx) == 3:
            res  = cv2.drawContours(res, [cnt], -1, (0,255,255), 3)
            # compute the center of mass of the triangle
            M = cv2.moments(cnt)
            if M['m00'] != 0.0:
                x = int(M['m10']/M['m00'])
                y = int(M['m01']/M['m00'])
            cv2.putText(res, 'Triangle', (x, y), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255, 255, 0), 2)

            if w > h:
                if approx[0][0][0] < x:
                    direction =2
                else:
                    direction = 1
            else:
                continue
    return direction
 
def detect_aruco(frame):
    defective = 0
    nondefective = 0 
    gray=cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
    key=getattr(aruco,f'DICT_{markerSize}X{markerSize}_{totalMarkers}')
    arucoDict = aruco.Dictionary_get(key)
    corners,ids,rejected=aruco.detectMarkers(gray,arucoDict)
    frame_markers = aruco.drawDetectedMarkers(frame.copy(), corners, ids)
    #cv2.imshow('frame_marker', frame_markers)
    
    if ids is not None:
        for i in range(len(ids)):
            if ids[i][0]%2 ==1:
                defective +=1
                GPIO.output(red_led,GPIO.HIGH)
                time.sleep(0.3)
                GPIO.output(red_led,GPIO.LOW)
                time.sleep(0.3)
                
            else:
                nondefective +=1
                GPIO.output(green_led,GPIO.HIGH)
                time.sleep(0.3)
                GPIO.output(green_led,GPIO.LOW)
                time.sleep(0.3)
    else:
        'Nothing Here'
    
    return defective,nondefective,ids

def noman_aruco(frame):
    defective = 0
    nondefective = 0 
    gray=cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
    key=getattr(aruco,f'DICT_{markerSize}X{markerSize}_{totalMarkers}')
    arucoDict = aruco.Dictionary_get(key)
    corners,ids,rejected=aruco.detectMarkers(gray,arucoDict)
    #cv2.imshow('frame_marker', frame_markers)
    
    if ids is not None:
        for i in range(len(ids)):
            if ids[i][0]%2 ==1:
                GPIO.output(red_led,GPIO.HIGH)
                time.sleep(0.3)
                GPIO.output(red_led,GPIO.LOW)
                
            else:
                nondefective +=1
                GPIO.output(green_led,GPIO.HIGH)
                time.sleep(0.3)
                GPIO.output(green_led,GPIO.LOW)            
    else:
        'Nothing Here'
    return ids


def aruco_drive(frame):
    defective = 0
    nondefective = 0 
    gray=cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
    key=getattr(aruco,f'DICT_{markerSize}X{markerSize}_{totalMarkers}')
    arucoDict = aruco.Dictionary_get(key)
    corners,ids,rejected=aruco.detectMarkers(gray,arucoDict)
    frame_markers = aruco.drawDetectedMarkers(frame.copy(), corners, ids)
    
    if ids is not None:
        corner_mid_point = corners[0][0][1][0] + (corners[0][0][0][0] - corners[0][0][1][0])/2
                    
    else:
        corner_mid_point = 0
    return corner_mid_point
    
cap = cv2.VideoCapture(0);
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 480)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 240)
markerSize=6
totalMarkers=250

GPIO.output(defective_lf,GPIO.LOW)
GPIO.output(nondefective_rt,GPIO.LOW)
GPIO.output(arucofollow,GPIO.LOW)

while(True):
    check_direction = GPIO.input(11)
    check_aruco = GPIO.input(16)
    check_noman_aruco = GPIO.input(22)
    
    if(check_direction == 1 and check_aruco ==0):
        for i in range(50):
            _, frame = cap.read()
            a = get_direction(frame)
            if a >0:
                if a ==  1:
                    GPIO.output(defective_lf,GPIO.HIGH)
                    print(a)
                    time.sleep(1)
                    break
                elif a == 2:
                    GPIO.output(nondefective_rt,GPIO.HIGH)
                    print(a)
                    time.sleep(1)
                    break
            else:
                continue
            print(a)
            time.sleep(0.3)
        GPIO.output(defective_lf,GPIO.LOW)
        GPIO.output(nondefective_rt,GPIO.LOW)
        
    elif(check_aruco ==1 and check_direction == 0):
        ret,frame = cap.read()
        def_count,nondef_count,identity = detect_aruco(frame)
        tot_def +=def_count
        tot_nondef += nondef_count
        print(identity)
        send_command(chr(12))
        message = "def = "
        message2 = "nondef = "
        send_command(message)
        send_command2(tot_def)

        send_command(chr(13))

        send_command(message2)
        send_command2(tot_nondef)
        
    elif(check_noman_aruco ==1):
        ret,frame = cap.read()
        identity = noman_aruco(frame)
        
        if identity is not None:
            GPIO.output(arucofollow,GPIO.HIGH)

        else:
            GPIO.output(arucofollow,GPIO.LOW)
            continue


    
    elif(check_direction ==1 and check_aruco ==1):
        ret,frame = cap.read()
        a = aruco_drive(frame)
        print(a)
        if(a == 0):
            GPIO.output(nondefective_rt,GPIO.LOW)
            GPIO.output(defective_lf,GPIO.LOW)            
        if(a >0 and a <150):
            GPIO.output(nondefective_rt,GPIO.LOW)
            GPIO.output(defective_lf,GPIO.HIGH)
            time.sleep(0.3)
            GPIO.output(defective_lf,GPIO.LOW)
        elif(a>350):
            GPIO.output(defective_lf,GPIO.LOW)
            GPIO.output(nondefective_rt,GPIO.HIGH)
            time.sleep(0.3)
            GPIO.output(nondefective_rt,GPIO.LOW)
        else:
            GPIO.output(defective_lf,GPIO.LOW)
            GPIO.output(nondefective_rt,GPIO.LOW)
        
        
    else:
        continue
        

cap.release()
cv2.destroyAllWindows()












