Float_t Bisection(Float_t left,Float_t right,Float_t epsilon, TGraphErrors *g, Float_t mean) {
	Float_t midpoint;
	do {
		midpoint = (right + left) / 2;
		if(((g->Eval(left) - mean) * (g->Eval(midpoint) - mean)) < 0)
			right = midpoint;
		else if(((g->Eval(right) - mean) * (g->Eval(midpoint) - mean)) < 0)
			left = midpoint;
		else return midpoint;
	} while (fabs(right - left) > 2*epsilon);
	return midpoint;
}