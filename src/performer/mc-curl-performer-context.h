#pragma once

#include "stackframe/mc-curl-stack-frame.h"
#include <vector>

using namespace std;

enum mcContextState {
	MC_CURL_CONTEXT_ROOT = 0,
	MC_CURL_CONTEXT_CONNECT
};

class mcICurlPerformerContext {
	public:
		virtual void set_context(mcContextState state, vector<mcIStackFrame*>* stack = NULL) = 0;
};
