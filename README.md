# BCIT_datacomm_data_structures
This repository is a compilation of data structures implemented by datacomm students

### requirements
- must only use POSIX standard functions
- nodes must only contain a void* pointer, and pointers to other nodes of the same structure
- do not print to screen, including error logging. Exceptions are: error logging can be deactivated; the function's explicit goal is to produce such output
- function calls that may produce an error must be checked. Appropriate error code must be returned. If the function is already returning a pointer, return null. If the function is returning a numerical value, request a status* as parameter and use it to set the return code

#### must provide
- means to get size
- means to insert
- means to remove
- means to iterate through all values
- means to get a specific value
- means to set a specific value

### casing convention  
snake_case

### naming conventions:  
- filename: name_of_data_structure
- structs: name_of_data_structure_s
- typedef of struct pointer: name_of_data_structure
- function: verb_noun(_preposition_noun)?
- variable: noun(_preposition_noun)?
- constant: NOUN(_PREPOSITION_NOUN)?

### project structure
- a directory for every data structure
- directories should be named as the data structure they contain
