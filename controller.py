import serial

usbport = 'COM4'

# Set up serial baud rate
ser = serial.Serial(usbport, 9600, timeout=1)




if __name__ == '__main__':

    output = ser.write(b'KL_OFF')

    print(output)

    output = ser.read(20)
    print(output)