from ctypes import c_char_p, windll
#from pywinstyles import *
from tkinter import Tk

from win32material import *


w = Tk()
w.title("example")
w.geometry("1080x570")
w.iconbitmap("")
w.config(background="black")

ApplyMica(windll.user32.GetParent(w.winfo_id()), True)

w.mainloop()