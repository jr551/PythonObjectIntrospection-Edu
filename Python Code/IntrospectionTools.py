import wx, shutil, os

def getOpenScriptScope():
    file = wx.GetApp().GetOpenFile()
    if os.path.exists("_openscript.py"):
        os.remove("_openscript.py")
    shutil.copy2(file, '_openscript.py')
    return __import__('_openscript')

def isClass( typ ):
    return (typ.find('class') != -1)

def getScriptClasses(scope):
    exclusions = ['__builtins__', '__doc__', '__name__', '__package__', '__file__', '__module__']
    found = dir(scope)
    items = []
    for item in found:
        if item in exclusions: continue
        objItem = getattr(scope,item)
        if isClass(str(type(objItem))):
            items.append(item)
    return items

def getConstructorParams(className):
    scope = getOpenScriptScope()
    x = getattr(scope, className)
    method = getattr(x, '__init__')
    items = list(method.func_code.co_varnames[0:method.func_code.co_argcount])
    items.remove('self')
    return items

def constructObjectDynamic(className, listParams):
    from _openscript import * 
    st = ""
    for p in listParams:
        if isinstance(p, str):
            st = st + "'" + str(p) + "' ,"
        else:
            st = st + str(p) + " ,"
    st = st[:-1] #(Remove last comma)
    return eval( className + "(" + st + ")" )


class IntrospectionObject:
    def __init__(self, objectName, objectType, objectPointer):
        self.objectName = objectName
        self.objectType = objectType
        self.objectPointer = objectPointer
    def getObject(self):
        return self.objectPointer
    def getObjectName(self):
        return self.objectName
    def getObjectTypeName(self):
        return self.objectType
    def getObjectID(self):
        return id(self.objectPointer)
    def getObjectAttribs(self, showMethods, showNonMethods):
        ignore_methods = ['__init__','__builtins__', '__doc__', '__name__', '__package__', '__file__', '__module__']
        methods = dir(self.objectPointer)
        methodsToReturn = []
        for method in methods:
            if method in ignore_methods: continue
            if showMethods and ('__call__' in dir(getattr(self.objectPointer, method))): methodsToReturn.append(method)
            if showNonMethods and not ('__call__' in dir(getattr(self.objectPointer, method))): methodsToReturn.append(method)
        return methodsToReturn
    def getMethodParams(self, methodName):
        method = getattr(self.objectPointer, methodName)
        items = list(method.func_code.co_varnames[0:method.func_code.co_argcount])
        items.remove('self')
        return items
    def callMethod(self, methodName, listParams):
        f = getattr( self.objectPointer, methodName )
        return f(*listParams)
