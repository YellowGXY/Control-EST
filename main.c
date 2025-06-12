/*
Se desea desarrollar un sistema de gestión de ventas qu tenga las siguientes funcionalidades, visualizar productos, crear venta, listar o 
imprimar las ventas, y buscar la venta, los atributos de la venta son los siguientes, nombre del cliente, cedula, total de la venta, 
productos vendidos. Los atributos del producto serian, nombre del producto y precio. NOTA: Los productos deben estar predefinidos, 
maximo 5 minimo 2.

ATRIBUTOS DE LA VENTA:

Nombre del cliente.
Cedula del cliente
Total de 1 venta.
Total de productos vendidos.

ATRIBUTOS DEL PRODUCTO:

Nombre del producto.
Precio del producto.
*/

#include <stdio.h>
#include <string.h>
#include "funciones.h"

int main() {
    struct Producto productos[MAX_PRODUCTOS] = {
        {"Producto 1", 10.0},
        {"Producto 2", 20.0},
        {"Producto 3", 30.0},
        {"Producto 4", 40.0},
        {"Producto 5", 50.0}
    };

    struct Clientes clientes[MAX_PRODUCTOS] = {0};
    struct Venta ventas[100] = {0}; 
    int num_ventas = 0;

    int opcion;
    do {
        opcion = menu();
        printf("\n\n");
        if (opcion < 1 || opcion > 5) {
            printf("Opcion invalida. Por favor, intente de nuevo.\n");
            continue;
        }
        
        switch (opcion) {
            case 1:
                visualizar_productos(productos, MAX_PRODUCTOS);
                printf("\n\n");
                break;
            case 2:
                crear_venta(ventas, &num_ventas, productos, MAX_PRODUCTOS, clientes, MAX_PRODUCTOS);
                        printf("\n\n");
                break;
            case 3:
                listar_ventas(ventas, num_ventas);
                printf("\n\n");
                break;
            case 4:
                buscar_venta(ventas, num_ventas);
                printf("\n\n");
                break;
            case 5:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }
    } while (opcion != 5);

    return 0;
}
