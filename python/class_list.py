#!/usr/bin/env python
# coding=utf-8
class Foo:
  def __init__(self, arg):
    print(arg)

class Foo1(Foo):
  pass

def bar(resolvers_list):
  for arg, resolver in resolvers_list:
    resolver(arg)

bar([("a1", Foo), ("a2", Foo1)])

