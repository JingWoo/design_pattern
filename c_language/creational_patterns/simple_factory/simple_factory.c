#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef enum _ProductType {
    PRODUCTA,
    PRODUCTB
} ProductType;

typedef struct _AbstractProduct {
    ProductType type;
    void (*DisplayProduct)(struct _AbstractProduct *product);
    void (*Destroy)(struct _AbstractProduct **product);
} AbstractProduct;

void DisplayProductA(AbstractProduct *product)
{
    assert(NULL != product);
    printf("product A\n");
}

void DisplayProductB(AbstractProduct *product)
{
    assert(NULL != product);
    printf("product B\n");
}

void DestroyProduct(AbstractProduct **product)
{
    assert(product != NULL);
    free(*product);
    *product = NULL;
}

AbstractProduct *SimpleFactoryCreateProduct(ProductType type)
{
    assert(type == PRODUCTA || type == PRODUCTB);
    AbstractProduct *product = (AbstractProduct *)malloc(sizeof(AbstractProduct));
    assert(product != NULL);
    switch (type) {
        case PRODUCTA:
            product->type = PRODUCTA;
            product->DisplayProduct = DisplayProductA;
            product->Destroy = DestroyProduct;
            break;
        case PRODUCTB:
            product->type = PRODUCTB;
            product->DisplayProduct = DisplayProductB;
            product->Destroy = DestroyProduct;
            break;
        default:
            fprintf(stderr, "Invalid product type\n");
            break;
    }

    return product;
}

int main()
{
    AbstractProduct *product = SimpleFactoryCreateProduct(PRODUCTA);
    product->DisplayProduct(product);
    product->Destroy(&product);
    assert(product == NULL);

    product = SimpleFactoryCreateProduct(PRODUCTB);
    product->DisplayProduct(product);
    product->Destroy(&product);
    assert(product == NULL);

    exit(EXIT_SUCCESS);
}

