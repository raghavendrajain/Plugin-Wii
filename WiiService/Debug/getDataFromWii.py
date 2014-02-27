#! /usr/bin/python

'''Try to implement the example in python'''

import wiiuse

import sys
import time
import os




nmotes = 2
wiimotes = wiiuse.init(nmotes)
rollAngle=[]

def handle_event(wmp):
    wm = wmp[0]
    #print '--- EVENT [wiimote id %i] ---' % wm.unid
    
    if wm.btns:
        for name, b in wiiuse.button.items():
            if wiiuse.is_pressed(wm, b):
                print name,'pressed'

        if wiiuse.is_just_pressed(wm, wiiuse.button['-']):
            wiiuse.motion_sensing(wmp, 0)
        if wiiuse.is_just_pressed(wm, wiiuse.button['+']):
            wiiuse.motion_sensing(wmp, 1)
        if wiiuse.is_just_pressed(wm, wiiuse.button['B']):
            wiiuse.toggle_rumble(wmp)         
        if wiiuse.is_just_pressed(wm, wiiuse.button['Up']):
            wiiuse.set_ir(wmp, 1)
        if wiiuse.is_just_pressed(wm, wiiuse.button['Down']):
            wiiuse.set_ir(wmp, 0)
    
    if wiiuse.using_acc(wm):
        
        print 'roll  = %f' % wm.orient.roll
        print 'pitch = %f' % wm.orient.pitch
        print 'yaw   = %f' % wm.orient.yaw
        print 'x_acc = %f' % wm.gforce.x
        print 'y_acc = %f' % wm.gforce.y
        print 'z_acc = %f' % wm.gforce.z

        
    
  
def handle_ctrl_status(wmp, attachment, speaker, ir, led, battery_level):
    wm = wmp[0]
    print '--- Controller Status [wiimote id %i] ---' % wm.unid
    print 'attachment', attachment
    print 'speaker', speaker
    print 'ir', ir
    print 'leds', led[0], led[1], led[2], led[3]
    print 'battery', battery_level

def handle_disconnect(wmp):
    print 'disconnect'



def getConnected():
    #global wiimotes
    #wiimotes = wiiuse.init(nmotes)
    found = wiiuse.find(wiimotes, nmotes, 5)
    if not found:
        print 'not found'
        sys.exit(1)
    connected = wiiuse.connect(wiimotes, nmotes)
    if connected:
        print 'Connected to %i wiimotes (of %i found).' % (connected, found)
    else:
        print 'failed to connect to any wiimote.'
        sys.exit(1)

    for i in range(nmotes):
        wiiuse.set_leds(wiimotes[i], wiiuse.LED[i])
        wiiuse.status(wiimotes[0])
        wiiuse.set_ir(wiimotes[0], 1)
        wiiuse.set_ir_vres(wiimotes[i], 1000, 1000)
    

def getData():
    getConnected()
    try:
        rum=1
        while True:
            r=wiiuse.poll(wiimotes, nmotes)
            print r
            if r!=0:
                a=handle_event(wiimotes[0])
                print a 

    except KeyboardInterrupt:
        for i in range(nmotes):
            wiiuse.disconnect(wiimotes[i])
            


def getDataOnlyOnce():
    getConnected()
    while True:
        r=wiiuse.poll(wiimotes, nmotes)
        if r!=0:
            a=handle_event(wiimotes[0])
            print a           


def withYield():
    getConnected()
    while True:
        r = wiiuse.poll(wiimotes, nmotes)
        if r != 0:
            wmp=wiimotes[0]
            wm=wmp[0]
          
            if wm.btns:
                for name, b in wiiuse.button.items():
                    if wiiuse.is_pressed(wm, b):
                        print name,'pressed'
                if wiiuse.is_just_pressed(wm, wiiuse.button['-']):
                    wiiuse.motion_sensing(wmp, 0)
                if wiiuse.is_just_pressed(wm, wiiuse.button['+']):
                        wiiuse.motion_sensing(wmp, 1)
                if wiiuse.is_just_pressed(wm, wiiuse.button['B']):
                    wiiuse.toggle_rumble(wmp) 
            if wiiuse.using_acc(wm):
                #global rollAngle
                global completeList
                #rollAngle=[wm.orient.roll]
                completeList=[wm.orient.roll, wm.orient.pitch, wm.orient.yaw, wm.gforce.x, wm.gforce.y, wm.gforce.z ]
                #yield rollAngle
                yield completeList
                #print rollAngle


                  
                  
if __name__ == "__main__" :


    found = wiiuse.find(wiimotes, nmotes, 5)
    if not found:
        print 'not found'
        sys.exit(1)
    connected = wiiuse.connect(wiimotes, nmotes)
    if connected:
        print 'Connected to %i wiimotes (of %i found).' % (connected, found)
    else:
        print 'failed to connect to any wiimote.'
        sys.exit(1)

    for i in range(nmotes):
        wiiuse.set_leds(wiimotes[i], wiiuse.LED[i])
        wiiuse.status(wiimotes[0])
        wiiuse.set_ir(wiimotes[0], 1)
        wiiuse.set_ir_vres(wiimotes[i], 1000, 1000)

    try:
        rum = 1
        while True:
            r = wiiuse.poll(wiimotes, nmotes)
            if r != 0:
                handle_event(wiimotes[0])
    except KeyboardInterrupt:
        for i in range(nmotes):
            wiiuse.set_leds(wiimotes[i], 0)
            wiiuse.rumble(wiimotes[i], 0)
            wiiuse.disconnect(wiimotes[i])

    print 'done'

