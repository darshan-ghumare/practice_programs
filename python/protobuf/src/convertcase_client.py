import sys
import os
import string
import socket
import collections
import convertcase_pb2
import google.protobuf.service
from httplib import HTTPConnection

class ConvertcaseController(google.protobuf.service.RpcController):
 	"""
        The primary purpose of the controller is to provide a way to manipulate
        settings specific to the RPC implementation and to find out about RPC-level errors.
        """
	def Reset(self):
		return

	def Failed(self):
		return false

	def ErrorText(self):
		return "ERROR"

	def SetFailed(self, reason):
		return

	def StartCancel(self):
		return

	def IsCanceled(self):
		return false

	def NotifyOnCancel(callback):
		#callback()
		return

class ConvertcaseChannel(google.protobuf.service.RpcChannel):
	"""
	An RpcChannel represents a communication line to a service which can be used
	to call that service's methods.  The service may be running on another
	machine.
	"""
	def __init__(self, endpoint):
		self.http_conn =  HTTPConnection(endpoint)

	def CallMethod(self, method_desc, controller, request, response_class, done):
		"""
		Calls the method identified by the descriptor.

		Call the given method of the remote service. The signature of this procedure looks
		the same as Service.CallMethod(), but the requirements are less strict in one
		important way: the request object doesn't have to be of any specific class as long as
		its descriptor is method.input_type.
		"""
		str = request.SerializeToString()
		#Send given @request over HTTP POST to remote HTTP server who is
		#hosting method identified by @method_desc.
		#Caller have already populated with necessary info so just send it across. 
		self.http_conn.request("POST", "rpc/", str)
		print("Sending "+ str)
		#Wait for response from HTTP request and then pass it to the caller using
		#@done() callback.
		resp_obj = self.http_conn.getresponse()
		#print(resp_obj.read())
		str = resp_obj.read(resp_obj.getheader("content-length"))
		response = response_class()
		response.ParseFromString(str)
		done(response)


def done(resp):
	print("Got response "+ resp.word +"\n")

channel = ConvertcaseChannel("localhost:8000")
service = convertcase_pb2.ConvertcaseService_Stub(channel)
method = service.GetDescriptor().FindMethodByName("ToUppercase")
req = convertcase_pb2.ConvertcaseService.GetRequestClass(method)()
rpc = ConvertcaseController()

req.header.service_name = "ConvertcaseService"
req.header.method_name = "ToUppercase"
req.word = "HELLo ! WORLd"
service.ToLowercase(rpc, req, done)

