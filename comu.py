import serial
import time

try:
	ser = serial.Serial('/dev/ttyACM0', 9600)
	time.sleep(2)
except:
	print ('No Arduino found')

while True:
	while True:		
		s = input("Value => ")
		ser.write(bytes(str(s),'utf-8'))
		#ser.write(s.encode('utf-8')):
		#ser.write(bytes(str(s)+'\n','utf-8'))
		#ser.write(bytes(str(s)+'\n','utf-8'))
		#print (ser.readline())
		#ser.write(b'B')
		time.sleep(2)
		print (ser.readline())
		
