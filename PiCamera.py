from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import cv2

camera = PiCamera()
camera.resolution = (853, 480)
camera.framerate = 24
rawCapture = PiRGBArray(camera, size=(853, 480))
 
for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
        image = frame.array
 
        name = "frame.jpg"
        cv2.imwrite(name, image,[cv2.IMWRITE_JPEG_QUALITY, 50])

        rawCapture.truncate(0)
                
cv2.destroyAllWindows()
cap.release()
