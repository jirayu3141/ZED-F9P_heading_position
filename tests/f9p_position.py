
# imports for f9p outputs
import struct
import serial
from serial.tools.list_ports import comports
from ubx import UBXManager
from itertools import count

# imports for lat-long to xyz
import pyproj
import math

# imports for plots
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation


x_vals = []
y_vals = []
heading_err = []
index = count()
gps_x = []
gps_y = []


print('\n--- Select ZED_F9P for position:\n')
# Show a list of ports and ask the user for a choice.
def ask_for_port():
    """\
    Show a list of ports and ask the user for a choice. Ask for user input
    """

    try:
        raw_input
    except NameError:
        raw_input = input

    
    ports = []
    for n, (port, desc, hwid) in enumerate(sorted(comports()), 1):
        print('--- {:2}: {:20} {!r}\n'.format(n, port, desc))
        ports.append(port)
    while True:
        port = raw_input('--- Enter port index or full name: ')
        try:
            index = int(port) - 1
            if not 0 <= index < len(ports):
                sys.stderr.write('--- Invalid index!\n')
                continue
        except ValueError:
            pass
        else:
            port = ports[index]
        return port


# set up conversion of lat-long to xyz
P = pyproj.Proj(proj='utm', zone=31, ellps='WGS84', preserve_units=True)
G = pyproj.Geod(ellps='WGS84')


def latlong_to_xy(lat, lon):
    return P(lon, lat)


def XY_To_LatLon(x, y):
    return P(x, y, inverse=True)


def distance(lat1, lon1, lat2, lon2):
    return G.inv(lon1, lat1, lon2, lat2)[2]


print(latlong_to_xy(2.3522219, 48.856614))

# %%
# modified call back function to only print GNRMC message


def nmea_cb(msg):
    # positional message
    if (msg.startswith("GNRMC,")):
        nmea_lat = msg.split(',')[3]
        nmea_long = msg.split(',')[5]

        # convert from nmea lat long to real lat long
        real_lat = (float(nmea_lat[0:2]) + float(nmea_lat[2:])/60)
        real_long = (float(nmea_long[0:3]) + float(nmea_long[3:])/60)

        real_x, real_y = (latlong_to_xy(real_lat, real_long)
                          )  # convert lat-long to xy

        # record the values to the list
        gps_x.append(real_x)
        gps_y.append(real_y)

        print("x: %s y:%s \t" % (real_x, real_y))

    # error message
    if (msg.startswith("GNGST,")):
        error = float(msg.split(',')[3])
        fix = float(msg.split(',')[2])
        print("error: %f fix: %f" % (error, fix))

        # print("lat:%s long:%s  x: %f y:%f" % (real_lat, real_long, real_x, real_y))


def ubx_cb(msg):
    None


# show output form f9p
ser = serial.Serial(ask_for_port())
manager = UBXManager(ser, debug=True)
manager.onUBX = ubx_cb
manager.onNMEA = nmea_cb
manager.start()

# %%
# animate plot
plt.style.use('fivethirtyeight')


def animate(i):
    global gps_x, gps_y
    plt.cla()

    # ax.grid(True)
    # ax.spines['left'].set_position('zero')
    # ax.spines['right'].set_color('none')
    # ax.spines['bottom'].set_position('zero')
    # ax.spines['top'].set_color('none')

    plt.xlim(gps_x[-1]-1, gps_x[-1]+1)
    plt.ylim(gps_y[-1]-1, gps_y[-1]+1)
    gps_x = gps_x[-100:]
    gps_y = gps_y[-100:]
    plt.scatter(gps_x[-100:], gps_y[-100:])


# run animate every n sec
ani = FuncAnimation(plt.gcf(), animate, interval=500)

plt.show()


# %%
