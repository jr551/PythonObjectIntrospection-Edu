import wx 
from IntrospectionTools import *
from WindowGetParams import WindowGetParams 
from WindowObjectInspector import WindowObjectInspector 

class ObjectMenu(wx.Menu):
    def setIObject(self, obj):
        self.iObj = obj
    def getIObject(self):
        return self.iObj

class ObjectPanel(wx.Panel):
    def load(self):
        self.objects = []
    def getObjectNames(self):
        names = []
        for o in self.objects:
            names.append( o.getObjectName() )
        return names
    def amountOfObjects(self):
        return len(self.objects)
    def findObjectByName(self, name):
        for o in self.objects:
            if o.getObjectName() == name:
                return o
        return None

    def addObject(self, iObj):
        self.objects.append(iObj)
        l = wx.Button(self, len(self.objects)-1, iObj.getObjectName() + "\n" + iObj.getObjectTypeName())
        l.SetForegroundColour(wx.Colour(255, 255, 255))
        l.SetBackgroundColour(wx.Colour(100, 150, 255))
        l.SetPosition(wx.Point(20,60*len(self.objects)))
        l.SetSize(wx.Size(90,50))
        l.Bind(wx.EVT_BUTTON, self.showMenu)
    def removeObject( self, object ):
        pass
    def showMenu( self, event ):
        obj = self.objects[event.GetId()]
        menu = ObjectMenu()
        menu.setIObject(obj)
        menu.Append( -1, "Inspect Object" )
        wx.EVT_MENU( menu, -1, self.menuSelInspector )
        i = 0
        for method in obj.getObjectAttribs(True,False):
            menu.Append( i, method )
            wx.EVT_MENU( menu, i, self.menuSel )
            i = i + 1
        self.PopupMenu( menu, event.EventObject.GetPosition() + wx.Point(0,40) )
        menu.Destroy()
    def menuSelInspector( self, event ):
        objectHandler = event.GetEventObject().getIObject()
        frm = WindowObjectInspector(objectHandler, None, -1, "")
        frm.Show()
    def menuSel( self, event ):
        objectHandler = event.GetEventObject().getIObject()

        method = objectHandler.getObjectAttribs(True,False)[event.GetId()]
        params = objectHandler.getMethodParams(method)

        wx.GetApp().LogMessage('Calling method "' + method + '" on object "' + objectHandler.getObjectName() + '"')

        if len( params ) == 0:
            r = objectHandler.callMethod(method, [])
            if r != None:
                dia = wx.MessageDialog(self, 'Function returned value: ('+ str(r) + ')', 'Function returned value', wx.OK)
                dia.ShowModal()
            return
        dlg = WindowGetParams(params, None, -1, "")
        if dlg.ShowModal() == 1:
            try:
                r = objectHandler.callMethod(method, dlg.getParams())
                if r != None:
                    dia = wx.MessageDialog(self, 'Function returned value: ('+ str(r) + ')', 'Function returned value', wx.OK)
                    dia.ShowModal()
            except Exception, err:
                dia = wx.MessageDialog(self, str(err), 'Error encounted in method call!', wx.OK)
                dia.ShowModal()
        dlg.Destroy()
