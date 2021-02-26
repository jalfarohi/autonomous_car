import smbus  
import time  
import sys  
bus = smbus.SMBus(1)  
address = 0x10              # Arduino I2C Address  

def main():    
    while 1:  
        # send data  
        bus.write_byte(address,1)  
        time.sleep(5)
        bus.write_byte(address,2)  
        time.sleep(5)
        bus.write_byte(address,3)  
        time.sleep(5)
        bus.write_byte(address,4)  
        time.sleep(5)
        bus.write_byte(address,5)  
        time.sleep(5)

if __name__ == '__main__':  
    try:  
        main()  
    except KeyboardInterrupt:  
        # gpio.cleanup()  
        sys.exit(0) 
