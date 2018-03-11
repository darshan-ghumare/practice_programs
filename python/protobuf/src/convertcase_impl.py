import sys
import string
import socket
import collections
import convertcase_pb2
import google.protobuf.service
from BaseHTTPServer import HTTPServer
from BaseHTTPServer import BaseHTTPRequestHandler

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


class ConvertcaseRequestHandler(BaseHTTPRequestHandler):
	"""
	This class is used to handle the HTTP requests that arrive at the server.
	By itself, BaseHTTPRequestHandler cannot respond to any actual HTTP requests; it must be subclassed
	to handle each request method (e.g. GET or POST).
	The handler will parse the request and the headers, then call a method specific to the request type.
	The method name is constructed from the request. For example, for the request method SPAM, the
	do_SPAM() method will be called with no arguments.
	"""
	def do_POST(self):
		print("Recv req.....reading body")
		#rfile: Contains an input stream, positioned at the start of the optional input data.
		req_str = self.rfile.read(int(self.headers["content-length"]));
		convertcase_req = convertcase_pb2.ConvertcaseRequest()
		convertcase_req.ParseFromString(req_str)

		print("Recv service_name: "+ convertcase_req.header.service_name +" method_name: "+ convertcase_req.header.method_name)
		service = self.server.service_map[convertcase_req.header.service_name]
		method = service.GetDescriptor().FindMethodByName(convertcase_req.header.method_name)
		req = convertcase_pb2.ConvertcaseService.GetRequestClass(method)()
		resp = convertcase_pb2.ConvertcaseService.GetResponseClass(method)()
		rpc = ConvertcaseController()

		def done_callback(resp):
			"""
			Sends @resp back to the client over HTTP.
			"""
			resp_str = resp.SerializeToString()
			print("Sending "+ resp_str)
			self.send_response(200)
			self.send_header("Content-length", str(len(resp_str)))
			#Sends a blank line, indicating the end of the HTTP headers in the response.
			self.end_headers()
			self.wfile.write(resp_str)

		req.CopyFrom(convertcase_req)
		#Calls ConvertcaseImpl.ToLowercase() or ToUppercase() depending on method descriptor.
		#Once finished call done_callback() to notify.
		service.CallMethod(method, rpc, req, done_callback)


class ConvertcaseServer(HTTPServer):
	"""
	Runs our own HTTP server to (host RPC service) accpet RPC request send over HTTP POST then hand it over
	to ConvertcaseRequestHandler.do_POST() to process it.
	"""
	def __init__(self, host, port):
		HTTPServer.__init__(self, (host, port), ConvertcaseRequestHandler)
		self.service_map = collections.defaultdict()

	def register_service(self, service):
		self.service_map[service.GetDescriptor().name] = service

	def run(self):
		self.serve_forever()


class ConvertcaseImpl(convertcase_pb2.ConvertcaseService):
	"""
	Implement RPC methods which are exported on ConvertcaseServer HTTP server.
	"""
	def ToLowercase(self, rpc_controller, request, done):
		#Create response object for a given method.
		#response = convertcase_pb2.ConvertcaseService.GetResponseClass(method_descriptor)()
		response = convertcase_pb2.ConvertcaseResponse()
		response.word = request.word.lower()
		done(response)

	def ToUppercase(self, rpc_controller, request, done):
		#Create response object for a given method.
		response = convertcase_pb2.ConvertcaseResponse()
		response.word = request.word.upper()
		done(response)



server = ConvertcaseServer("localhost", 8000)
server.register_service(ConvertcaseImpl())
server.run()

