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
	test_strlen("");
	test_strlen("e");
	test_strlen("hello world");
	test_strlen("abc\0def");

	printf("\n===== ft_write =====\n");
	fflush(stdout);
	test_write(1, "hello", 5);
	test_write(1, "hello", 0);
	test_write(1, "hello", 3);
	test_write(-1, "hello", 5);

    printf("===== ft_read =====\n");
	test_read("main.c", 0, 10);
	test_read("main.c", 0, 0);
	test_read(NULL, -1, 10);
	test_read(".", 0, 10);

	printf("===== ft_strcpy =====\n");
	test_strcpy("");
	test_strcpy("e");
	test_strcpy("hello world");
	test_strcpy("abc\0def");

	printf("\n===== ft_strdup =====\n");
	test_strdup("");
	test_strdup("e");
	test_strdup("hello world");
	test_strdup("abc\0def");

	return (0);
}