
**Note**: This project was originally developed as a university assignment and has been preserved for educational purposes.




# Python Object Introspection Project

A comprehensive demonstration of Python object introspection capabilities using both embedded Python interpreters and GUI-based inspection tools. This project showcases runtime analysis of Python objects, classes, and their attributes through multiple interfaces.

## 🎯 Project Overview

This project implements Python object introspection - the ability to examine and analyze Python objects at runtime. It provides two main approaches:

1. **Text-based introspection** using C++ with embedded Python interpreter
2. **GUI-based introspection** using Qt framework with Python integration

## 🏗️ Architecture

### Components

- **C++ Text Interface**: Command-line tool for introspecting Python objects
- **Qt GUI Application**: Visual interface for object exploration
- **Python Tools**: Core introspection utilities and demo classes
- **Demo Scripts**: Example Python classes for testing introspection features

### Key Features

- **Class Discovery**: Automatically find all classes in a Python module
- **Attribute Analysis**: Distinguish between methods and data attributes
- **Parameter Inspection**: Extract method signatures and parameter lists
- **Object Instantiation**: Dynamically create objects from discovered classes
- **Method Invocation**: Call methods with runtime-discovered parameters

## 📁 Project Structure

```
├── C++ Code/
│   ├── QT introspection example/     # Qt-based GUI application
│   └── Text Based introspection example/  # Command-line C++ tool
├── Python Code/
│   ├── IntrospectionTools.py        # Core introspection utilities
│   ├── ObjectPanel.py              # GUI components
│   ├── WindowObjectInspector.py    # Main GUI application
│   └── [other Python modules]
├── Windows Executable of Project/   # Pre-built executables
├── LICENSE                          # MIT License
└── README.md                       # This file
```

## 🚀 Getting Started

### Prerequisites

- **Python 2.7** (for compatibility with the original project)
- **C++ Compiler** with C++11 support
- **Qt 4.x or 5.x** (for GUI version)
- **Python Development Headers** (python-dev package)

### Building the Text-Based Version

```bash
cd "C++ Code/Text Based introspection example/"
# Compile with appropriate flags for Python embedding
g++ main.cpp -o PyIntrospection -I/usr/include/python2.7 -lpython2.7
```

### Building the Qt Version

```bash
cd "C++ Code/QT introspection example/PythonIntrospection/"
qmake PythonIntrospection.pro
make
```

### Running the Python GUI

```bash
cd "Python Code/"
python WindowObjectInspector.py
```

## 🎓 Educational Value

This project demonstrates several important concepts:

- **Python C API**: How to embed Python in C++ applications
- **Runtime Reflection**: Object introspection and dynamic analysis
- **Cross-language Integration**: C++/Python interoperability
- **GUI Development**: Qt framework usage with Python integration
- **Software Architecture**: Modular design for extensibility

## 🔧 Usage Examples

### Text-based Introspection

```bash
# Run the C++ executable
./PyIntrospection

# Output will show all classes and their attributes
(DemoClass) 
* (Function: Hello ) 
     Arguments:
     [*] self
* (Function: Say ) 
     Arguments:
     [*] self
     [*] msg
```

### Python API Usage

```python
from IntrospectionTools import *

# Get all classes from a module
scope = getOpenScriptScope()
classes = getScriptClasses(scope)

# Inspect a specific class
params = getConstructorParams("DemoClass")

# Create an instance dynamically
instance = constructObjectDynamic("DemoClass", ["param1", 42])
```

## 📊 Demo Classes

The project includes several demo classes for testing:

- **DemoClass**: Basic class with methods and attributes
- **Cake**: Simple class with properties
- **Calculator**: Mathematical operations
- **WindowTest**: wxPython GUI components

## 🔍 Technical Details

### Introspection Process

1. **Module Loading**: Python modules are dynamically imported
2. **Class Discovery**: `dir()` and `type()` functions identify classes
3. **Attribute Analysis**: Each attribute is classified as method or data
4. **Signature Extraction**: Method parameters extracted from `func_code.co_varnames`
5. **Dynamic Execution**: Objects instantiated and methods called via `eval()`

### File Dependencies

- **demo_john.py**: Primary demo class definitions
- **_openscript.py**: Temporary copy of target script for introspection
- **Python libraries**: Standard library modules for GUI and system operations

## 🛠️ Development Notes

- Originally developed as a university project at University of Portsmouth
- Compatible with Python 2.7 (legacy support)
- Uses wxPython for GUI components
- Cross-platform support (Windows, Linux)

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🤝 Contributing

This is a legacy educational project. Contributions are welcome for:
- Python 3 compatibility updates
- Modern C++ improvements
- Additional introspection features
- Documentation enhancements

## 🐛 Known Issues

- Python 2.7 compatibility (legacy)
- Hard-coded file paths in some configurations
- Limited error handling in demo implementations

---
