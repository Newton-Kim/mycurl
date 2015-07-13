#include "mc-curl-performer-factory.h"
#include "mc-curl-performer.h"

mcIPerformer* mcCurlPerformerFactory::create(void) {
	return new mcCurlPerformer;
}
