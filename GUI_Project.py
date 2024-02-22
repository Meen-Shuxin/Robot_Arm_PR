#!/usr/bin/env python3

import rospy
from sensor_msgs.msg import JointState
from std_msgs.msg import UInt16
import tkinter as tk
from tkinter import ttk

# เริ่มต้นการใช้งาน ROS node
rospy.init_node('GUI_Control')
pub = rospy.Publisher("joint_states", JointState, queue_size=10)
pub2 = rospy.Publisher("encoder_cmd1", UInt16, queue_size=10)
pub3 = rospy.Publisher("encoder_cmd2", UInt16, queue_size=10)
switch_pub = rospy.Publisher('mode', UInt16, queue_size=10)

msg = JointState()
msg.name = ['joint2', 'joint3']  # ชื่อ joints ควรตรงกับจำนวนและชื่อในระบบของคุณ
msg.position = [0, 0]  # กำหนดค่าเริ่มต้นสำหรับตำแหน่งของทั้งสอง joints

def on_slider_change(event):
    value = int(slider.get())
    label.config(text=f"Joint 2 : {value}")
    msg.position[0] = value / 180.0 * 3.14159  # แปลงเป็นเรเดียนสำหรับ ROS
    msg.header.stamp = rospy.Time.now()
    pub.publish(msg)
    pub2.publish(UInt16(value))

def on_slider_change2(event):
    value = int(slider2.get())
    label2.config(text=f"Joint 3 : {value}")
    msg.position[1] = value / 180.0 * 3.14159
    msg.header.stamp = rospy.Time.now()
    pub.publish(msg)
    pub3.publish(UInt16(value))
    
def talker(val):
    cmd_val = UInt16(val)
    rospy.loginfo(cmd_val)
    switch_pub.publish(cmd_val)


root = tk.Tk()
root.title("Robotic Arm Control Panel")
root.geometry("750x200")
root.configure(bg="lightblue")

frame = ttk.Frame(root, padding=20, borderwidth=2, relief="groove")
frame.grid(row=0, column=0, padx=10, pady=10, sticky="nsew")

slider = ttk.Scale(frame, from_=0, to=180, orient="horizontal", command=on_slider_change, length=300)
slider.grid(row=0, column=0, padx=10, pady=10)
slider.set(90)

label = ttk.Label(frame, text="Joint 2 : 90")
label.grid(row=1, column=0, padx=10, pady=5)

slider2 = ttk.Scale(frame, from_=0, to=180, orient="horizontal", command=on_slider_change2, length=300)
slider2.grid(row=0, column=1, padx=10, pady=10)
slider2.set(90)

label2 = ttk.Label(frame, text="Joint 3 : 90")
label2.grid(row=1, column=1, padx=10, pady=5)

B1 = ttk.Button(frame, text="ON", command=lambda: talker(1))
B1.grid(row=2, column=0, padx=10, pady=10)

B2 = ttk.Button(frame, text="OFF", command=lambda: talker(0))
B2.grid(row=2, column=1, padx=10, pady=10)

root.mainloop()
