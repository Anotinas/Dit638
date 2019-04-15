import numpy as np
import cv2
import os

POSTITIVE="Positive_Pictures"

def makePicsGrey():
    global POSTITIVE
    if not os.path.exists(POSTITIVE):
        os.makedirs(POSTITIVE)
pic_num = 1

for i in os.listdir(POSTITIVE):
    try:
        print(i)
        img = cv2.imread(POSTITIVE+'\\'+i,cv2.IMREAD_GRAYSCALE)
        cv2.imwrite(POSTITIVE+'\\'+i, img)
        pic_num+=1
    except Exception as e:
        print(str(e))

#def processPositivePics():

#if __name__ == '__main__':
    #TODO

    