import os
import sys
import shutil

def run(module_path, global_path, args=None):
    path = os.path.dirname(module_path)
    shutil.copy(os.path.join(path,"config.h"),os.path.join(path,"upstream"))
    shutil.copy(os.path.join(path,"cairo-features.h"),os.path.join(path,"upstream","src"))
