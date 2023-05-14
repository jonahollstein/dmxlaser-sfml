
import serial
import time


 
s = serial.Serial('/dev/ttyS0', 115200) # Namen ggf. anpassen
s.close()
s.open()
# time.sleep(5) # der Arduino resettet nach einer Seriellen Verbindung, daher muss kurz gewartet werden
 

 
while 1:
    
    x = s.read()
    x = int.from_bytes(x, "big")
    # if x > 0:
    print(x)
    
