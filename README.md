- PSDI:
    - Este es un proyecto simple de cliente-servidor en C++ usando sockets TCP y hilos. El servidor puede manejar múltiples clientes al mismo tiempo.
    - El servidor escucha en el puerto 5000 y acepta múltiples conexiones de clientes. Cada cliente se maneja en un hilo. El cliente se conecta al servidor, manda un mensaje y recibe una respuesta.
    - Para compilar y ejecutar el proyecto, primero clona el proyecto y entra en la carpeta del código bin. Luego ejecuta make para compilar.
    - Después, ejecuta el servidor con ./server y, en otra terminal, ejecuta el cliente con ./client. En el cliente, escribe mensajes. El servidor los recibirá y responderá. Para cerrar el cliente, escribe exit.
    - Los archivos principales son server.cpp (código del servidor), client.cpp (código del cliente) y Makefile (para compilar el proyecto).

