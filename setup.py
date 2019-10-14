import os
#from distutils.core import setup, Extension
from setuptools import setup, Extension

os.environ["CC"] = "g++"
os.environ["CXX"] = "g++"
#os.environ["CPP"] = "g++"
#os.environ["LDSHARED"] = "g++"

compile_args = ["-O3", "-std=c++11"]
#compile_args = ["-O3", "-g"]
link_args    = ["-lstdc++"]

repeatfinder_module = Extension('repeatfinder',
                    language='g++',
                    extra_compile_args=compile_args,
                    extra_link_args=link_args,
                    include_dirs=[
                             '.',
                             '...',
                             os.path.join(os.getcwd(), 'include'),
                    ],
                    library_dirs = [os.getcwd(),],
                    sources = ['src/repeatfinder.cpp'])

with open("README.md", "r") as fh:
    long_desc = fh.read()


setup (
    name = 'repeatfinder',
    version = '1.5',
    author = "Katelyn McNair",
    author_email = "deprekate@gmail.com",
    description = 'A package for finding repeats in a DNA sequence',
    long_description = long_desc,
    long_description_content_type="text/markdown",
    url =  "https://github.com/deprekate/RepeatFinder",
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
    ],
    python_requires='>3.5.2',
    ext_modules = [repeatfinder_module]
)
