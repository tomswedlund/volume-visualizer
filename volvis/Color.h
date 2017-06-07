#ifndef __Color_h__
#define __Color_h__

class Color {
public:
	Color(float r, float g, float b, float a = 1);
	Color(const Color& toCopy);
	~Color();
	Color& operator =(const Color& rhs);

	void r(float r);
	float r() const;

	void g(float g);
	float g() const;

	void b(float b);
	float b() const;

	void a(float a);
	float a() const;

private:
	static void copy(const Color& from, Color& to);

	float _r, _g, _b, _a;
};

#endif // __Color_h__