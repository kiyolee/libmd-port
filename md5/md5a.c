/*
 * Derived from:
 *
 * MDDRIVER.C - test driver for MD2, MD4 and MD5
 */

/*
 *  Copyright (C) 1990-2, RSA Data Security, Inc. Created 1990. All
 *  rights reserved.
 *
 *  RSA Data Security, Inc. makes no representations concerning either
 *  the merchantability of this software or the suitability of this
 *  software for any particular purpose. It is provided "as is"
 *  without express or implied warranty of any kind.
 *
 *  These notices must be retained in any copies of any part of this
 *  documentation and/or software.
 */

/*
 *  This is a modified version that the context structure is hidden
 *  and allocated dynamically.
 */

#ifdef unix
#include <sys/cdefs.h>
#endif
#ifdef __FreeBSD__
__FBSDID("$FreeBSD: release/10.3.0/sbin/md5/md5.c 281513 2015-04-14 00:32:03Z delphij $");
#endif

#ifdef _MSC_VER
#include <stddef.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#if defined(_MSC_VER) || defined(__OS400__)
#include <stdarg.h>
#endif

#include <sys/types.h>
#if defined(unix) || defined(__OS400__)
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#endif
#ifdef unix
#include <err.h>
#include <strings.h>
#endif
#ifdef __OS400__
#include <errno.h>
#include <ctype.h>
#endif

#include "md5.h"
#include "ripemd.h"
#include "sha.h"
#include "sha256.h"
#include "sha512.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if defined(_MSC_VER) || defined(__OS400__)
#include "getopt/getopt.h"
#endif

#if defined(__OS400__)
#include "../libmd/supp/e2a.h"
#endif

#if defined(_MSC_VER) && _MSC_VER >= 1400
#define strnicmp _strnicmp
#elif defined(unix) || defined(__OS400__)
#define strnicmp strncasecmp
#endif

/*
 * Length of test block, number of test blocks.
 */
#define TEST_BLOCK_LEN 10000
#define TEST_BLOCK_COUNT 100000
#define MDTESTCOUNT 8

static int qflag;
static int rflag;
static int sflag;
static char* checkAgainst;
static int checksFailed;

typedef struct DIGEST_CTX_t DIGEST_CTX;

typedef DIGEST_CTX *(DIGEST_Create)(void);
typedef void (DIGEST_Destroy)(DIGEST_CTX *);
typedef void (DIGEST_Update)(DIGEST_CTX *, const void *, size_t);
typedef char *(DIGEST_End)(DIGEST_CTX *, char *);

extern const char *MD5TestOutput[MDTESTCOUNT];
extern const char *SHA1_TestOutput[MDTESTCOUNT];
extern const char *SHA256_TestOutput[MDTESTCOUNT];
extern const char *SHA512_TestOutput[MDTESTCOUNT];
extern const char *RIPEMD160_TestOutput[MDTESTCOUNT];

typedef struct Algorithm_t {
	const char *progname;
	size_t prognamelen;
	const char *name;
	const char *(*TestOutput)[MDTESTCOUNT];
	DIGEST_Create *Create;
	DIGEST_Destroy *Destroy;
	DIGEST_Update *Update;
	DIGEST_End *End;
	char *(*Data)(const void *, unsigned int, char *);
	char *(*File)(const char *, char *);
} Algorithm_t;

static void MDString(const Algorithm_t *, const char *);
#ifndef __OS400__
static void MDTimeTrial(const Algorithm_t *);
#endif
static void MDTestSuite(const Algorithm_t *);
static void MDFilter(const Algorithm_t *, int);
static void usage(const Algorithm_t *);

/* max(MD5_DIGEST_LENGTH, SHA_DIGEST_LENGTH,
	SHA256_DIGEST_LENGTH, SHA512_DIGEST_LENGTH,
	RIPEMD160_DIGEST_LENGTH)*2+1 */
#define HEX_DIGEST_LENGTH 129

#define STR_LEN_PAIR(s) s, (sizeof(s)-sizeof(""))

/* algorithm function table */

static const struct Algorithm_t Algorithm[] = {
	{ STR_LEN_PAIR("md5"), "MD5", &MD5TestOutput,
		(DIGEST_Create*)&MD5Create,
		(DIGEST_Destroy*)&MD5Destroy,
		(DIGEST_Update*)&MD5Update,
		(DIGEST_End*)&MD5End,
		&MD5Data, &MD5File },
	{ STR_LEN_PAIR("sha1"), "SHA1", &SHA1_TestOutput,
		(DIGEST_Create*)&SHA1_Create,
		(DIGEST_Destroy*)&SHA1_Destroy,
		(DIGEST_Update*)&SHA1_Update,
		(DIGEST_End*)&SHA1_End,
		&SHA1_Data, &SHA1_File },
	{ STR_LEN_PAIR("sha256"), "SHA256", &SHA256_TestOutput,
		(DIGEST_Create*)&SHA256_Create,
		(DIGEST_Destroy*)&SHA256_Destroy,
		(DIGEST_Update*)&SHA256_Update,
		(DIGEST_End*)&SHA256_End,
		&SHA256_Data, &SHA256_File },
	{ STR_LEN_PAIR("sha512"), "SHA512", &SHA512_TestOutput,
		(DIGEST_Create*)&SHA512_Create,
		(DIGEST_Destroy*)&SHA512_Destroy,
		(DIGEST_Update*)&SHA512_Update,
		(DIGEST_End*)&SHA512_End,
		&SHA512_Data, &SHA512_File },
	{ STR_LEN_PAIR("rmd160"), "RMD160", &RIPEMD160_TestOutput,
		(DIGEST_Create*)&RIPEMD160_Create,
		(DIGEST_Destroy*)&RIPEMD160_Destroy,
		(DIGEST_Update*)&RIPEMD160_Update,
		(DIGEST_End*)&RIPEMD160_End,
		&RIPEMD160_Data, &RIPEMD160_File }
};

#if defined(_MSC_VER) || defined(__OS400__)

static void
warn(const char *fmt, ...)
{
	va_list va;
	va_start(va, fmt);
	if (fmt != NULL) {
		vfprintf(stderr, fmt, va);
		fprintf(stderr, ": ");
	}
#if defined(_MSC_VER) && _MSC_VER >= 1500
	{
		char err[256];
		if (strerror_s(err, sizeof(err), errno) == 0)
			fprintf(stderr, "%s\n", err);
		else
			fprintf(stderr, "errno(%d)\n", errno);
	}
#else
	fprintf(stderr, "%s\n", strerror(errno));
#endif
	va_end(va);
}

static void
err(int eval, const char *fmt, ...)
{
	va_list va;
	va_start(va, fmt);
	if (fmt != NULL) {
		vfprintf(stderr, fmt, va);
		fprintf(stderr, ": ");
	}
#if defined(_MSC_VER) && _MSC_VER >= 1500
	{
		char err[256];
		if (strerror_s(err, sizeof(err), errno) == 0)
			fprintf(stderr, "%s\n", err);
		else
			fprintf(stderr, "errno(%d)\n", errno);
	}
#else
	fprintf(stderr, "%s\n", strerror(errno));
#endif
	va_end(va);
	exit(eval);
}

#endif

/* Main driver.

Arguments (may be any combination):
  -sstring - digests string
  -t       - runs time trial
  -x       - runs test script
  filename - digests file
  (none)   - digests standard input
 */
int
main(int argc, char *argv[])
{
	int	ch;
	char   *p;
	char	buf[HEX_DIGEST_LENGTH];
	int	failed;
	unsigned	digest;
	const char*	progname;

	if ((progname = strrchr(argv[0], '/')) != NULL)
		progname++;
#ifdef _MSC_VER
	else if ((progname = strrchr(argv[0], '\\')) != NULL)
		progname++;
	else if ((progname = strrchr(argv[0], ':')) != NULL)
		progname++;
#endif
	else
		progname = argv[0];

	for (digest = 0; digest < sizeof(Algorithm)/sizeof(*Algorithm); digest++)
		if (strnicmp(Algorithm[digest].progname, progname, Algorithm[digest].prognamelen) == 0)
			break;

	if (digest == sizeof(Algorithm)/sizeof(*Algorithm))
		digest = 0;

	failed = 0;
	checkAgainst = NULL;
	checksFailed = 0;
	while ((ch = getopt(argc, argv, "c:pqrs:tx")) != -1)
		switch (ch) {
		case 'c':
			checkAgainst = optarg;
			break;
		case 'p':
			MDFilter(&Algorithm[digest], 1);
			break;
		case 'q':
			qflag = 1;
			break;
		case 'r':
			rflag = 1;
			break;
		case 's':
			sflag = 1;
			MDString(&Algorithm[digest], optarg);
			break;
		case 't':
#ifndef __OS400__
			MDTimeTrial(&Algorithm[digest]);
#else
			fprintf(stderr, "option -t is not functional yet on iSeries.\n");
			exit(1);
#endif
			break;
		case 'x':
			MDTestSuite(&Algorithm[digest]);
			break;
		default:
			usage(&Algorithm[digest]);
		}
	argc -= optind;
	argv += optind;

	if (*argv) {
		do {
			p = Algorithm[digest].File(*argv, buf);
			if (!p) {
				warn("%s", *argv);
				failed++;
			} else {
				if (qflag)
					printf("%s", p);
				else if (rflag)
					printf("%s  %s", p, *argv);
				else
					printf("%s (%s) = %s",
					    Algorithm[digest].name, *argv, p);
				if (checkAgainst && strcmp(checkAgainst,p))
				{
					checksFailed++;
					if (!qflag)
						printf(" [ Failed ]");
				}
				printf("\n");
			}
		} while (*++argv);
	} else if (!sflag && (optind == 1 || qflag || rflag))
		MDFilter(&Algorithm[digest], 0);

	if (failed != 0)
		return (1);
	if (checksFailed != 0)
		return (2);

	return (0);
}
/*
 * Digests a string and prints the result.
 */
static void
MDString(const Algorithm_t *alg, const char *string)
{
	size_t len = strlen(string);
	char buf[HEX_DIGEST_LENGTH];

	alg->Data(string,len,buf);
	if (qflag)
		printf("%s", buf);
	else if (rflag)
		printf("%s \"%s\"", buf, string);
	else
		printf("%s (\"%s\") = %s", alg->name, string, buf);
	if (checkAgainst && strcmp(buf,checkAgainst))
	{
		checksFailed++;
		if (!qflag)
			printf(" [ failed ]");
	}
	printf("\n");
}
/*
 * Measures the time to digest TEST_BLOCK_COUNT TEST_BLOCK_LEN-byte blocks.
 */
#ifndef __OS400__
static void
MDTimeTrial(const Algorithm_t *alg)
{
	DIGEST_CTX *pcontext;
#ifdef _MSC_VER
	LARGE_INTEGER freq;
	LARGE_INTEGER before, after;
#else
	struct rusage before, after;
	struct timeval total;
#endif
	int hastime;
	float seconds = 0.0;
	unsigned char block[TEST_BLOCK_LEN];
	unsigned int i;
	char *p, buf[HEX_DIGEST_LENGTH];

	printf("%s time trial. Digesting %d %d-byte blocks ...",
	    alg->name, TEST_BLOCK_COUNT, TEST_BLOCK_LEN);
	fflush(stdout);

	/* Initialize block */
	for (i = 0; i < TEST_BLOCK_LEN; i++)
		block[i] = (unsigned char) (i & 0xff);

	/* Start timer */
#ifdef _MSC_VER
	memset(&before, 0, sizeof(before));
	hastime = (QueryPerformanceFrequency(&freq) && QueryPerformanceCounter(&before));
#else
	getrusage(RUSAGE_SELF, &before);
	hastime = 1;
#endif

	/* Digest blocks */
	pcontext = alg->Create();
	if (pcontext)
	{
		for (i = 0; i < TEST_BLOCK_COUNT; i++)
			alg->Update(pcontext, block, TEST_BLOCK_LEN);
		p = alg->End(pcontext, buf);
		alg->Destroy(pcontext);
		pcontext = NULL;
	}
	else
	{
		p = NULL;
	}

	/* Stop timer */
#ifdef _MSC_VER
	if (hastime) {
		QueryPerformanceCounter(&after);
		seconds = (float)((double)(after.QuadPart - before.QuadPart) / (double)freq.QuadPart);
	}
#else
	getrusage(RUSAGE_SELF, &after);
	timersub(&after.ru_utime, &before.ru_utime, &total);
	seconds = total.tv_sec + (float) total.tv_usec / 1000000;
#endif

	if (p)
	{
		printf(" done\n");
		printf("Digest = %s", p);
		if (hastime) {
			printf("\nTime = %f seconds\n", seconds);
			printf("Speed = %f bytes/second\n",
				(float) TEST_BLOCK_LEN * (float) TEST_BLOCK_COUNT / seconds);
		} else {
			printf("Timing not available\n");
		}
	}
	else
	{
		printf("Failed to create context\n");
	}
}
#endif
/*
 * Digests a reference suite of strings and prints the results.
 */

static const char *MDTestInput[MDTESTCOUNT] = {
	"",
	"a",
	"abc",
	"message digest",
	"abcdefghijklmnopqrstuvwxyz",
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789",
	"12345678901234567890123456789012345678901234567890123456789012345678901234567890",
	"MD5 has not yet (2001-09-03) been broken, but sufficient attacks have been made \
that its security is in some doubt"
};

const char *MD5TestOutput[MDTESTCOUNT] = {
	"d41d8cd98f00b204e9800998ecf8427e",
	"0cc175b9c0f1b6a831c399e269772661",
	"900150983cd24fb0d6963f7d28e17f72",
	"f96b697d7cb7938d525a2f31aaf161d0",
	"c3fcd3d76192e4007dfb496cca67e13b",
	"d174ab98d277d9f5a5611c2c9f419d9f",
	"57edf4a22be3c955ac49da2e2107b67a",
	"b50663f41d44d92171cb9976bc118538"
};

const char *SHA1_TestOutput[MDTESTCOUNT] = {
	"da39a3ee5e6b4b0d3255bfef95601890afd80709",
	"86f7e437faa5a7fce15d1ddcb9eaeaea377667b8",
	"a9993e364706816aba3e25717850c26c9cd0d89d",
	"c12252ceda8be8994d5fa0290a47231c1d16aae3",
	"32d10c7b8cf96570ca04ce37f2a19d84240d3a89",
	"761c457bf73b14d27e9e9265c46f4b4dda11f940",
	"50abf5706a150990a08b2c5ea40fa0e585554732",
	"18eca4333979c4181199b7b4fab8786d16cf2846"
};

const char *SHA256_TestOutput[MDTESTCOUNT] = {
	"e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855",
	"ca978112ca1bbdcafac231b39a23dc4da786eff8147c4e72b9807785afee48bb",
	"ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad",
	"f7846f55cf23e14eebeab5b4e1550cad5b509e3348fbc4efa3a1413d393cb650",
	"71c480df93d6ae2f1efad1447c66c9525e316218cf51fc8d9ed832f2daf18b73",
	"db4bfcbd4da0cd85a60c3c37d3fbd8805c77f15fc6b1fdfe614ee0a7c8fdb4c0",
	"f371bc4a311f2b009eef952dd83ca80e2b60026c8e935592d0f9c308453c813e",
	"e6eae09f10ad4122a0e2a4075761d185a272ebd9f5aa489e998ff2f09cbfdd9f"
};

const char *SHA512_TestOutput[MDTESTCOUNT] = {
	"cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a921d36ce9ce47d0d13c5d85f2b0ff8318d2877eec2f63b931bd47417a81a538327af927da3e",
	"1f40fc92da241694750979ee6cf582f2d5d7d28e18335de05abc54d0560e0f5302860c652bf08d560252aa5e74210546f369fbbbce8c12cfc7957b2652fe9a75",
	"ddaf35a193617abacc417349ae20413112e6fa4e89a97ea20a9eeee64b55d39a2192992a274fc1a836ba3c23a3feebbd454d4423643ce80e2a9ac94fa54ca49f",
	"107dbf389d9e9f71a3a95f6c055b9251bc5268c2be16d6c13492ea45b0199f3309e16455ab1e96118e8a905d5597b72038ddb372a89826046de66687bb420e7c",
	"4dbff86cc2ca1bae1e16468a05cb9881c97f1753bce3619034898faa1aabe429955a1bf8ec483d7421fe3c1646613a59ed5441fb0f321389f77f48a879c7b1f1",
	"1e07be23c26a86ea37ea810c8ec7809352515a970e9253c26f536cfc7a9996c45c8370583e0a78fa4a90041d71a4ceab7423f19c71b9d5a3e01249f0bebd5894",
	"72ec1ef1124a45b047e8b7c75a932195135bb61de24ec0d1914042246e0aec3a2354e093d76f3048b456764346900cb130d2a4fd5dd16abb5e30bcb850dee843",
	"e8a835195e039708b13d9131e025f4441dbdc521ce625f245a436dcd762f54bf5cb298d96235e6c6a304e087ec8189b9512cbdf6427737ea82793460c367b9c3"
};

const char *RIPEMD160_TestOutput[MDTESTCOUNT] = {
	"9c1185a5c5e9fc54612808977ee8f548b2258d31",
	"0bdc9d2d256b3ee9daae347be6f4dc835a467ffe",
	"8eb208f7e05d987a9b044a8e98c6b087f15a0bfc",
	"5d0689ef49d2fae572b881b123a85ffa21595f36",
	"f71c27109c692c1b56bbdceb5b9d2865b3708dbc",
	"b0e20b6e3116640286ed3a87a5713079b21f5189",
	"9b752e45573d4b39f4dbd3323cab82bf63326bfb",
	"5feb69c6bf7c29d95715ad55f57d8ac5b2b7dd32"
};

static void
MDTestSuite(const Algorithm_t *alg)
{
	int i;
	char buffer[HEX_DIGEST_LENGTH];

	printf("%s test suite:\n", alg->name);
	for (i = 0; i < MDTESTCOUNT; i++) {
#ifdef __OS400__
		char asc[1024];
		e2acpy(asc, MDTestInput[i]);
		(*alg->Data)((const unsigned char *)(asc), strlen(MDTestInput[i]), buffer);
#else
		(*alg->Data)((const unsigned char *)(MDTestInput[i]), strlen(MDTestInput[i]), buffer);
#endif
		printf("%s (\"%s\") = %s", alg->name, MDTestInput[i], buffer);
		if (strcmp(buffer, (*alg->TestOutput)[i]) == 0)
			printf(" - verified correct\n");
		else
			printf(" - INCORRECT RESULT!\n");
	}
}

/*
 * Digests the standard input and prints the result.
 */
static void
MDFilter(const Algorithm_t *alg, int tee)
{
	DIGEST_CTX *pcontext;
	unsigned int len;
	unsigned char buffer[BUFSIZ];
	char buf[HEX_DIGEST_LENGTH];

	pcontext = alg->Create();
	if (pcontext)
	{
		while ((len = fread(buffer, 1, BUFSIZ, stdin)) > 0) {
			if (tee && len != fwrite(buffer, 1, len, stdout))
				err(1, "stdout");
			alg->Update(pcontext, buffer, len);
		}
		printf("%s\n", alg->End(pcontext, buf));
		alg->Destroy(pcontext);
		pcontext = NULL;
	}
	else
	{
		printf("Failed to create context\n");
	}
}

static void
usage(const Algorithm_t *alg)
{

	fprintf(stderr, "usage: %s [-pqrtx] [-c string] [-s string] [files ...]\n", alg->progname);
	exit(1);
}

/* vim: ts=4:sts=4:sw=4:noet
 */
