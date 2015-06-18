#include "mc-curl-performer.h"
#include <cstdio>

mcCurlPerformer::mcCurlPerformer():m_current(NULL) {
}

mcLanguageState mcCurlPerformer::open(string url, string alias){
	if(m_current) {
		fprintf(stderr, "A handle cannot be opened in another handle");
	} else {
		string mnymonic = (alias.empty()) ? url : alias;
		if(m_map.find(mnymonic) == m_map.end()) {
			m_current = new mcCurl(url, mnymonic);
			m_map[mnymonic] = m_current;
		} else {
			m_current = m_map[mnymonic];
		}
	}
	return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformer::close(void){
	if(!m_current) {
		fprintf(stderr, "invalid handle\n");
	} else {
		m_map[m_current->mnymonic()] = NULL;
		m_map.erase(m_current->mnymonic());
		delete m_current;
		m_current = NULL;
	}
	return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformer::verbose(bool& onoff){
	if(!m_current) {
		fprintf(stderr, "invalid handle\n");
	} else {
		onoff = m_current->verbose();
	}
	return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformer::verbose_on(void){
	if(!m_current) {
		fprintf(stderr, "invalid handle\n");
	} else {
		m_current->verbose(true);
	}
	return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformer::verbose_off(void){
	if(!m_current) {
		fprintf(stderr, "invalid handle\n");
	} else {
		m_current->verbose(false);
	}
	return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformer::leave(void){
	if(!m_current) {
		fprintf(stderr, "invalid handle\n");
	} else {
		m_current = NULL;
	}
	return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformer::list(void){
	if(m_current) {
		fprintf(stderr, "A handles cannot be listed in another handle");
	} else {
		for(map<string, mcCurl*>::iterator it = m_map.begin() ; it != m_map.end() ; it++)
			fprintf(stdout, "%s\n", it->second->mnymonic().c_str());
	}
	return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformer::get(string path, string lst){
	if(!m_current) {
		fprintf(stderr, "invalid handle\n");
	} else {
		m_current->get(path, lst);
	}
	return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformer::del(string lst){
	if(!m_current) {
		fprintf(stderr, "invalid handle\n");
	} else {
		m_current->del(lst);
	}
	return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformer::post(string inpath, size_t chunk, string outpath, string lst){
	if(!m_current) {
		fprintf(stderr, "invalid handle\n");
	} else {
		m_current->post(inpath, chunk, outpath, lst);
	}
	return MC_LANG_CONTINUE;
}

mcLanguageState mcCurlPerformer::put(string inpath, size_t chunk, string outpath, string lst){
	if(!m_current) {
		fprintf(stderr, "invalid handle\n");
	} else {
		m_current->put(inpath, chunk, outpath, lst);
	}
	return MC_LANG_CONTINUE;
}

string mcCurlPerformer::current(void){
	return m_current ? m_current->mnymonic() : "mycurl";
}

mcLanguageState mcCurlPerformer::header(string key, string value, string lst){
	if(!m_current) {
		fprintf(stderr, "invalid handle\n");
	} else {
		m_current->header(key, value, lst);
	}
	return MC_LANG_CONTINUE;
}
