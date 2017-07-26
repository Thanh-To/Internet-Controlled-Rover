# The following program is derrived from pyimagesearch's http://www.pyimagesearch.com/2015/03/30/accessing-the-raspberry-pi-camera-with-opencv-and-python/
# and pythonprogramming.net's https://pythonprogramming.net/haar-cascade-object-detection-python-opencv-tutorial/
# The program detect human faces and send commands to a pan-tilt module via serial to ensure the face is always centered.

from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import numpy as np
import cv2
import serial

ser = serial.Serial('/dev/ttyACM0', 9600)

# multiple cascades: https://github.com/Itseez/opencv/tree/master/data/haarcascades

#https://github.com/Itseez/opencv/blob/master/data/haarcascades/haarcascade_frontalface_default.xml
face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')

camera = PiCamera()
camera.resolution = (853, 480)
camera.framerate = 24
rawCapture = PiRGBArray(camera, size=(853, 480))

globalWidth = 853
globalHeight = 480
globalCenterX = int(globalWidth/2)
globalCenterY = int(globalHeight/2)

for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
    img = frame.array
    img = cv2.flip(img,-1)
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, 1.3, 5)
    cv2.line(img,(globalCenterX,0),(globalCenterX,globalHeight),(0,255,0),1)
    cv2.line(img,(0,globalCenterY),(globalWidth,globalCenterY),(0,255,0),1)
    panCode = 0
    tiltCode = 0
    

    for (x,y,w,h) in faces:
        cv2.rectangle(img,(x,y),(x+w,y+h),(255,0,0),2)
        center_x = int(x+w/2)
        center_y = int(y+h/2)
        cv2.circle(img,(center_x, center_y), 5, (0,255,0), -1)
        roi_gray = gray[y:y+h, x:x+w]
        roi_color = img[y:y+h, x:x+w]

        if center_x < globalCenterX:
            panCode = 1
        elif center_x > globalCenterX:
            panCode = 2
        else:
            panCode = 0

        if center_y < globalCenterY:
            tiltCode = 2
        elif center_y > globalCenterY:
            tiltCode = 1
        else:
            tiltCode = 0

    cv2.imshow('img',img)
    ser.write(str(0) + ',' + str(panCode) + ',' + str(tiltCode) + '\n')
    rawCapture.truncate(0)
    
    k = cv2.waitKey(30) & 0xff
    if k == 27:
        break

cap.release()
cv2.destroyAllWindows()
