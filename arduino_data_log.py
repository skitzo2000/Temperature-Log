#!/usr/bin/env python

import serial 
import MySQLdb
import os
from time import sleep      
#establish connection to MySQL. You'll have to change this for your database.
dbConn = MySQLdb.connect("localhost","YourUser","YourPassword","YourDBName") or die ("could not connect to database")
#open a cursor to the database
device = '/dev/ttyUSB0' #this will have to be changed to the serial port you are using
try:
	#print "Trying...",device 
	arduino = serial.Serial(device, 9600, timeout = 5)
except:
	print "Failed to connect on",device
while True:
	try:
		arduino.write("1")
		data = arduino.readline()
		#arduino.close()
		pieces = data.split("\t")
		if pieces[0] != "85.00" and pieces[1] != "85.00" and pieces[2] != "85.00":
			try:
				cursor = dbConn.cursor()
				#You Will need to change YourTable to Match your database
				cursor.execute("INSERT INTO YourTable (ambient, fermenter1, fermenter2) VALUES (%s,%s,%s)", (pieces[0], pieces[1], pieces[2]))
				dbConn.commit()
				cursor.close()
				sleep(60)
			except MySQLdb.IntegrityError:
				print "failed to insert data"
				sleep(30)
			finally:
				cursor.close()
		#Hack to throw out device read errors
		if pieces[0] == "85.00" or pieces[1] == "85.00" or pieces[2] == "85.00":
			print "Resetting USB Device /001/010 " #this will have to be changed to the serial port you are using
			os.system("/root/./usbreset /dev/bus/usb/001/010") #this will have to be changed to the serial port you are using
			sleep(60)
	except:
		print "Failed to get data from Arduino!"
		sleep(10)
		