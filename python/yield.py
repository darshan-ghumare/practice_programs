#!/usr/bin/env python
# coding=utf-8

import contextlib

"""
  output:
    Without raise ValueError:
      1 call func():
      line 1
      line 2
      ('x = ', None)
      finally line 1

    With raise ValueError:
      1 call func():
      line 1
      ('x = ', None)
      finally line 1
      Traceback (most recent call last):
      File "yield.py", line 29, in <module>
        for i in generator:
      File "yield.py", line 20, in func
        raise ValueError()
      ValueError

    Description:
      When we call func() first time it will return a generator, at this time
      code in func() is not executed. When we use/iterate this generator
      then the code is executed till "yield" is encountered.
"""
def func():
  try:
    print("line 1")
    #raise ValueError()
    print("line 2")
    yield
  finally:
    print("finally line 1")

@contextlib.contextmanager
def func1():
  """
  try:
    print("line 1")
    #raise ValueError()
    print("line 2")
    yield
  finally:
    print("finally line 1")
  """
  # This will be excuted as part of 1st iteration.
  print("func1(): line 1")
  yield # End of first interation.
  # Start of 2nd interation.
  print("func1(): line 2")

#func()
print("1 call func(): ")
generator = func()
for i in generator:
  print("i = ", i)

#func1()
"""
  Output:
    1 call func1():
    func1(): line 1
    Inside with.
    func1(): line 2
"""
print("1 call func1(): ")
with func1():
  print("Inside with.")
