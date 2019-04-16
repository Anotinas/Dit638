import numpy as np
import cv2
import os

POSTITIVE="Positive_Pictures"

def makePicsGrey():
    for i in glob.glob("*.jpg"):
        try:
            print(i)
            img = cv2.imread(i,cv2.IMREAD_GRAYSCALE)
            cv2.imwrite(i, img)
        except Exception as e:
            print(str(e))

if __name__ == '__main__':
    makePicsGrey()

    