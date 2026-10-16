#include <stdio.h>
#include <string.h>

size_t ft_strlen(const char *s);

int main(void)
{
    printf("ft_strlen : %zu\n", ft_strlen("hello"));
    printf("strlen    : %zu\n", strlen("hello"));
    return 0;
}