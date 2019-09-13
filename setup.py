#from distutils.core import setup, Extension
from setuptools import setup, Extension
import os

os.environ["CC"] = "g++"
os.environ["CXX"] = "g++"
#os.environ["CPP"] = "g++"
#os.environ["LDSHARED"] = "g++"


compile_args = ["-O3"]

repeatfinder_module = Extension('repeatfinder',
                    language='g++',
                    extra_compile_args=compile_args,
                    include_dirs=[
                             '.',
                             '...',
                             os.path.join(os.getcwd(), 'include'),
                    ],
                    library_dirs = [os.getcwd(),],
                    sources = ['src/repeatfinder.cpp'])

setup (name = 'repeatfinder',
       version = '1.1',
       description = 'A package for finding repeats in a DNA sequence',
       ext_modules = [repeatfinder_module])
