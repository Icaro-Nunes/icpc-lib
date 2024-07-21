#include <iostream>
#include <math>

const long double PI = std::arccos(-1);

template<typename T>
struct Complex {
	T a, b;

	Complex(T a, T b) {
		this->a = a;
		this->b = b;
	}

	Complex(T a) {
		this->a = a;
		this->b = 0;
	}

	Complex operator+(const Complex& other) const {
		return Complex(a+other.a, b+other.b);
	}

	Complex operator-(const Complex& other) const {
		return Complex(a-other.a, b-other.b);
	}

	Complex operator*(const T& real) const {
		return Complex(a*real, b*real);
	}

	Complex operator*(const Complex& other) const {
		return Complex(a*other.a - b*other.b, a*other.b + b*other.a);
	}
};



// works for a power of 2 sized vector
// T must be a floating point type because
// of the trigonometric operations
template<typename T>
vector<Complex<T>> fft(const vector<T>& p) {
	int n = p.size();

	vector<Complex<T>> ans(n);

	if(n == 1) {
		ans[0] = Complex<T>(p[0]);
		return ans;
	}

	T angle = (2*PI)/n;
	Complex<T> w = Complex<T>(std::cos(angle), std::sin(angle));

	vector<T> pe(n/2), po(n/2);
	for(int i=0; i<=n-2; i+=2)
		pe[i/2] = p[i], po[i/2] = p[i+1];
	
	vector<Complex<T>> ye = fft(pe), yo = fft(po);

	Complex<T> w_i = Complex<T>(T(1));

	for(int i=0; i<n/2; i++) {
		ans[i] = ye[i] + w_i*yo[i];
		ans[i+n/2] = ye[i] - w_i*yo[i];
		w_i = w_i*w;
	}

	return ans;
}




// works for a power of 2 sized vector
// T must be a floating point type because
// of the trigonometric operations
template<typename T>
vector<Complex<T>> ifft(const vector<Complex<T>>& p) {
	int n = p.size();

	vector<Complex<T>> ans(n);

	if(n == 1) {
		ans[0] = Complex<T>(p[0]);
		return ans;
	}

	T angle = (2*PI)/n;
	Complex<T> w = (1/double(n)) * Complex<T>(std::cos(-angle), std::sin(-angle));

	vector<T> pe(n/2), po(n/2);
	for(int i=0; i<=n-2; i+=2)
		pe[i/2] = p[i], po[i/2] = p[i+1];
	
	vector<Complex<T>> ye = ifft(pe), yo = ifft(po);

	Complex<T> w_i = Complex<T>(T(1));

	for(int i=0; i<n/2; i++) {
		ans[i] = ye[i] + w_i*yo[i];
		ans[i+n/2] = ye[i] - w_i*yo[i];
		w_i = w_i*w;
	}

	return ans;
}





std::ostream& operator<<(std::ostream& os, const Complex<T>& c) {
	os << "Complex(" << c.a << ", " << c.b << ")";
	return os;
}






