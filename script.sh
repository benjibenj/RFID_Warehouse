#!/bin/bash

for i in `seq 1 10`;
do
  sshpass -p 'raspberry' ssh pi@10.3.141.1 '
  echo "Connect to RPi3 ..."
  cd /home/pi/Desktop/
  echo "Access to /home/pi/Desktop/"
  echo '' >> Detected_products.txt
  echo "Detected_products.txt created"
  chmod 777 Detected_products.txt
  echo "Rights for Detected_products.txt modified"
  echo "Lunching Serial.py"
  python3 Serial.py
  echo "End of Serial.py"
  exit
  '


  echo 'Copying file Detected_products.txt'
  sshpass -p 'raspberry' scp pi@10.3.141.1:/home/pi/Desktop/Detected_products.txt /Users/User/Desktop
  echo 'Detected_products.txt copied in /Desktop'
done
