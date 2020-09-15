import serial
from itertools import count
from ubx import UBXManager
from f9p_heading import ask_for_port

import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import itertools
import datetime  #import time for x-axis


x_vals = []
y_vals = []
heading_err = []
i = 1
index = count()


print('\n--- Select ZED_F9H for heading:')
def setup():
    # f9h : /dev/cu.usbmodem1442301
    ser = serial.Serial(ask_for_port())
    manager = UBXManager(ser, debug=True)
    manager.onUBX = ubx_cb
    manager.start()


def plot_heading():
    plt.style.use('dark_background')
    ani = FuncAnimation(plt.gcf(), animate, interval=125)
    
    
    plt.tight_layout()
    plt.show()


def animate(i):
    global x_vals
    global y_vals

    plt.cla()
    plt.ylabel('degree')
    plt.ylim(0,360)
    x_vals = x_vals[-50:]

    
    cm = plt.cm.get_cmap('RdYlGn')
    plt.scatter(x_vals[-50:], y_vals[-50:], c=heading_err[-50:], vmin=80, vmax=100, cmap=cm, s=10) #color scale is reversed
    plt.gcf().autofmt_xdate()
    # cbar = plt.colorbar(sc)
    # cbar.ax.set_ylabel('error', rotation=270)
    
def x_plot(str):
    if (str is 'iteration'):
        x_vals.append(next(index))

    if (str is 'time'):
        now = datetime.datetime.now()
        x_vals.append(now)

def ubx_cb(msg):
    heading_deg = msg.heading_deg
    heading_acc = msg.accHeading * 1e-5
    r_heading_acc = (abs(heading_acc-180)/180)*100 # revesed heading accuracty
    
    
    x_plot('time')  # choose between 'time' and 'iteration' to change x-axis in plot

    y_vals.append(heading_deg)
    heading_err.append(r_heading_acc)


    print("heading: {0:.2f} error: {1:.2f} normalised: {2:.2f}".format(heading_deg, heading_acc, r_heading_acc))

def f9h_main():
    setup()
    plot_heading()


if __name__ == "__main__":
    f9h_main()




