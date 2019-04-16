#Imports
import sys
import os
import cv2

sys.path.insert(0, './scripts/')
import recognition as recog

"""
Trained Stop Sign classifier taken from:
https://github.com/cfizette/road-sign-cascades
"""
stopSignCascadePath = "%s/classifiers/Stopsign_HAAR_19Stages.xml"%(os.getcwd())

#Main PI loop
def main():
    print(stopSignCascadePath)
    #Load classifiers
    stopSignCascade = cv2.CascadeClassifier(stopSignCascadePath)
    """
        Video loop logic taken from OpenCV offical documentation 
        https://docs.opencv.org/3.4/dd/d43/tutorial_py_video_display.html
    """
    cap = cv2.VideoCapture(0)
    while True:
        ret, frame = cap.read()

        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        """
        Run stop sign detection as test
        """
        recog.isStopSignDetected(stopSignCascade,gray)
        cv2.imshow('frame',gray)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cap.release()
    cv2.destroyAllWindows()

    #Intersection mode
        #detect and register streets signs
        #await given direction
            #if given direction not allowed by streets signs
                #refuse
        #Count cars
        #Roll up to stop line
        #while count cars > 0 
            #if car detected passing by
                # Count cars --
        #move / turn in given direction
        #enter standby mode

    #Follow car mode
        #if isCarRecognised()
                #if Stopsign recognised
                    #register stop sign 
                #if stop sign registered && car not moving
                    #enter Intersection mode
        #else
            #stop moving
        
if __name__ == '__main__':
    main()