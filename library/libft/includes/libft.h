/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 12:06:03 by svan-has      #+#    #+#                 */
/*   Updated: 2023/08/14 15:12:58 by psadeghi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	int				index;
}	t_list;

int			ft_isalpha(int x);
int			ft_isdigit(int x);
int			ft_isalnum(int argument);
int			ft_isascii(int argument);
int			ft_isprint(int argument);
size_t		ft_strlen(const char *str);
int			ft_toupper(int ch);
int			ft_tolower(int ch);
void		*ft_memset(void *str, int c, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t len);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
char		*ft_strchr(const char *str, int c);
char		*ft_strrchr(const char *str, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
int			ft_atoi(const char *str);
void		*ft_calloc(size_t nitems, size_t size);
char		*ft_strdup(const char *s1);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_substr_free(char *s, unsigned int start, size_t len, int f);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

/* linked list function */
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* Libft add-ons */
char		*ft_strjoin_free(char *s1, char *s2);
char		*ft_strtrim_free(char *s1, char const *set);
/* counts the words in a line seperated by a SPC */
int			ft_count_word(char const *s, char c);
/* counts the sets of numbers seperated by anything else */
int			ft_count_items(char const *s);
int			*ft_split_num(char const *s); /* splits numbers in a string */

/* GET_NEXT_LINE */
char		*get_next_line(int fd);

int			ft_printf(const char *format, ...);

/* New functions */
long int	ft_atoi_li(const char *str);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

#endif