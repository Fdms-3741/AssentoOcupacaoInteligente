#ifndef SERVERH
#define SERVERH

/** Structure that contains information about server state */
struct Server;

/**
 * Set the port to listen to
 *
 * @param server [in] 	Pointer to initialized server struct
 * @param port [in] 	value for the port 
 * @returns int error code for its sucess
 */ 
int DefineServer

/**
 * Initializes the server and returns a pointer to the appropriate Server 
 *
 * @param server [in] Pointer to server to initalize it
 * @returns error code for success in declaring 
 * */
int StartServer(struct Server *server);


/**
 * Waits for receiveing packets and check every income message with an function pointer
 *
 * @param server [in] 		The pointer to the initialized server
 * @param bufferSize [in] 	The maximum size of the buffer
 * @param message [out] 	Pointer to where the message is located
 * 
 * @returns Error code in case of any errors
 * */
int CatchProtocol(struct Server *server, unsigned int bufferSize);


/**
 * Sends message of 
 * */

#endif
