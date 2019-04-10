from serial import Serial
from time import sleep
from datetime import datetime
from envimon_common import is_number

DEBUG = False  # Enable debug breaks
CONSOLE = True  # Enable console output

ser = Serial("COM3", 115200)  # timeout=10 may be causing issues
ser.flushInput()
print("Ready")

while True:
    try:
        cc = ''

        if len(cc) != 6:
            ser.flushInput()
            ser_bytes = ser.readline()
            decode_bytes = ser_bytes[0:len(ser_bytes) - 2].decode("utf-8")
            cc = decode_bytes.split()

        for i in range(len(cc)):
            if is_number(cc[i]) is False:
                print(cc[i])
                cc[i] = "NaN"

        if CONSOLE is True:
            print(str(datetime.now()) + ': ', end='')  # end='' replaces newline with nul
            print(cc)

        # TODO  Change this to use a temp file, then replace existing (avoid read while file being written)
        # TODO  Also, change to a platform-agnostic path
        f = open("C:\\Program Files\\wmi_exporter\\textfile_inputs\\aquarium.prom", "w+")
        f.write("aq_visible_light %s\n" % (cc[0]))  # SI1145.ReadVisible
        f.write("aq_ir_light %s\n" % (cc[1]))       # SI1145.ReadIR
        f.write("aq_uv_light %s\n" % (cc[2]))       # SI1145.ReadUV
        f.write("aq_water_temp %s\n" % (cc[3]))     # getTempCByIndex
        f.write("aq_humidity %s\n" % (cc[4]))       # humidity
        f.write("aq_a_temp %s\n" % (cc[5]))
        f.close()

        if DEBUG:
            ser.close()
            break

        # TODO  Sample data every second for 15 seconds, average it, then write to file
        sleep(15)

    except Exception as e:
        print("Oops!")
        print(e)
        ser.close()
        break
