#!/usr/bin/env python
#this code is WTFPL, please reuse it, improve it and share it as much as you like and pay me a beer !
#(c)2011 guyzmo at leloop dot org

import sys, serial, fcntl, os


def clumper(s, count=4):
    """http://stackoverflow.com/questions/5676302/taking-four-items-instead-of-on-in-a-for-loop"""
    for x in range(0, len(s), count):
        yield s[x:x+count]

fd = sys.stdin.fileno()
fl = fcntl.fcntl(fd, fcntl.F_GETFL)
fcntl.fcntl(fd, fcntl.F_SETFL, fl | os.O_NONBLOCK)

if len(sys.argv) != 4:
    print "Usage: bitmap2screen /dev/ttyUSB0 9600 file.bitmap"
    exit(1)

with serial.Serial(sys.argv[1], baudrate = sys.argv[2]) as ser:
    print ser.readline()

    ser.write(bytearray([27,'0']))
    #ser.write('\x1b')
    #ser.write('0')
    print ser.readline()

    with open(sys.argv[3],'r') as infile:
        # TODO : transform the bitmap file so it is read the right way on screen

        lines = infile.readlines()

        # seperate all the displays, by iteratings 8 lines by 8 lines
        for disp in clumper(lines,8):
            # for each group of lines, get all the columns by zipping them
            for col in zip(*disp):
                # for each column, print the pixels
                for pixel in col:
                    ser.write(pixel)

        #for col in zip(*lines):
        #    for pixels in clumper(col,8):
        #        for pixel in pixels:
        #            ser.write(pixels[0])

        #for line in lines:
        #    for c in line:
        #        ser.write(c)
    ser.flush()

