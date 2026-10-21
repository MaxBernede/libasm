#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
 
size_t	ft_strlen(const char *s);
ssize_t	ft_write(int fd, const void *buf, size_t count);
ssize_t	ft_read(int fd, void *buf, size_t count);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strdup(const char *s);
int	ft_strcmp(const char *s1, const char *s2);

static void	test_strlen(const char *s)
{
	printf("\"%s\" -> ft_strlen: %zu | strlen: %zu\n", s, ft_strlen(s), strlen(s));
}

static void	test_write(int fd, const char *s, size_t n)
{
	ssize_t	ret;

	errno = 0;
	ret = ft_write(fd, s, n);
	printf(" <- ft_write: ret=%zd errno=%d\n", ret, errno);
	errno = 0;
	ret = write(fd, s, n);
	printf(" <- write:    ret=%zd errno=%d\n\n", ret, errno);
}

/* path == NULL : utilise fd tel quel (pour tester un fd invalide) */
static void	test_read(const char *path, int fd, size_t n)
{
	char	buf[32];
	ssize_t	ret;
 
	if (path)
		fd = open(path, O_RDONLY);
	memset(buf, 0, sizeof(buf));
	errno = 0;
	ret = ft_read(fd, buf, n);
	printf("ft_read: ret=%zd errno=%d buf=\"%s\"\n", ret, errno, buf);
	if (path)
	{
		close(fd);
		fd = open(path, O_RDONLY);
	}
	memset(buf, 0, sizeof(buf));
	errno = 0;
	ret = read(fd, buf, n);
	printf("read:    ret=%zd errno=%d buf=\"%s\"\n\n", ret, errno, buf);
	if (path)
		close(fd);
}

static int	sign(int n)
{
	return ((n > 0) - (n < 0));
}

static void	test_strcmp(const char *s1, const char *s2)
{
	int	a = ft_strcmp(s1, s2);
	int	b = strcmp(s1, s2);

	printf("\"%s\" vs \"%s\" -> ft: %d | real: %d | %s\n",
		s1, s2, a, b, (sign(a) == sign(b)) ? "OK" : "KO");
}


static void	test_strcpy(const char *src)
{
	char	dst1[64];
	char	dst2[64];
	char	*ret1;
	char	*ret2;

	memset(dst1, 'X', sizeof(dst1));
	memset(dst2, 'X', sizeof(dst2));
	ret1 = ft_strcpy(dst1, src);
	ret2 = strcpy(dst2, src);
	printf("\"%s\" -> ft_strcpy: \"%s\" | strcpy: \"%s\" | ret==dst: %s | %s\n",
		src, dst1, dst2,
		(ret1 == dst1) ? "yes" : "NO",
		(strcmp(dst1, dst2) == 0 && ret2 == dst2) ? "OK" : "KO");
}

static void	test_strdup(const char *s)
{
	char	*d1;
	char	*d2;

	errno = 0;
	d1 = ft_strdup(s);
	d2 = strdup(s);
	if (!d1)
	{
		printf("\"%s\" -> ft_strdup: NULL errno=%d\n", s, errno);
		free(d2);
		return ;
	}
	printf("\"%s\" -> ft_strdup: \"%s\" | strdup: \"%s\" | new ptr: %s | %s\n",
		s, d1, d2,
		(d1 != s) ? "yes" : "NO",
		(strcmp(d1, d2) == 0) ? "OK" : "KO");
	free(d1);
	free(d2);
}

int	main(void)
{
	printf("===== ft_strlen =====\n");
	test_strlen("");                 // empty string → 0
	test_strlen("e");                // single char → 1
	test_strlen("hello world");
	test_strlen("abc\0def");         // stops at first \0 → 3

	printf("\n===== ft_write =====\n");
	fflush(stdout);
	test_write(1, "hello", 5);       // normal write to stdout
	test_write(1, "hello", 0);       // count = 0 → writes nothing, returns 0
	test_write(1, "hello", 3);       // partial write → "hel", returns 3
	test_write(-1, "hello", 5);      // invalid fd → -1, errno = EBADF (9)
	test_write(1, NULL, 5);          // NULL buffer → -1, errno = EFAULT (14)

    printf("===== ft_read =====\n");
	test_read("main.c", 0, 10);      // normal read of 10 bytes
	test_read("main.c", 0, 0);       // count = 0 → reads nothing, returns 0
	test_read(NULL, -1, 10);         // invalid fd → -1, errno = EBADF (9)
	test_read(".", 0, 10);           // read a directory → -1, errno = EISDIR (21)
	test_read(NULL, 42, 10);         // fd not open → -1, errno = EBADF (9)
	{
		int fd = open("/tmp/libasm_test", O_WRONLY | O_CREAT, 0644);
		test_read(NULL, fd, 10);     // write-only fd → -1, errno = EBADF (9)
		close(fd);
	}

	printf("===== ft_strcpy =====\n");
	test_strcpy("");                 // empty string → copies only the \0
	test_strcpy("e");                // single char
	test_strcpy("hello world");      // normal string
	test_strcpy("abc\0def");         // stops at first \0 → "abc"

	printf("\n===== ft_strdup =====\n");
	test_strdup("");                 // empty string → malloc(1), just the \0
	test_strdup("e");                // single char
	test_strdup("hello world");      // normal string
	test_strdup("abc\0def");         // stops at first \0 → "abc"

	printf("\n===== ft_strcmp =====\n");
	test_strcmp("", "");
	test_strcmp("abc", "abc");
	test_strcmp("abc", "abd");       // negative
	test_strcmp("abd", "abc");       // positive
	test_strcmp("abc", "ab");        // s2 shorter
	test_strcmp("ab", "abc");        // s1 shorter
	test_strcmp("", "a");
	test_strcmp("\x80", "a");        // char > 127: must be POSITIVE (unsigned)

	return (0);
}