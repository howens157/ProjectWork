void secretradio_init();
char * secretradio_get_audioloc();
void secretradio_register_callback(void (*f)(int));
void secretradio_listen(int debug);
void secretradio_cleanup();
