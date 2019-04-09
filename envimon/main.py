from serial import Serial
from time import sleep
from datetime import datetime

DEBUG_ENABLE = True

ser = Serial("COM3", 9600, timeout=10)
ser.flushInput()
# sleep(10)  # Wait for serial link

while True:
    # Change this to use a temp file, then replace existing
    f = open("C:\\Program Files\\wmi_exporter\\textfile_inputs\\aquarium.prom", "w+")
    ser_bytes = ser.readline()
    decode_bytes = ser_bytes[0:len(ser_bytes)-2].decode("utf-8")
    cc = decode_bytes.split()

    if DEBUG_ENABLE is True:
        print(str(datetime.now()) + ': ', end='')  # end='' replaces newline with nul
        print(cc)

    # try:
    #for i in range(len(cc)):
    #    if cc[i] is None:
    #        cc.insert(i, 'NaN')
    #        if DEBUG_ENABLE is True:
    #            print(cc, i, cc[i])

    f.write("aq_visible_light %s\n" % (cc[0]))  # SI1145.ReadVisible
    f.write("aq_ir_light %s\n" % (cc[1]))       # SI1145.ReadIR
    f.write("aq_uv_light %s\n" % (cc[2]))       # SI1145.ReadUV
    f.write("aq_water_temp %s\n" % (cc[3]))     # getTempCByIndex
    f.write("aq_humidity %s\n" % (cc[4]))       # humidity
    f.write("aq_a_temp %s\n" % (cc[5]))

    f.close()
    sleep(15)
    # except Exception as e:
    #    print("oops")
    #    print(e.__doc__)
    #    print(e)
