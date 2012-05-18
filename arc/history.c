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
		if (*buf == 0) break;
		buf++;
	}
	closeio(o);
	return start;
}
void
rchistory(tree *t){
	char buf[2048];
	struct var *hist;
	struct word *histval;
	if(!runq->iflag || !t)
		return;
	treetostr(t, buf);
	fprint(2, "<%s>\n", vlook("%")->val->word);
	/*setvar("%", newword(buf, vlook("%")->val));*/
	setvar("%", newword(buf, (word*)0));
}

