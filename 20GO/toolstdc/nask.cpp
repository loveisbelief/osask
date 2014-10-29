/* copyright(C) 2003 H.Kawai (under KL-01). */

#include <cstdio>
#include <cstdlib>

#define SIZ_STDOUT		(16 * 1024)
#define SIZ_STDERR		(16 * 1024)
#define SIZ_WORK		(8 * 1024 * 1024)
#define SIZ_SYSWRK		(1024 * 1024)

#define	MAX_SRCSIZ		(2 * 1024 * 1024)
#define	MAX_TMPSIZ		(4 * 1024 * 1024)
#define	MAX_BINSIZ		(2 * 1024 * 1024)
#define	MAX_LSTSIZ		(4 * 1024 * 1024)

#define	NL			"\n"

typedef struct GO_STR_FILE {
	char *p0, *p1, *p;
	int dummy;
} GO_FILE;

extern GO_FILE GO_stdin, GO_stdout, GO_stderr;
extern struct GOL_STR_MEMMAN GOL_memman, GOL_sysman;
int GOL_retcode;

char *GOL_work0;
int main1(int argc, char **argv, char *src0);
unsigned int GO_strlen(const char *s);
void GOL_sysabort(unsigned char termcode);
void *GOL_memmaninit(struct GOL_STR_MEMMAN *man, size_t size, void *p);

struct bss_alloc {
	char _stdout[SIZ_STDOUT];
	char _stderr[SIZ_STDERR];
	char work[SIZ_WORK];
	char work1[MAX_SRCSIZ + MAX_TMPSIZ + MAX_BINSIZ + MAX_LSTSIZ];
};

#include "../drv_stdc/others.hpp"

int main(int argc, char **argv)
{
	struct bss_alloc *bss0 = (struct bss_alloc *) malloc(sizeof (struct bss_alloc));
	GO_stdout.p0 = GO_stdout.p = bss0->_stdout;
	GO_stdout.p1 = GO_stdout.p0 + SIZ_STDOUT;
	GO_stdout.dummy = ~0;
	GO_stderr.p0 = GO_stderr.p = bss0->_stderr;
	GO_stderr.p1 = GO_stderr.p0 + (SIZ_STDERR - 128); /* わざと少し小さくしておく */
	GO_stderr.dummy = ~0;
	GOL_memmaninit(&GOL_memman, SIZ_WORK, GOL_work0 = bss0->work);

	GOL_retcode = main1(argc, argv, bss0->work1);
	/* バッファを出力 */
	GOL_sysabort(0);
	return 0; /* ダミー */
}

#include "../drv_stdc/others.cpp"
#include "../drv_stdc/wfile_b.cpp"
#include "../drv_stdc/wfile_t.cpp"
#include "../funcs/nasksub.cpp"
