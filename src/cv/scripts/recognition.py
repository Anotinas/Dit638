import numpy as np
import cv2

#Returns a list of objects detected that match the classifier
def getObjectsFromFrame(cascade,grayScale):
    #Collect all recognised objects from frame
    objectsDetected = cascade.detectMultiScale(grayScale, scaleFactor=10, minNeighbors=1, minSize=(1,1))
    return objectsDetected

def isStopSignDetected(cascade,image):
    stopSigns = getObjectsFromFrame(cascade,image)
    if(len(stopSigns)>0):
        print("Stop sign detected!")

def numCarsDetected(cascade,image):
    cars = getObjectsFromFrame(cascade,image)
    if(len(cars)>1):
        print("That's a car babby!")