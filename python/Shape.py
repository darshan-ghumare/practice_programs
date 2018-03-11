class Point:
	def __init__(self, x=0, y=0):
		self.x = x
		self.y = y
	def distance_from_origin(self):
        print("Pomt method called.")
		return math.hypot(self.x, self.y)
	def __eq__(self, other):
		return self.x == other.x and self.y == other.y
	def __repr__(self):
		return "Point({0.x!r}, {0.y!r})".format(self)
	def __str__(self):
		repr(self)
		#return "({0.x!r}, {0.y!r})".format(self)

class Circle(Point):
	def __init__(self, radius, x=0, y=0):
		Point.__init__(self, x, y)
		self.radius = radius
	def distance_from_origin(self):
        print("Circle method called.")
	def edge_distance_from_origin(self):
		return abs(self.distance_from_origin() - self.radius)
	def __str__(self):
		repr(self)
	def __repr__(self):
		return "Circle({0.radius!r}, {0.x!r}, {0.x!r})".format(self)

p = Point()
p.distance_from_origin()
Circle().distance_from_origin()
if not p.z:
    print("z not set")
else:
    print("z not set")
