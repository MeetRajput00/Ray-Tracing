#pragma once
#ifndef SPHERE_H
#define SPHERE_H

#include"hittable.h"
#include"vec3.h"

class Sphere :public Hittable {
public:
	Sphere() {}
	Sphere(Point3 cen, double r) : center(cen), radius(r) {};
	virtual bool hit(const Ray& r, double t_max, double t_min, Hit_Record& rec) const override;
public:
	Point3 center;
	double radius;
};
bool Sphere::hit(const Ray& r, double t_max, double t_min, Hit_Record& rec) const {
	Vec3 oc = r.origin() - center;
	auto a = r.direction().length_squared();
	auto b = dot(oc, r.direction());
	auto c = oc.length_squared() - radius * radius;
	auto discriminant = b * b - a * c;
	if (discriminant < 0)
		return false;
	auto sqrtd = sqrt(discriminant);

	auto root = (-b - sqrtd) / a;
	if (root < t_min || t_max < root) {
		root = (-b + sqrtd) / a;
		if (root < t_min || t_max < root)
			return false;
	}
	rec.t = root;
	rec.p = r.at(rec.t);
	Vec3 outward_normal = (rec.p - center) / radius;
	rec.set_face_normal(r, outward_normal);
	return true;
}

#endif // !SPHERE_H
