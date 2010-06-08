// $Id$

local vector = Vector3(1, 7, 3);
print(vector.X + ", " + vector.Y + ", " + vector.Z);

local vector2 = vector.normalize();
print(vector2.X + ", " + vector2.Y + ", " + vector2.Z);

local vector3 = -(vector.setLength(10) * 10);
print(vector3.X + ", " + vector3.Y + ", " + vector3.Z);

print("Noch ein Test:");
print(vector);

local vector4 = Vector3(0, 1, 0) % Vector3(1, 0, 0);
print(vector4);
