using ld = double;
const ld eps = 1e-8;
bool iszero(ld x) { return abs(x) <= eps; }

// solves linear systems for numerical types
// expected to solve for double, frac, modint (with prime mod)
// type must implement operations: +, -, *, /, =, iszero(num), constructor that accepts 0
template<typename T>
struct LinearSolver {
	int n;
	vector<vector<T>> A;

	// solution to the system, vector of size n
	vector<T> x;
	// index of equation for i-th variable
	// after solution is performed,
	// ind[i] will be an equation where c[i] == 1
	// if i is an independent variable, ind[i] = n
	vector<int> ind;

	// status:
	// -2: not solved
	// -1: no valid solutions
	// 0: solved, no independent terms
	// i: solved, i independent terms
	int status=-2;

	// n: number of variables in the system
	// each row in sys must have size n+1,
	// with A[i][n] = rhs of the i-th equation, independent term
	//
	// also say goodbye to your matrix
	// because it is erased from your original variable
	LinearSolver(vector<vector<T>>& sys) {
		n = sys.size();
		A = std::move(sys);
	}

	LinearSolver(int n): n(n) {
		A = vector<vector<T>>(n, vector<T>(n+1, T(0)));
	}

	// evaluate i-th variable with independent terms
	// set according to in
	T eval(int i, const vector<T>& in) {
		// equation index
		int e = ind[i];

		T v(0);
		if(e == n) return v;

		for(int j=0; j<n; j++) if(j != i)
			v = v - A[e][j] * in[j];

		v = v + A[e][n];
		return v;
	}

	int solve() {
		ind = vector<int>(n, n);

		// solved columns
		int sc = 0;

		// solve for i-th column
		for(int i=0; i<n; i++) {
			// choose i-th pivot
			int p=sc;
			for(; p<n; p++) if(!iszero(A[p][i])) break;

			// no pivot (independent variable)
			if(p == n) {
				ind[i] = n;
				continue;
			}

			ind[i] = sc;
			swap(A[sc], A[p]);

			// set pivot to 1
			{
				T r = A[sc][i]; // ratio
				for(int j=0; j<n+1; j++)
					A[sc][j] = A[sc][j] / r;
			}

			// zero i-th coefficient in every other equation
			for(int j=0; j<n; j++) if(j != sc and !iszero(A[j][i])) {
				// ratio
				T r = A[j][i];
				for(int k=0; k < n+1; k++)
					A[j][k] = A[j][k] - A[sc][k] * r;
			}

			sc++;
		}

		status = n - sc;

		// check if solution is consistent
		x = vector<T>(n, T(0));

		for(int i=0; i<n; i++)
			x[i] = eval(i, x);

		for(int i=0; i<n; i++) {
			T lhs = 0;
			for(int j=0; j<n; j++)
				lhs = lhs + A[i][j] * x[j];
			if(!iszero(lhs - A[i][n]))
				return status = -1;
		}

		return status;
	}
