float MulAdd(float a, float b, float c) { return a * b + c; }
float Dot3(const float *a, const float *b) { return a[0] * b[0] + a[1] * b[1] + a[2] * b[2]; }
float Lerp(float a, float b, float t) { return a + (b - a) * t; }
int Trunc(float f) { return (int)f; }
float Div(float a, float b) { return a / b; }
bool Less(float a, float b) { return a < b; }
float Recip(float a) { return 1.0f / a; }
