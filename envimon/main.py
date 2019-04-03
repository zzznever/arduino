from serial import Serial
from logger_settings import api_logger

ser = Serial("COM3", 9600)

#logging.basicConfig(filename="logfilename.log", level=logging.INFO)

while True:
    # SI1145.ReadVisible , SI1145.ReadIR, SI1145.ReadUV, getTempCByIndex, humidity
    cc = str(ser.readline())
    # print(cc[2:][:-5])
    cc = cc[2:][:-5]
    cc = cc.split()
    print(cc)
 #   api_logger('test')
