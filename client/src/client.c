#include "client.h"
#include <readline/readline.h>

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();
	log_info(logger,"Soy un log");

	

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"


	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();

	ip = config_get_string_value(config,"IP");
	puerto = config_get_string_value(config,"PUERTO");
	valor = config_get_string_value(config,"CLAVE");

	log_info(logger,"La ip: %s , puerto: %s y clave: %s ",ip,puerto,valor);


	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	// Loggeamos el valor de config


	/* ---------------- LEER DE CONSOLA ---------------- */

	//leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor,conexion);
	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;
	nuevo_logger = log_create("cliente.log","CL_LOG",1,LOG_LEVEL_INFO);
	if(nuevo_logger == NULL){
		printf("Error al crear el log");
		exit (1);
	}

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;
	nuevo_config = config_create("./cliente.config");

	if(nuevo_config==NULL){
		printf("Error con el config");
		exit(2);
	}

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char *leido;

    while (1) {
        leido = readline(">");

		if (strcmp(leido,"")==0) {
                   exit(1);
                }
               if (!leido) {
                   break;
                }

        log_info(logger,"%s\n",leido);
        free(leido);
    }



}

void paquete(int conexion)
{
	//Ahora toca lo divertido!

	char* leido;
	t_paquete* paquete;

	paquete = crear_paquete();

    leido = readline(">");

	while((strcmp(leido,"")!=0)){
		agregar_a_paquete(paquete,leido,strlen(leido) + 1);
        free(leido);
		leido = readline(">");
    }
	
	enviar_paquete(paquete,conexion);

	eliminar_paquete(paquete);
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	if(logger!=NULL){
		log_destroy(logger);
	}

	if(config!=NULL){
		config_destroy(config);
	}

	liberar_conexion(conexion);
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
}
