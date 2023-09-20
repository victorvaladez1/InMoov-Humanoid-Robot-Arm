import cvzone
from cvzone.SerialModule import SerialObject
from cvzone.HandTrackingModule import HandDetector
import cv2

cap = cv2.VideoCapture(0)
detector = HandDetector(detectionCon=0.8,maxHands=1)
mySerial = SerialObject("COM4",9600,1)
while True:
    success, img = cap.read()
    hands,img = detector.findHands(img)

    if hands:
        hand1 = hands[0]
        lmList1 = hand1["lmList"]
        bbox1 = hand1["bbox"]
        centerPoint1 = hand1["center"]
        handType1 = hand1["type"]

        fingers1 = detector.fingersUp(hand1)

        mySerial.sendData(fingers1)


    cv2.imshow("Image", img)
    cv2.waitKey(1)