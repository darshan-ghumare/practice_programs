#!/usr/bin/env python
# coding=utf-8
class F:
  def f(self):
    print("F:f()")

class A:
  def __init__(self):
    self.__a = F();

  @property
  def a(self):
    return self.__a

  def d(self):
    print("A:d()")

class D:
  def d(self):
    print("D:d()")

class B(D, A):
  def call(self):
    self.d()
    self.a.f()

B().call()
