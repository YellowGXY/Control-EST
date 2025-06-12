struct Clientes {
    char nombre[50];
    char cedula[20];
};

struct Producto {
    char nombre[50];
    float precio;
};

struct Venta {
    struct Clientes cliente;
    struct Producto producto;
    int cantidad;
    float total_venta;
};

#define MAX_PRODUCTOS 5

void limpiar_buffer();
void leercadena(char *cadena, int longitud);
int leer_entero();
int menu();

void crear_venta(struct Venta ventas[], 
                 int *num_ventas, 
                 struct Producto productos[], 
                 int cantidad_productos, 
                 struct Clientes clientes[], 
                 int cantidad_clientes
                );
                
void visualizar_productos(struct Producto productos[], int cantidad);
void listar_ventas(struct Venta ventas[], int num_ventas);
void buscar_venta(struct Venta ventas[], int num_ventas);