from distutils.core import setup, Extension
import os

os.environ["CC"] = "g++"
os.environ["CXX"] = "g++"


compile_args = ["-O3"]

module1 = Extension('repeatfinder',
                    language='g++',
                    extra_compile_args=compile_args,
                    include_dirs=[
                             '.',
                             '...',
                             os.path.join(os.getcwd(), 'include'),
                    ],
                    library_dirs = [os.getcwd(),],
                    sources = ['src/repeatfinder.cpp'])

setup (name = 'RepeatFinder',
       version = '1.0',
       description = 'The c library for finding repeats',
       ext_modules = [module1])
