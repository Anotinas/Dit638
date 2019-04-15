import numpy as np
import cv2

#Returns a list of objects detected that match the classifier
def getObjectsFromFrame(cascadePath, image):
    #Read image with OpenCV
    image = cv2.imread(image)
    #Create grayscale of image
    grayScale = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    #Load given classifier
    cascade = cv2.CascadeClassifier(cascadePath)
    #Collect all recognised objects from frame
    objectsDetected = cascade.detectMultiScale(grayScale, scaleFactor=1.1, minNeighbors=1, minSize=(1,1))
    return objectsDetected