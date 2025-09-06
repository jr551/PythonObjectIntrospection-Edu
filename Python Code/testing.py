#
# This is a test script for use within 
# the Object Introspection Demo.
#

class VariableTest:
    def __init__(self, variable):
        self.variable = variable
    def GetVariable(self):
        return self.variable
    def PrintVariable(self):
        print self.variable
    def SetVariable(self, variable):
        self.variable = variable
    def InputVariableString(self):
        self.variable = raw_input("Input new variable (string): ")


class OtherObjectsTest:
    def __init__(self):
        pass
    def lookAtDummy(self, dummy):
        print "That dummy is " + dummy.GetColour() 

        
class DummyObject:
    def __init__(self, colour):
        self.colour = colour    
    def GetColour(self):
        return self.colour
    def SetColour(self, colour):
        self.colour = colour
       
        
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
