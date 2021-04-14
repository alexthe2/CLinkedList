#include "ListTools.h"


void* PackInt(int content) {
	int* val = SAFEMALLOC(sizeof(int));
	*val = content;

	return val;
}

void* PackDouble(double content) {
	double* dbl = SAFEMALLOC(sizeof(double));
	*dbl = content;

	return dbl;
}

void* PackFloat(float content) {
	float* flt = SAFEMALLOC(sizeof(float));
	*flt = content;

	return flt;
}

void* PackString(const char* content) {
	const size_t length = strlen(content);
	char* ptr = SAFEMALLOC(sizeof(char) * length);

	for(int i = 0; i < length; i++) {
		ptr[i] = content[i];
	}

	return ptr;
}

void EasyFree(void* ctx) {
	free(ctx);
}

int CompareFunctionInt(void* a, void* b) {
	return (*(int*)a) - (*(int*)b);
}

int CompareFunctionDouble(void* a, void* b) {
	return (*(double*)a) - (*(double*)b);
}

int CompareFunctionFloat(void* a, void* b) {
	return (*(float*)a) - (*(float*)b);
}

int CompareFunctionString(void* a, void* b) {
	return strcmp((*(char**)a), (*(char**)b));
}
