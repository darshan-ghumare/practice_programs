#!/usr/bin/env python

import sys
import string
import os
import convertcase_pb2

def SerializeRequest(req):
	str = request.SerializeToString()
	fp = open("proto_rec", "wb")
	fp.write(str)
	fp.close()

def DeserializeRequest():
	fp = open("proto_rec", "rb")
	req = convertcase_pb2.ConvertcaseRequest()
	req.ParseFromString(fp.read())
	fp.close()
	return req


request = convertcase_pb2.ConvertcaseRequest()
request.word = raw_input("Enter string: ")
SerializeRequest(request)
request = DeserializeRequest()
print("req{{word : {0}}}".format(request.word))
