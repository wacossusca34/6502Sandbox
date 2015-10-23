#include <stdint.h>

#ifndef SANDBOX_H_
#define SANDBOX_H_

// pool of emulators
typedef struct _sandbox_pool {
	// emus
	struct _sandbox_inst* inst;
	size_t inst_amt;
	// destroys the entire pool
	void (*close) (struct _sandbox_pool* self);
} sandbox_pool;

// instance of a single emulator
typedef struct _sandbox_inst {
	// destroys the emulator
	void (*close) (struct _sandbox_inst* self);
	// passes a program to the emulator, taking an argument to the program itself and a callback function pointer
	// the callback function is invoked when the program is no longer executing
	void (*pass) (struct _sandbox_inst* self, uint8_t* prgm, size_t prgm_size, void (*callback) (int8_t response));
} sandbox_inst;

void __attribute__ ((constructor)) sandbox_init(void);
void __attribute__ ((destructor)) sandbox_fini(void);

// registers a function for the given sandbox pool (how is this supposed to work?)
void __attribute__ ((visibility("default")))
(*sandbox_regcallback) (sandbox_pool* pool, char* identifier, void (*func_ptr) ());

// inits a emulator pool
sandbox_pool* __attribute__ ((visibility("default")))  (*sandbox_init) (int8_t* cores, size_t cores_size);
// creates a new emulator for the specified pool
sandbox_inst* __attribute__ ((visibility("default"))) (*sandbox_newinst) (sandbox_pool* pool, int memory);

#endif // SANDBOX_H_