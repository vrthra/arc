#include "rc.h"
#include "exec.h"
#include "fns.h"
#include "io.h"

void
rewind(io* o);
char*
treetostr(tree *t, char* buf){
	io* o;
	char* start=buf;
	o = openstr();
	pfmt(o, "%t", t);
	rewind(o);
	while(1) {
		*buf = rchr(o);
		if (!*buf) break;
		++buf;
	}
	closeio(o);
	return start;
}
void
rchistory(tree *t){
	char buf[NBUF];
	struct word *oldw = (word*)0;
	if(!runq->iflag || !t)
		return;
	treetostr(t, buf);
	oldw = copywords(vlook("%")->val, oldw);
	setvar("%", newword(vlook("%%")->val->word, oldw));
	setvar("%%", newword(buf, (word*)0));
}

