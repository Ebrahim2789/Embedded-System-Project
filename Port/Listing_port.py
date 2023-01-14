import serial
import time
import win32clipboard as cp

device ='COM3'
cp.OpenClipboard()
cp.EmptyClipboard()
cp.SetClipboardText('text')
time.sleep(5)
cp.CloseClipboard()
cp.OpenClipboard()
data=cp.GetClipboardData()
cp.CloseClipboard()

print(data)
try:
	print("trying to ..")
	arduino=serial.Serial( 9600)
	
	
except:
	print("fiald toconnect")
try:
	time.sleep(5)
	data=arduino.readline()
	print(data)
except:
	print("faildbto read")


	


