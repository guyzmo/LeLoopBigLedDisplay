#!/usr/bin/env python
#this code is WTFPL, please reuse it, improve it and share it as much as you like and pay me a beer !
#(c)2011 guyzmo at leloop dot org
#
# NOT TESTED ON THE WILD !!!

import sys, serial, fcntl, os


def send_to_serial(serial, baudrate, infile):
    fd = sys.stdin.fileno()
    fl = fcntl.fcntl(fd, fcntl.F_GETFL)
    fcntl.fcntl(fd, fcntl.F_SETFL, fl | os.O_NONBLOCK)

    with serial.Serial(serial, baudrate) as ser:
        print ser.readline()

        # set binary mode
        ser.write(bytearray([27,'0']))
        print ser.readline()
        ser.flush()

    for pixel in matrix_adapt(infile):
        ser.write(pixel)
        print ser.read()
        ser.flush()

def clumper(s, count=4):
    """http://stackoverflow.com/questions/5676302/taking-four-items-instead-of-on-in-a-for-loop"""
    for x in range(0, len(s), count):
        yield s[x:x+count]

def matrix_adapt(file):
    with open(file,'r') as infile:
        lines = infile.readlines()
        dotmat = []

        for disp in clumper(lines,8*96):
            disp.reverse()
            for cols in clumper(disp,8):
                cols.reverse()
                for col in zip(*cols):
                    for pixel in col:
                        if pixel == '\n':
                            continue
                        if pixel == ' ' or pixel == '0':
                            dotmat += [0]
                        else:
                            dotmat += [1]
        dotmat.reverse()
        return dotmat

def write_to_screen(serial,pixels):
    for pix in matrix_adapt(sys.argv[1]):
        print pix,


if __name__ == '__main__':
    if len(sys.argv) != 4:
        print "Usage: bitmap2screen /dev/ttyUSB0 9600 file.bitmap"
        exit(1)

    init_serial(sys.argv[1],sys.argv[2],sys.argv[3])
