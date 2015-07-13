#pragma once

enum mcContextState {
	MC_CURL_CONTEXT_ROOT,
	MC_CURL_CONTEXT_CONNECT
};

class mcICurlPerformerContext {
	public:
		virtual void set_context(mcContextState state) = 0;
};
