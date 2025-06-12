#include <stdio.h>
#include <string.h>
#include "funciones.h"

void limpiar_buffer() {
    while (getchar() != '\n');
}

void leercadena(char *cadena, int longitud) {
    fgets(cadena, longitud, stdin);
    int len = strlen(cadena);
    if (len > 0 && cadena[len - 1] == '\n') {
        cadena[len - 1] = '\0';
    }
}

int leer_entero() {
    int numero;
    while (1) {
        if (scanf("%d", &numero) != 1) {
            limpiar_buffer();
            printf("Entrada invalida. Por favor, ingrese un numero entero: ");
        } else {
            limpiar_buffer();
            if (numero < 0) {
                printf("Por favor, ingrese un numero positivo: ");
                continue;
            }
            return numero;
        }
    }
}

int menu() {
    printf("Menu:\n");
    printf("1. Visualizar productos\n");
    printf("2. Crear venta\n");
    printf("3. Listar ventas\n");
    printf("4. Buscar venta\n");
    printf("5. Salir\n");
    printf("Seleccione una opcion: ");
    return leer_entero();
}

void visualizar_productos(struct Producto productos[], int cantidad) {
    printf("Productos disponibles:\n");
    for (int i = 0; i < cantidad; i++) {
        printf("%d. %s\t - Precio: %.2f\n", i + 1, productos[i].nombre, productos[i].precio);
    }
}

void crear_venta(struct Venta ventas[], int *num_ventas, struct Producto productos[], int cantidad_productos, struct Clientes clientes[], int cantidad_clientes) {
    int hay_clientes = 0;
    int cliente_idx = -1;

    for (int i = 0; i < cantidad_clientes; i++) {
        if (strlen(clientes[i].nombre) > 0) {
            hay_clientes = 1;
            break;
        }
    }

    if (hay_clientes) {
        printf("Ya existen clientes registrados.\n");
        printf("1. Elegir cliente existente\n");
        printf("2. Registrar nuevo cliente\n");
        printf("Seleccione una opcion: ");
        int opcion = leer_entero();
        if (opcion == 1) {
            printf("Clientes registrados:\n");
            int total_clientes = 0;
            for (int i = 0; i < cantidad_clientes; i++) {
                if (strlen(clientes[i].nombre) > 0) {
                    printf("%d. %s\t (Cedula: %s)\n", total_clientes + 1, clientes[i].nombre, clientes[i].cedula);
                    total_clientes++;
                }
            }
            if (total_clientes == 0) {
                printf("No hay clientes registrados. Debe registrar uno nuevo.\n");
                opcion = 2;
            } else {
                int seleccion;
                do {
                    printf("Seleccione el numero del cliente: ");
                    seleccion = leer_entero();
                    if (seleccion < 1 || seleccion > total_clientes) {
                        printf("Seleccion invalida.\n");
                    }
                } while (seleccion < 1 || seleccion > total_clientes);
                int contador = 0;
                for (int i = 0; i < cantidad_clientes; i++) {
                    if (strlen(clientes[i].nombre) > 0) {
                        contador++;
                        if (contador == seleccion) {
                            cliente_idx = i;
                            break;
                        }
                    }
                }
            }
        }
        if (opcion == 2 || cliente_idx == -1) {
            for (int i = 0; i < cantidad_clientes; i++) {
                if (strlen(clientes[i].nombre) == 0) {
                    cliente_idx = i;
                    break;
                }
            }
            if (cliente_idx == -1) {
                printf("No hay espacio para mas clientes.\n");
                return;
            }
            printf("Ingrese el nombre del cliente: ");
            leercadena(clientes[cliente_idx].nombre, 50);
            printf("Ingrese la cedula del cliente: ");
            leercadena(clientes[cliente_idx].cedula, 20);
        }
    } else {
        cliente_idx = 0;
        printf("Ingrese el nombre del primer cliente: ");
        leercadena(clientes[cliente_idx].nombre, 50);
        printf("Ingrese la cedula del cliente: ");
        leercadena(clientes[cliente_idx].cedula, 20);
    }

    int prod_idx = -1;
    do {
        visualizar_productos(productos, cantidad_productos);
        printf("Ingrese el numero del producto: ");
        prod_idx = leer_entero() - 1;
        if (prod_idx < 0 || prod_idx >= cantidad_productos) {
            printf("Producto invalido. Intente de nuevo.\n");
        }
    } while (prod_idx < 0 || prod_idx >= cantidad_productos);

    int cantidad;
    do {
        printf("Ingrese la cantidad a vender: ");
        cantidad = leer_entero();
        if (cantidad <= 0) {
            printf("La cantidad debe ser mayor a cero.\n");
        }
    } while (cantidad <= 0);

    float total = productos[prod_idx].precio * cantidad;

    ventas[*num_ventas].cliente = clientes[cliente_idx];
    ventas[*num_ventas].producto = productos[prod_idx];
    ventas[*num_ventas].cantidad = cantidad;
    ventas[*num_ventas].total_venta = total;
    (*num_ventas)++;

    printf("Venta creada exitosamente. Total: %.2f\n", total);
}

void listar_ventas(struct Venta ventas[], int num_ventas) {
    if (num_ventas == 0) {
        printf("No hay ventas registradas.\n");
        return;
    }
    printf("Listado de ventas:\n");
    for (int i = 0; i < num_ventas; i++) {
        printf("Venta #%d\n", i + 1);
        printf("Cliente: %s (Cedula: %s)\n", ventas[i].cliente.nombre, ventas[i].cliente.cedula);
        printf("Producto: %s\n", ventas[i].producto.nombre);
        printf("Cantidad: %d\n", ventas[i].cantidad);
        printf("Total venta: %.2f\n", ventas[i].total_venta);
        printf("-------------------------\n");
    }
}

void buscar_venta(struct Venta ventas[], int num_ventas) {
    if (num_ventas == 0) {
        printf("No hay ventas registradas.\n");
        return;
    }
    char cedula[20];
    printf("Ingrese la cedula del cliente a buscar: ");
    leercadena(cedula, 20);
    int encontrado = 0;
    for (int i = 0; i < num_ventas; i++) {
        if (strcmp(ventas[i].cliente.cedula, cedula) == 0) {
            printf("Venta #%d\n", i + 1);
            printf("Cliente: %s (Cedula: %s)\n", ventas[i].cliente.nombre, ventas[i].cliente.cedula);
            printf("Producto: %s\n", ventas[i].producto.nombre);
            printf("Cantidad: %d\n", ventas[i].cantidad);
            printf("Total venta: %.2f\n", ventas[i].total_venta);
            printf("-------------------------\n");
            encontrado = 1;
        }
    }
    if (!encontrado) {
        printf("No se encontraron ventas para la cedula ingresada.\n");
    }
}