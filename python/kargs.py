#!/usr/bin/env python
# coding=utf-8
class foo:
  def __init__(self, **kargs):
    self._kargs = kargs

  def print_kargs(self):
    for key in self._kargs.keys():
      print("%s: %s" % (key, self._kargs[key]))

class bar:
  pass

foo(vm=bar(), image="vm1.iso").print_kargs()

