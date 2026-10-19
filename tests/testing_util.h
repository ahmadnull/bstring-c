
#define BLUE   "\033[34m"
#define GREEN  "\033[32m"
#define CYAN   "\033[36m"
#define YELLOW "\033[33m"
#define BOLD   "\033[1m"
#define NORMAL "\033[0m"

#define index_start(level, start) static size_t index_##level = start

#define run_test(test) do                                       \
{                                                               \
    printf("\n" BOLD BLUE "[%zu] " #test NORMAL "\n", index_0); \
    test();                                                     \
    index_0++;                                                  \
} while (0)

#define tee(statement) do                                                          \
{                                                                                  \
    printf("\n" GREEN BOLD "[%zu.%zu] " #statement NORMAL "\n", index_0, index_1); \
    statement;                                                                     \
    index_1++;                                                                     \
} while (0)

#define debug(name, specifier, value, tabs) do                                                                           \
{                                                                                                                        \
    printf("\n" CYAN BOLD "[%zu.%zu] " name "%.*s= %" specifier NORMAL "\n", index_0, index_1, tabs, "\t\t\t", value);   \
    index_1++;                                                                                                           \
} while (0)

#define log(comment) printf("\n" YELLOW BOLD comment NORMAL "\n")
