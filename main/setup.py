from setuptools import setup
from Cython.Build import cythonize

setup(
    name="sgo",						# 这个位置我也不确定有什么用，随便写吧！
    ext_modules=cythonize("sgo.py") # 这里放入需要生成为pyd文件的py文件
)
