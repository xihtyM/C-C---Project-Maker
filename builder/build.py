COMPILER = "g++"
MAIN_FILE = "\"main.cc\""
import os

def build_project(name: str):
    command = COMPILER + " -o %s.exe -O2 -s " % name

    for entry in os.scandir("impl"):
        if not entry.is_file() or not entry.name.endswith((".cc", ".c", ".cpp")):
            continue
        
        command += "\"%s\" " % entry.path
    
    command += MAIN_FILE
    
    os.system(command)

build_project("builder")
