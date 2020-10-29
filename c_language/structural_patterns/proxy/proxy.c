#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct image {
    void (*display)(void *);
};

struct real_image {
    struct image interface;
    char *file_name;
    void (*load)(char *file_name);
};

static void load(char *file_name)
{
    printf("loading image file: %s\n", file_name);
}

static void real_display(void *image)
{
    struct real_image *real_image = (struct real_image *)image;
    real_image->load(real_image->file_name);
    printf("real display image file: %s\n", real_image->file_name);
}

struct real_image *real_image_init(const char *file_name)
{
    struct real_image *real_image = (struct real_image *)calloc(1, sizeof(struct real_image));
    assert(real_image != NULL);
    real_image->file_name = strdup(file_name);
    real_image->load = load;
    real_image->interface.display = real_display;

    return real_image;
}

struct proxy_image {
    struct image interface;
    char *file_name;
};

void proxy_display(void *image)
{
    struct proxy_image *proxy_image = (struct proxy_image *)image;
    struct real_image *real_image = real_image_init(proxy_image->file_name);

    printf("proxy display image file: %s\n", proxy_image->file_name);
    real_image->interface.display(real_image);
    free(real_image->file_name);
    free(real_image);
}

int main()
{
    struct proxy_image proxy_image;
    struct image *image = NULL;
    proxy_image.file_name = strdup("hello.png");
    proxy_image.interface.display = proxy_display;

    image = (struct image *)&proxy_image;
    image->display(&proxy_image);
    free(proxy_image.file_name);

    exit(EXIT_SUCCESS);
}
