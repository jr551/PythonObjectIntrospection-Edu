#
# This is a test script for use within 
# the Object Introspection Demo.
#



class Person:
    def __init__(self, name, age):
        self.name = name
        self.age = age
    def sayHiToSelf(self):
        print 'hello ' + self.name
    def doubleMyAge(self):
        print (self.age*2)
    def getName(self):
        return self.name
    def lookAtCake(self,cake):
        print "the cake is " + cake.getColour()

class Cake:
    def __init__(self):
        self.colour = "white"
    def getColour(self):
        return self.colour
    def setColour(self, colour):
        self.colour = colour

class Calculator:
    def __init__(self):
        pass
    def add(self, x, y):
        return x+y
    def times(self, x, y):
        return x*y
    def padd(self, x, y):
        print x+y
    def ptimes(self, x, y):
        print x*y

import wx
class WindowTest:
    def __init__(self):
        self.win = wx.Frame(None, title="Hello World", size=(300,200))
    def show(self):
        self.win.Show()
    def hide(self):
        self.win.Hide()
    def setTitle(self, title):
        self.win.SetTitle(title)
