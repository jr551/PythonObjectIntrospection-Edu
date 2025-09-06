/*
	Python Object Introspection on an Embedded Interpreter
	Proof of Concept
	By John Rowe (University of Portsmouth)
*/


#include <iostream>
#include <Python.h> // Python include. Also we link the static library in the linker options.

using namespace std;

// This function decides weather a Python object is a function or not
// It checks by seeing if the item has the __call__ attribute
// If it does then it is a function.

bool Introspection_IsFunction( PyObject *pContext, PyObject* pItem )
{
    PyObject *pAttribute = PyObject_GetAttr(pContext, pItem);
    return (PyObject_HasAttrString(pAttribute, "__call__") == 1);
}

// This function takes a Python object which should be a method/function
// It then accesses the func_code.co_varnames attribute which will give
// us the function paramaters which it takes.
// It will output a list to the std::out (Standard output)

void Introspection_ListFunctionParams( PyObject *pContext, PyObject* pItem )
{
    PyObject *p1 = PyObject_GetAttr(pContext, pItem);
    PyObject *p2 = PyObject_GetAttrString(p1, "func_code");
    PyObject *p3 = PyObject_GetAttrString(p2, "co_varnames");

    int listSize = PyTuple_Size(p3);

    for (int i = 0; i < listSize; i++) {

        PyObject *item = PyTuple_GetItem(p3, i);
        char *sItem;
        PyArg_Parse( item, "s", &sItem );
        cout << "     [*] ";
        cout << sItem << endl;
    }

}

// This function takes a context (Python module) and a item name (Class name)
// It will scan the class showing all of the attributes, functions and function paramaters.

void Introspection_ListClassAttribs( PyObject *pContext, const char* sItem)
{
    PyObject *pAttribute = PyObject_GetAttrString(pContext, sItem); // Get pointer to actual class object
    PyObject *pAttributeList = PyObject_Dir(pAttribute); // Run a dir() operation on the class object

    int listSize = PyList_Size(pAttributeList);
    cout << "(" << sItem << ") \n";
    for (int i = 0; i < listSize; i++) { // Iterate the returned dir() operation

        PyObject *item = PyList_GetItem(pAttributeList, i);
        char *sItem;
        PyArg_Parse( item, "s", &sItem );
        if ( Introspection_IsFunction( pAttribute, item ) ) // If its a function list the arguments
        {
           cout << "* (Function: ";
           cout << sItem << " ) \n     Arguments:" << endl;
           Introspection_ListFunctionParams(pAttribute, item);
        }
        else
        {
            cout << "* (Non-Function: ";
            cout << sItem << " )" << endl;
        }
    }
}

// This is the entry point for the application
int main(int argc, char *argv[])
{
    Py_Initialize(); // Initalize the embedded interpreter
    PyObject *demoCodeModule = PyImport_ImportModule("demo_john"); // Import the demo_john.py script

    if (demoCodeModule == NULL) // If we are unable to locate the script end the program
    {
        printf("Can't load 'demo_john' module!");
        return 1;
    }
    Introspection_ListClassAttribs(demoCodeModule, "DemoClass"); // Call to list all information on the 
																 // DemoClass class within demo_john.
	Py_Finalize(); // Clean up and close everything.												 
    return 0;
}
